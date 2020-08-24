//------------------------------------------------
// file.........: weak-pointer.cpp
// description..: smart pointers studies (weak pointer) 
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

// weak pointers:
// ..don't increment reference counter
// ..acess only via the associated shared pointer (via lock())
// ..common uses: to break circular references (e.g.: Manager X employee)
//   (make one of them weak pointer)

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
 	cout << ">>>>> displaying the shared pointer details ..." << endl;
	if(sharedPointer != nullptr)
 		cout << ">>>>> shared pointer content (object)=[" << sharedPointer->getData()<< "]" << endl;
	else
		cout << ">>>>> shared pointer content (object)=[null]" << endl;
	cout << ">>>>> shared pointer reference count=[" << sharedPointer.use_count()<< "]" << endl;
	
}

void display(std::weak_ptr<strc> & weakPointer)
{
	if(!weakPointer.expired())
	{
		// use weakPointer.lock() to get the associated sharedPtr to 
        //the weak pointer
 		cout << ">>>>> displaying the weak pointer details ..." << endl;
 		cout << ">>>>> shared pointer content (object)=[" << (weakPointer.lock())->getData()<< "]" << endl;
		cout << ">>>>> shared pointer reference count=[" << (weakPointer.lock    ()).use_count()<< "]" << endl;
 		cout << ">>>>> weak pointer content (object)=[ N/A - needs shared ptr associated to this weak pointer!]" << endl;
		cout << ">>>>> weak pointer reference count=[" << weakPointer.use_count()<< "]" << endl;
	}
	else
	{
		cout << ">>>>> weak pointer content (object)=[null]" << endl;
	}
}

void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

/*
void f(std::weak_ptr<strc>  p)
{
	message(">>>>> in function f");
    cout << "...pointed object content=" << p->getData() << endl;
	cout << "...weak pointer reference count=[" << p.use_count()<< "]" << endl;
}
*/

int main (int argc, char *argv[])
{
	message(">>>>>create a shared pointer + 5 copies of it!");
	std::shared_ptr<strc> sharedOne(new strc("one"));
	auto x1 = sharedOne;
	auto x2 = sharedOne;
	auto x3 = sharedOne;
	auto x4 = sharedOne;
	auto x5 = sharedOne;
	display(sharedOne);

	//create a weak pointer based on sharedOne
	message(">>>>>create weak ptr from shared - shared's ref. count not changed!");
	
	message(">>>>>shared pointer before weak pointer creation");
	display(sharedOne);
	auto weakOne = std::weak_ptr<strc>(sharedOne);
	display(weakOne);
	message(">>>>>shared pointer  AFTER the weak pointer creation -> no changes in the ref. count");
	display(sharedOne);

	// making copies of a weak pointer
	cout << endl;
	message(">>>>> copy of weak pointers...");
	message(">>>>>shared pointer BEFORE copies of weak pointer");
	display(sharedOne);
	message(">>>>>weak pointer BEFORE copies of weak pointer");
	display(weakOne);
	auto w1 = weakOne;
	auto w2 = weakOne;
	auto w3= weakOne;
	auto w4 = weakOne;
	auto w5 = weakOne;
	message(">>>>>shared pointer AFTER copies of weak pointer");
	display(sharedOne);
	message(">>>>>weak pointer AFTER copies of weak pointer");
	display(weakOne);

	message(">>>>> End of Calls !!!");
}

