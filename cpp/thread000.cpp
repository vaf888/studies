//------------------------------------------------
// file.........: thread000.cpp
// description..: threads - general studies
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

int main() 
{

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	std::vector<int> vec1{1, 2, 3, 4, 5};
	std::vector<int> vec2{6, 7, 8, 9, 10};
	std::vector<int> vec3{11, 12, 13, 14, 15};

	std::thread thread1{processVector, std::ref(vec1)};
	std::thread thread2{processVector, std::ref(vec1)};
	std::thread thread3{processVector, std::ref(vec1)};

	thread1.join();
	thread2.join();
	thread3.join();

  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

