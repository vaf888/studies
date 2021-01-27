//------------------------------------------------
// description..: threads - creating a detached thread (deamon)
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

#include <sys/types.h>
#include <unistd.h>		// get process id
#include <sys/types.h>

using namespace std;


//----------------------------------------------------------------------
void myHelloWorld()
{

	//generatin an exception
	for(auto i{0}; i < 3; ++i)
	{
		cout << "i=" << i << endl;
		std::this_thread::sleep_for (std::chrono::seconds(60));
	}
}

//----------------------------------------------------------------------
int main() 
{

	
	cout << "_____________________" << endl;
	pid_t pid = getpid();
	cout << ">>>>>processId..:" << pid << endl;

	auto this_id = std::this_thread::get_id();	
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	cout << ">>>>>starting new thread..." << endl;
	std::thread t(myHelloWorld);
	cout << "Hello World! - thread_id=" << t.get_id() << endl;

	cout << ">>>>>detaching..."<< endl;	
	t.detach();
	
	cout << ">>>>>main - end !!!" << endl;	

	return 0;
}

