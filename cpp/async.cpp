//------------------------------------------------
// file.........: async.cpp
// description..: async. operations - future + promise - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>
#include <stdexcept>
#include <iterator>
#include <algorithm>  // for std::find
#include <utility>    // make_pair
#include <future>

using namespace std;

void message(string s)
{
  cout << endl << "________________________________" << endl;
  cout << ">>>>> " << s << endl;
}

/*
------------------------------------------------
*/
using namespace std;



/*
  std::async
  -this is a simplification of promise + future
  -returns future

  -std::async feels like an asynchronous function call. 
   Under the hood std::async is a task (*). One, which is extremely easy to use.


   (*) tasks:
   -Tasks behave like data channels. 
   -On one side, the sender sets a value. 
   -On the other side, the receiver picks up the value. 
   -The sender is called promise, the receiver - future. 
   -Or to say it in different words, the sender promises 
    to provide a value, which the receiver can pick 
    up in the future.


*/

/*
--------------------------------------------------
  main
--------------------------------------------------  
*/

int main()
{

  //using default policy
  //like: creates the promise + return future together + start the thread async.
  //      using the given launch policy - as param.
  std::future<std::string> future = 
  std::async([&]
  {
     std::cout << endl << "waiting 5 secs to generate results..." << endl;
     std::this_thread::sleep_for(std::chrono::seconds(5));
     return std::string("Some Message");
  });
 
  // thread to get the results from future
  auto consumer = 
  std::thread([&]
  {
     // get results via future
     std::cout << endl;
     std::cout << "result=" << future.get().c_str() << endl;;
  });
 
  consumer.join();  

  return 0;
}


