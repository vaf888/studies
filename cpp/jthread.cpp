//------------------------------------------------
// file.........: jthread.cpp
// description..: jthread - general studies - c++20
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

using namespace std;


void processVector(const std::vector<int>& vec) 
{
 	// calculate the sum and print it
 	while(auto i=0; i < 1000000; ++i)
 		cout << "DEBUG: in processVector..."
}

int main() 
{
	cout << "_____________________" << endl;
  	cout << ">>>>>main thread: Start..." << endl;

	 std::vector<int> vec1{1, 2, 3, 4, 5};
	 std::vector<int> vec2{6, 7, 8, 9, 10};
	 std::vector<int> vec3{11, 12, 13, 14, 15};
	 processVector(vec1); // takes A amount of time
	 processVector(vec2); // takes A amount of time
	 processVector(vec3); // takes A amount of time

  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

