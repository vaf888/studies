//------------------------------------------------
// file.........: unique-pointer.cpp
// description..: smart pointers studies (unique pointer) 
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
void display(std::unique_ptr<strc> & uniquePointer)
{
	if(uniquePointer != nullptr)
 		cout << ">>>>> unique pointer content (object)=[" << uniquePointer->getData()<< "]" << endl;
	else
		cout << ">>>>> unique pointer content (object)=[null]" << endl;
}

void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

void f(std::unique_ptr<strc> & p)
{
	message(">>>>> in function f");
    cout << "...pointed object content=" << *p << endl;
    cout << "...pointed object content=" << p->getData() << endl;
	strc * rp1 = p.get();
    cout << "...pointed object content=" << rp1->getData() << endl;
    cout << "...unique pointer=" << *p << endl;

}

int main (int argc, char *argv[])
{
	message(">>>>> unique smart pointer - uniqueOne");
	std::unique_ptr<strc> uniqueOne(new strc("one"));
	display(uniqueOne);

	message(">>>>> unique smart pointer - uniqueTwo");
	auto uniqueTwo = std::make_unique<strc>("two");
	display(uniqueOne);
	display(uniqueTwo);
	
	// reset - uses:
    // ..to distroy an object
	// ..to replace by a new one

	// case-I: reset + replace by a new object
    //         unique pointer will point to a new object,
    //         and the former obj. will be destroyed.
	message(">>>>> reset + replace by a new object!!!");
	uniqueOne.reset(new strc("three"));
	display(uniqueOne); // uniqueOne points to the new objc "three" ("one" - ther former obj. -  was distroyed"
	display(uniqueTwo);
	
	// case-II: reset + distroy objected pointed by the unique pointer
	message(">>>>> reset() - distroy object pointed by the unique pointer !!!");
	uniqueOne.reset();
	display(uniqueOne);
	display(uniqueTwo);
	
	message(">>>>> move a unique pointer - WE CAN'T COPY IT !!!");
	uniqueOne = std::make_unique<strc>("one");
	auto uniqueThree = std::move(uniqueOne);
	display(uniqueOne);
	display(uniqueTwo);
	display(uniqueThree);
	
	message(">>>>> release - releases smart pointer control of the object (no destructor called)!!!");
	uniqueOne = std::make_unique<strc>("one");
	strc * beforeRelease = &(*uniqueOne);
	cout << ">>>>>object before release=" << *beforeRelease << endl;
    uniqueOne.release();
	display(uniqueOne);
	cout << ">>>>>object after release=" << *beforeRelease << endl;
	
	message(">>>>> CAN'T PASS unique pointer BY VALUE as parm function!!!");
	// error: will try to use the copy constructor - that is deleted
    //        unique_ptr(const unique_ptr&) = delete;

	//VIP: BUT YOU CAN PASS IT BY REFERENCE !!!
	uniqueOne = std::make_unique<strc>("one");
	f(uniqueOne);
	display(uniqueOne);
	
	message(">>>>> End of Calls !!!");


}

