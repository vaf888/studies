//------------------------------------------------
// file.........: thread-RAII.cpp
// description..: threads + join using RAII idiom
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

using namespace std;

class MySimpleVector
{
public:
	MySimpleVector()
	{
		vec_ = {100,200,300,400};
	}

	void operator()()
	{
		auto this_id = std::this_thread::get_id();

		cout << "_____________________" << endl;
	  	cout << ">>>>>processVector via operator(): Start... thread-id=" << this_id << endl;

	 	// calculate the sum and print it
	 	for(auto i=0; i < (int)vec_.size(); ++i)
	 		cout << "v[" << i << "]=" << vec_[i] << endl;
	  	cout << ">>>>>processVector thread: End!!!" << endl;
	}

private:
	std::vector<int> vec_;

};

class ThreadGuard
{
private:
	std::thread& t;

public:
	explicit ThreadGuard(std::thread& tp):t(tp)
	{
		auto this_id = std::this_thread::get_id();
		cout << ">>>>>ThreadGuard() constructor - Start... thread-id=" << this_id << endl;

	}

	~ThreadGuard()
	{
		cout << ">>>>> ~ThreadGuard() - Starting..." << endl;

		if(t.joinable())
		{
			t.join();
		}
	}

	//non-copyable
	ThreadGuard(ThreadGuard const&)=delete;
	ThreadGuard& operator=(ThreadGuard const&)=delete;
};

struct Func
{
	int i;

	Func(int ip):i{ip}{}

	void operator()()
	{
		auto this_id = std::this_thread::get_id();

		cout << ">>>>>in Func : Start... thread-id=" << this_id << endl;
		for(auto j=0; i < 100000; ++i)
			j=j;
		cout << ">>>>>in Func : End !!!" << endl;

	}
};

/*
-When the execution of the current thread reaches the end 
 of f, the local objects are destroyed in reverse order 
 of construction. 
 Consequently, the ThreadGuard object, threadGuard, is 
 destroyed first, and the thread is joined with, in the 
 destructor. 
 This even happens if the function exits because doSomething throws an exception.

The destructor of thread_guard in listing 2.3 first tests to see if the std::thread object is joinable() before calling join(). This is important, because join() can be called only once for a given thread of execution, so it would be a mistake to do so if the thread had already been joined.

The copy constructor and copy-assignment operators are marked =delete to ensure that they’re not automatically provided by the compiler. Copying or assigning such an object would be dangerous, because it might then outlive the scope of the thread it was joining. By declaring them as deleted, any attempt to copy a thread_guard object will generate a compilation error. See appendix A, section A.2, for more about deleted functions. 

*/

void doSomething()
{
	cout << ">>>>> in doSomething() - Start..." << endl;

	// do sth in the current thread
	for(auto i=0; i < 100000; ++i)
		;
	cout << ">>>>> in doSomething() - End!!!" << endl;
}

int main() 
{
	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	int someLocalState=0;

	Func myFunc(someLocalState);
	std::thread t(myFunc);

	ThreadGuard threadGuard(t);

	doSomething();

	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

