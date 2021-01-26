//------------------------------------------------
// file.........: thread100.cpp
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

class MyClass
{
public:
	void operator()()
	{
		cout << "Hello World! - from operator overloading !" << endl;		
	}


};

void myHelloWorld()
{
	cout << "Hello World! - from function" << endl;

}

int main() 
{

	auto this_id = std::this_thread::get_id();
	cout << "_____________________" << endl;
	cout << ">>>>>main thread: Start... thread-id=" << this_id << endl;

	std::this_thread::sleep_for (std::chrono::seconds(1));

	//using lambda to define the thread's function !
	std::thread thread1
	{
		[](){cout << "Hello World! - from lambda" << endl;}
	};

	std::this_thread::sleep_for (std::chrono::seconds(2));

	//using a function, to start the thread
	std::thread thread2(myHelloWorld);


	//std::this_thread::sleep_for (std::chrono::seconds(2));
	//using class + operating overloading
	MyClass myClass;
	std::thread thread3(myClass);

		

	thread1.join();
	thread2.join();
	thread3.join();	
	
  	cout << ">>>>>main thread: End !!!" << endl;

	return 0;
}

