//------------------------------------------------
// description..: mutex
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <type_traits>
#include <list>
#include <thread>
#include <algorithm>	// for_each
#include <mutex>

using namespace std;


std::list<int> aList{};
std::mutex listMutex;


//----------------------------------------------------------------------
void displayIt()
{
	cout << "num items in the list=" << aList.size() << endl;
	cout << "items: ";

	for(int i:aList)
	{
		cout << i << " ";
	}

	cout << endl;

}

//----------------------------------------------------------------------
void addToList(int value)
{

	std::lock_guard<std::mutex> lg(listMutex);
	cout << "starting thread for n=" << value << endl;
	aList.push_back(value);

}


//----------------------------------------------------------------------
int main() 
{

	std::vector<std::thread> allThreads{};

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	for(auto i=0; i < 50; ++i)
	{
		std::thread t(addToList, (i+10));
		allThreads.push_back(std::move(t));
	}


	for(auto & t:allThreads)
	{
		if(t.joinable())
			t.join();
	}

	displayIt();
	

  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

