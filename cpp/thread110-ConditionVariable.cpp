//------------------------------------------------
// description..: condition variable
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <type_traits>
#include <queue>
#include <thread>
#include <algorithm>	// for_each
#include <mutex>
#include <condition_variable>
#include <cstdlib>		// rand()

using namespace std;
/*
	condition variable (CV) -> header <condition_variable>
	- A condition variable is an object able to block the calling thread until notified to resume.
  	  It uses a unique_lock (over a mutex) to lock the thread when one of its wait functions is
      called. 
      The thread remains blocked until woken up by another thread that calls a
      notification function on the same condition_variable object.
      Objects of type condition_variable always use unique_lock<mutex> to wait: for 
      an  alternative that works with any kind of lockable type, see condition_variable_any
    -The most  basic mechanism for waiting for an event to be triggered by another thread
*/

constexpr int MaxNumberItems = 10;
typedef int data_chunk;
int numberItemsGenerated=0;
data_chunk lastChunk=-1;


// the mutex used to protect the shared data
std::mutex mut;

// you have a queue  that’s used to pass the data between the two threads
std::queue<data_chunk> data_queue;                 

// the condition var. using to synchronize the access to the shared data
std::condition_variable data_cond;

//----------------------------------------------------------------------
const data_chunk prepare_data()
{
	numberItemsGenerated++;

	int i = rand()%1000;
	cout << ">>>prepared data=" << i << endl;
	lastChunk = static_cast<const data_chunk>(i);

	return lastChunk;
}

//----------------------------------------------------------------------
bool more_data_to_prepare()
{

	return (numberItemsGenerated <= MaxNumberItems) ? true : false;

}

//----------------------------------------------------------------------
bool is_last_chunk(data_chunk data)
{
	cout << "DEBUG: is_last_chunk() - numberItemsGenerated=" << numberItemsGenerated
	     << "; MaxNumberItems=" << MaxNumberItems << endl;
	if (numberItemsGenerated > MaxNumberItems)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------
void data_preparation_thread()
{
	cout << endl;
	cout << ">>>>>In data_preparation_thread() - Start" << endl;

    while(more_data_to_prepare())
    {

    	cout << endl;
    	cout << ">>>>>In data_preparation_thread() - preparing more data ..." << endl;

        //When the data is ready, the thread preparing the data locks the mutex         
        //protecting the queue using a std::lock_guard and pushes the data onto the queue 
        data_chunk const data=prepare_data();
        {
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(data);  
        } // end of scope - unlocks the mutex mut !!!

        //It then calls the notify_one() member function on the std::condition_variable instance 
        //to notify the waiting thread (if there is one)
        //(*) Note that you put the code to push the data onto the queue in a smaller scope, so
        //      you notify the condition variable after unlocking the mutex — this is so that, if the 
        //      waiting thread wakes immediately, it doesn’t then have to block again, waiting         
        //       for you to unlock the mutex.      
        data_cond.notify_one(); 
        std::this_thread::sleep_for (std::chrono::seconds(2));

    }
}

//----------------------------------------------------------------------
void process(const data_chunk value)
{
	cout << ">>>processing data_chunk; value=" << static_cast<int>(value) << endl;
}

//----------------------------------------------------------------------
void data_processing_thread()
{

	cout << endl;
	cout << ">>>>>In data_processing_thread()..." << endl;

    while(true)
    {

    	cout << ">>>>>In data_processing_thread() - waiting fro more data ..." << endl;

        //This thread first locks the mutex, but this time with a std::unique_lock rather 
        // than a std::lock_guard
        std::unique_lock<std::mutex> lk(mut); 
        
         //The thread then calls wait() on the std:: condition_variable, passing in the 
         //lock object and a lambda function that expresses the condition being waited for
        
        //(*) the  lambda function checks to see if the data_queue is not empty()—that is, there’s 
        //     some data in the queue ready for processing.
        //     ..If the condition isn’t satisfied (the lambda function returned false), wait() unlocks 
        //       the mutex and puts the thread in a blocked or waiting state. 

        //     ..When the condition variable is notified by a call to  notify_one() - from the 
        //       data-preparation thread:
        //       a) the data_processing thread wakes up (unblocks it)
        //       b) reacquires the lock on the mutex, and  checks the condition again:
        //            ..if the condition has been satisfied -> it returns from wait() with the mutex 
        //                                                                                   still locked
        //             ..If the condition hasn’t been satisfied -> the thread unlocks         the mutex and 
        //                                                                                        resumes waiting

        //(*) This is why you need the std::unique_lock rather than the std::lock_guard:
        //      ..the waiting thread must unlock the mutex while it’s waiting and lock it again
        //         afterward, and std::lock_guard doesn’t provide that flexibility
        //         (**) If the mutex remained locked while the thread was sleeping, the 
        //                  data-preparation thread wouldn’t be able to lock the mutex to add 
        //                  an item to the queue, and the waiting thread would never be able to 
        //                   see its condition satisfied.
 
        data_cond.wait(lk,[]{return !data_queue.empty();});

        data_chunk data=data_queue.front();
        data_queue.pop();

        lk.unlock();

        process(data);

        if(is_last_chunk(data))
            break;
    }
}


//----------------------------------------------------------------------
int main(int argc, char * argv[])
{
	cout << ">>>main - Start !" << endl;

	std::thread tprep (data_preparation_thread);
	std::thread tproc (data_processing_thread);

	tprep.join();
	tproc.join();

	cout << ">>>main - End !" << endl;

	return 0;
}

