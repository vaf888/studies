//------------------------------------------------
// description..: assync + future
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <chrono>
#include <ctime>
#include <thread>
#include <algorithm>	// for_each

#include <future>
#include <iostream>


using namespace std;

/*
-std::async  + future
  ..used to start an asynchronous task for which you don’t need the result right away
  ..Rather than giving you a std::thread object to wait on, std::async returns a std::future object, 
    which will eventually hold the return value of the function.
 ..When you need the return value, you just call get() on the future, and the thread blocks until  
    the future is ready and then returns the value. 
*/



//----------------------------------------------------------------------
std::string getTimeNow()
{
	auto timenow = 
      chrono::system_clock::to_time_t(chrono::system_clock::now()); 
  
    return ctime(&timenow); 
} 

//----------------------------------------------------------------------
int find_the_answer_to_ltuae()
{
	cout << ">>>>>find_the_answer_to_ltuae()... time=" << getTimeNow() << endl;
	std::this_thread::sleep_for (std::chrono::seconds(10));
	
	cout << ">>>>>find_the_answer_to_ltuae() - End ! -" << getTimeNow() << endl;
	return 12345;
}

//----------------------------------------------------------------------
void do_other_stuff()
{
	cout << ">>>>>do_other_stuff() ... time=" << getTimeNow() << endl;
	std::this_thread::sleep_for (std::chrono::seconds(5));
	cout << ">>>>>do_other_stuff() - End -" << getTimeNow() << endl;
}

//----------------------------------------------------------------------
int main(int argc, char * argv[])
{
    
	cout << ">>>>>main() ..." << endl;
	
	std::future<int> the_answer=std::async(find_the_answer_to_ltuae);    	

	do_other_stuff();   

	//waiting for the response - blocks while it is not available
	cout << "getting the response - via get()" << " - time=" << getTimeNow()<< endl;
	auto theAnswer =  the_answer.get();
	cout << "got the response - via get() - time=" << getTimeNow()<< endl;

	std::cout <<"The answer is " << theAnswer << endl;



	cout << ">>>>>main() - End !" << endl;

	return 0;

}
