//------------------------------------------------
// file.........: mutex001.cpp
// description..: mutex - studies
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
#include <mutex>

using namespace std;

std::mutex locker;
int global=0;

void inc(std::string callName) 
{
	locker.lock();

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>thread " << callName << " : Start... thread-id=" << this_id << endl;

	global = global + 1; // protecting shared resource
	locker.unlock();
}

//---using lock_gard (c++17) to unlock mutex automaticaly
void incWithGuard(std::string callName) 
{
	// lock the mutex via lock_guard
	std::lock_guard g(locker);	

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>thread " << callName << " : Start... thread-id=" << this_id << endl;

	global = global + 1; // protecting shared resource
}

int main() 
{
	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	std::thread thread1{inc,"FIRST THREAD CALLED"};
	std::thread thread2{inc,"SECOND THREAD CALLED"};

	//using lock
	std::thread thread3{incWithGuard,"FIRST LockGuard THREAD CALLED"};
	std::thread thread4{inc,"SECOND LockGuard THREAD CALLED"};

	thread1.join();
	thread2.join();
	thread3.join();
	thread4.join();

  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

