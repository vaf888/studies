//------------------------------------------------
// file.........: conditionalVariable.cpp
// description..: std::conditional_varialbe + concurrence studie
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <condition_variable>
#include <thread>

using namespace std;

/*
------------------------------------------------
*/
void message(const string s="")
{
  cout << endl << "________________________________" << endl;
  cout << ">>>>> " << s << endl;
}

/*
------------------------------------------------
*/
//--- global variables ---
std::mutex aMutex;
std::condition_variable condVar;

bool dataReady{false}; // this is the shared resource

/*
------------------------------------------------
*/
//consumer
void waitingForWork()
{
  //cout << "DEBUG: in waitingForWork() I - dataReady=" << dataReady << endl;
  cout << ">>>>>Waiting..." << endl;
  //cout << "DEBUG: in waitingForWork() II - dataReady=" << dataReady << endl;

  std::unique_lock<std::mutex> uniqueLock{aMutex};
  //cout << "DEBUG: in waitingForWork() III - dataReady=" << dataReady << endl;

  //The wait workflow:
  //1) In the initial processing of wait, the thread locks 
  //the mutex and then checks the predicate []{ return dataReady;}
  //..If the call of the predicated evaluates to
  //  true: the thread continues its work.
  //  false: condVar.wait() unlocks the mutex and puts 
  //         the thread in a waiting (blocking) state
  //
  //2) If the condition_variable condVar is in the 
  //   waiting state and gets a notification or a 
  //   spurious wakeup the following steps happen.
  //   ..The thread is unblocked and will reacquire 
  //     the lock on the mutex. 
  //   ..The thread checks the predicate.
  //   ..If the call of the predicated evaluates to
  //     true: the thread continues its work.
  //     false: condVar.wait() unlocks the mutex and 
  //            puts the thread in a waiting (blocking) 
  //            state.
  condVar.wait(uniqueLock, []{return dataReady;});

  cout << ">>>>>Running..." << endl;
}

/*
------------------------------------------------
*/
//producer
void setDataReady()
{
  cout << "DEBUG: in setDataReady() I - dataReady=" << dataReady << endl;
  {
    //lock_guard - in RAII mode - unlock will be called at the end of the block
    //lock_guard - acquires the lock
    std::lock_guard<std::mutex> lg(aMutex);
    dataReady = true;
  }
  cout << "DEBUG: in setDataReady() II - dataReady=" << dataReady << endl;

  cout << ">>>>>Data prepared..." << endl;
  //at this point, the aMutex was unlocked !
  condVar.notify_one();
}

/*
------------------------------------------------
*/
int main()
{
  //thread t1(waitingForWork);
  //thread t2(setDataReady);

  thread t1(setDataReady);
  thread t2(waitingForWork);

  t1.join();
  t2.join();

  cout << endl;

  return 0;
}



