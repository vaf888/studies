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

//----------------------------------------------------------------------
class MyList
{


public:
	void addToList(int value);
	void displayIt();


private:
	std::list<int> m_aList{};
	std::mutex m_mutex;	
};

//----------------------------------------------------------------------
void MyList::displayIt()
{
	cout << "num items in the list=" << m_aList.size() << endl;
	cout << "items: ";

	m_aList.sort();

	for(int i:m_aList)
	{
		cout << i << " ";
	}

	cout << endl;

}

//----------------------------------------------------------------------
void MyList::addToList(int value)
{

	std::lock_guard<std::mutex> lg(m_mutex);
	cout << "starting thread for n=" << value << endl;
	m_aList.push_back(value);

}


//----------------------------------------------------------------------
int main() 
{

	std::vector<std::thread> allThreads{};

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	MyList * myListPtr = new MyList();

	for(auto i=0; i < 50; ++i)
	{
		// Create a thread using member function
		std::thread t(&MyList::addToList, myListPtr, (i*10));
		allThreads.push_back(std::move(t));
	}


	for(auto & t:allThreads)
	{
		if(t.joinable())
			t.join();
	}

	myListPtr->displayIt();
	
	delete myListPtr;

  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

