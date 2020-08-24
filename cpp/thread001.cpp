//------------------------------------------------
// file.........: thread001.cpp
// description..: threads - using different callable objects
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

/*
void processVector(const std::vector<int>& vec) 
{
	auto this_id = std::this_thread::get_id();

	cout << "_____________________" << endl;
  	cout << ">>>>>processVector thread: Start... thread-id=" << this_id << endl;

 	// calculate the sum and print it
 	for(auto i=0; i < 10; ++i)
 		cout << "DEBUG: in processVector..." << endl;
  	cout << ">>>>>processVector thread: End!!!" << endl;
}
*/

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

int main() 
{
	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	//---using a callable obj = lambda expression---
	std::vector<int> vec1{1, 2, 3, 4, 5};
	std::thread thread1{[&]()
		{
			auto this_id = std::this_thread::get_id();

			cout << "_____________________" << endl;
		  	cout << ">>>>>processVector thread - via LAMBDA: Start... thread-id=" << this_id << endl;

		 	// calculate the sum and print it
		 	for(auto i=0; i < (int)vec1.size(); ++i)
		 		cout << "v[" << i << "]=" << vec1[i] << endl;
		  	cout << ">>>>>processVector thread: End!!!" << endl;
		}
	};

	//---another callable obj -> class with the overridden operator()
	std::thread thread2{MySimpleVector()};

	thread1.join();
	thread2.join();

  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

