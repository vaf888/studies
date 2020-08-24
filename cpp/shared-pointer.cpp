//------------------------------------------------
// file.........: shared-pointer.cpp
// description..: smart pointers studies (shared pointer) 
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include "strc.h"
#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <algorithm>	// std::move
#include <memory>		// smart pointers 
 
using namespace std;

// display value of object pointed by the smart pointer
void display(std::shared_ptr<strc> & sharedPointer)
{
	if(sharedPointer != nullptr)
 		cout << ">>>>> shared pointer content (object)=[" << sharedPointer->getData()<< "]" << endl;
	else
		cout << ">>>>> shared pointer content (object)=[null]" << endl;
	cout << ">>>>> shared pointer reference count=[" << sharedPointer.use_count()<< "]" << endl;
	
}

void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

void f(std::shared_ptr<strc>  p)
{
	message(">>>>> in function f");
    cout << "...pointed object content=" << p->getData() << endl;
	cout << "...shared pointer reference count=[" << p.use_count()<< "]" << endl;
}

void deleter(const strc * o)
{
	message(">>>>> deleter - function");
	if(o)
	{
		cout << "..object data=[" << o->getData() << "]" << endl;
		delete o;
	}
	else
	{
		cout << "..object pointed by the smart pointer is null !!!" << endl;
	}
}

int main (int argc, char *argv[])
{
	message(">>>>> shared smart pointer - sharedOne");
	std::shared_ptr<strc> sharedOne(new strc("one"));
	display(sharedOne);

	message(">>>>> shared smart pointer - sharedTwo");
	auto sharedTwo = std::make_shared<strc>("two");
	display(sharedTwo);
	
	// reset -> case I: used to destroy the object when ref count reaches =0
	message(">>>>>reset() - destroy object pointed - when ref. reaches 0");
	sharedOne.reset();	
	display(sharedOne);

	// reset -> case II: destroy actual object and point to a new one 
	// reset sharedTwo to point to object "three"
	message(">>>>>reset() - destroy  actual pointed obj. and point to a new one");
	cout << ">>>>> sharedTwo - before reset" << endl;
	display(sharedTwo);
	//sharedTwo.reset(*(std::make_shared<strc>("three")));
	sharedTwo.reset(new strc("three"));
	cout << ">>>>> sharedTwo - after reset" << endl;
	display(sharedTwo);

	// create serveral shared pointers do the same object
	auto x1 = sharedTwo;
	display(x1);
	auto x2 = sharedTwo;
	display(x2);
	auto x3 = sharedTwo;
	display(x2);
	auto x4 = sharedTwo;
	display(x4);
	auto x5 = sharedTwo;
	display(x5);
	cout << ">>>>> sharedTwo - after the copies (x1..x5)" << endl;
	display(sharedTwo);

	// reset all pointer x
	x1.reset();
	x2.reset();
	x3.reset();
	x4.reset();
	x5.reset();
	cout << ">>>>> sharedTwo - after the reset of the copies (x1..x5)" << endl;
	display(sharedTwo);

	// passing shared pointer by VALUE (so a copy will be done) to a function
	cout << ">>>>> sharedTwo -  before function call by value" << endl;
	display(sharedTwo);
	f(sharedTwo);
	cout << ">>>>> sharedTwo -  after function call by value" << endl;
	display(sharedTwo);

	// using a custom delete - as function
	cout << ">>>>> using custom delete - via function" << endl;
	shared_ptr<strc> sharedFour(new strc("four"), deleter);
	display(sharedFour);

	// using a custom delete - via lambda
	cout << ">>>>> using custom delete - via lambda" << endl;
	shared_ptr<strc> sharedFive(new strc("five"), 
									[](strc * o)
									{
										message(">>>>> deleter - lambda");
										if(o)
										{
											cout << "..object data=[" << o->getData() << "]" << endl;
											delete o;
										}
										else
										{
											cout << "..object pointed by the smart pointer is null !!!" << endl;
										}
									}
								);
	display(sharedFive);

	message(">>>>> End of Calls !!!");
}

