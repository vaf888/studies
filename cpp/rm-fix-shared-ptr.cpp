//------------------------------------------------
// description..: resource management - passing smart pointers
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>

using namespace std;


/*
	demangle executables:  

	nm a.out | c++filt  -> e.g. nm ../bin/rm-fix-shared-ptr | c++filt


	(*)  GNU nm lists the symbols from object files objfile…. If no object files are 
	     listed as arguments, nm assumes the file a.out. 

	(**) c++filt - demangling:
		 The c++filt program does the inverse mapping: it decodes (demangles) low-level 
		 names into user-level names so that they can be read. 

*/

struct Object
{
	virtual ~Object() = default;

	virtual int value() const 
	{
		return 1;
	}

};

struct Derived : Object
{
	virtual int value() const 
	{
		return 2;
	}
};


void useObject(const std::shared_ptr<Object> &o)
{
	cout << __PRETTY_FUNCTION__ << endl;
	std::cout << o->value() << endl;
}


// solution: don't use smart pointer , if you can
void useObjectOk(const Object &o)
{
	cout << __PRETTY_FUNCTION__ << endl;
	std::cout << o.value() << endl;
}


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << ">>>>>main() ..." << endl;

	

	// bad call - because it will create a temp Base class shared pointer
	//            (expensive - uses atomic loc to update reference counter) 
	//            required by the function useObject
	useObject(std::make_shared<Derived>());

	// solution: don't use smart pointer , if you can
	Derived d;
	useObjectOk(d);	


	cout << ">>>>>main() - End !" << endl;

	return 0;

}

