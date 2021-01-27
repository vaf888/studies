//------------------------------------------------
// description..: threads - passing parameters
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>
#include <thread>
#include <vector>
#include <algorithm>	// for_each

using namespace std;

/*

	Passing parameters to a thread function:
	-Passing parameters to a new thread in C++11 is as simple as passing the 
	 parameters to a callable object. 
	-It is important to note that the parameters are passed as local copies 
	 in the thread"s stack, so that they can be accessed by the running thread, 
	 even if the corresponding parameters of the function expect reference.
*/


//----------------- Case-1 ---------------------------------------------

//----------------------------------------------------------------------
void function1(const string & fileName)
{
	auto this_id = std::this_thread::get_id();
	cout << ">>>>>thread function1 - thread_id=" << this_id << endl;

	cout << "fileName=" << fileName << endl;
}


//----------------------------------------------------------------------
void oops1()
{

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>function oops1 - thread-id=" << this_id << endl;

	/*
		Case-1

		Even if the execute function1's thread receives a reference of std::string as a parameter, 
		the string is passed as const char* and converted only in the new thread 
		to std::string.

		In the example below, a pointer to the local variable buffer is passed to 
		the new thread, that waits for a std::string type parameter. 

		It is possible that the oops1 function completes before its conversion 
		from char* to std::string takes place -> The passed pointer becomes a 
		dangling pointer (١) and the thread behaviour will be undefied !!!

		To fix: use std::string(buffer) - to pass it by value

	*/

	char buffer[] = "test000.cpp";

	//BAD - passing pointer by value
	//std::thread t(function1, aFileName);

	//OK - build string , before calling function thread
	std::thread t(function1, std::string(buffer));

	t.detach();
}

//----------------- Case-2 ---------------------------------------------

//----------------------------------------------------------------------
void function2(string & pGreeting)
{
	auto this_id = std::this_thread::get_id();
	cout << endl;
	cout << ">>>>>thread function2 - thread_id=" << this_id << endl;

	cout << "received pGreeting=" << pGreeting << endl;

	pGreeting.assign("Hello World !!!!!!!!!!");

	cout << "changed pGreeting=" << pGreeting << endl;

}


//----------------------------------------------------------------------
void oops2()
{

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>function oops2 - thread-id=" << this_id << endl;

	/*
		Case-2

 		-where the passed parameter is copied, even if the intention was to send 
 		 a reference of the object whose value had to be changed by the thread


		To fix: 

	*/


	std::string greeting("Hello World");

	cout << "before thread call - greeting=" << greeting << endl;

	//BAD - copie of greeting var is passed - not a ref as expected by oops2
	std::thread t(function2, std::ref(greeting));

	cout << "after thread call - greeting=" << greeting << endl;

	if(t.joinable())
		t.join();
}


//----------------------------------------------------------------------
int main() 
{

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	oops1();

	oops2();

	cout << endl;
  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

