//------------------------------------------------
// description..: threads - using RAII assure join during exceptions
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


//----------------------------------------------------------------------
class ThreadGuard
{

	std::thread & m_thread;

public:
	ThreadGuard(std::thread & t) : m_thread(t) {}

	~ThreadGuard()
	{
		cout << ">>>>>ThreadGuard destructor called !!!" << endl;

		if(m_thread.joinable())
			m_thread.join();
	}

	ThreadGuard(const ThreadGuard & other) = delete;
	ThreadGuard & operator=(const ThreadGuard & other) = delete;
};

//----------------------------------------------------------------------
void myHelloWorld()
{
	auto this_id = std::this_thread::get_id();
	cout << "Hello World! - from function  - thread_id=" << this_id << endl;

	//generatin an exception
	int * i = nullptr;
	*i=99;
}

//----------------------------------------------------------------------
int main() 
{

	{
		auto this_id = std::this_thread::get_id();
		cout << "_____________________" << endl;
		cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

		std::thread t(myHelloWorld);
		ThreadGuard tg(t);

		cout << ">>>>>ending protected block via RAII" << endl;
	}

  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

