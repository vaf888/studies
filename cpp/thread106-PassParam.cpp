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
void myHelloWorld(int timeToSleep, string name)
{
	auto this_id = std::this_thread::get_id();

	cout << "myHelloWorld - Start  - thread_id=" << this_id << endl;

	cout << "name=" << name << endl;
	cout << "timeToSleep=" << timeToSleep << endl;


}

//----------------------------------------------------------------------
int main() 
{

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	std::thread t(myHelloWorld, 60, "abcd");

	if(t.joinable())
		t.join();


  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

