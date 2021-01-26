//------------------------------------------------
// description..: threads - start a list of threads
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

int threadNum=0;

void myHelloWorld()
{
	auto this_id = std::this_thread::get_id();
	cout << "Hello World! - from function -> threadNum=" << ++threadNum << "; thread_id=" << this_id << endl;

}

int main() 
{
	std::vector<std::thread> vt{};
	constexpr int maxThreads=10;
	

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	/*
		---why I can't add the thread directly to the vector
		   I need move it ? ---

		a) std::thread is not copy-constructible (this constructor is deleted).
	    b) No two std::thread objects may represent the same thread of execution; 
	       std::thread is not CopyConstructible or CopyAssignable, although it is 
	       MoveConstructible and MoveAssignable. 
	*/

	for(auto i{0} ; i < maxThreads; ++i)
	{
		std::thread t(myHelloWorld);
		vt.push_back(std::move(t));

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	/* 
		--- required: join or dettach threads ---
		Once you’ve started your thread, you need to explicitly decide whether 
	    wait for it to finish (by joining with it—see section 2.1.2) or leave it 
	    to run on its own (by detaching it—see section 2.1.3). 
	    If you don’t decide before the std::thread object is destroyed, then your 
	    program is terminated (the std::thread destructor calls std::terminate()). 
	    It’s therefore imperative that you ensure that the thread is correctly 
	    joined or detached, even in the presence of exceptions.	
	*/

	std::this_thread::sleep_for (std::chrono::seconds(1));

	//for_each(vt.begin(), vt.end(), std::mem_fn(&std::thread::join));

	//for(auto t:vt)
	//{
	//		t.join();
	//}


	//for(auto i=0; i < maxThreads; ++i)
	//{
	//	auto &t = vt.back();
	//	t.join();
	//	vt.pop_back();
	//	
    //
	//}

	for(auto & t:vt)
	{
		if(t.joinable())
		{
			cout << ">>>joinning thread_id=" << t.get_id() << endl;
			t.join();
		}
	}


  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

