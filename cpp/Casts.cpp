//------------------------------------------------
// description..: casts - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <random>	//rnadom_device
#include <numeric>	//std::reduce
#include <chrono>   //time
#include <iomanip>  // set precision
#include <exception>
#include <ctime>
#include <typeinfo>	// typeid

/*
	c++ casts:
	static_cast<new_type>(expression)   	- checked at comp. type, similar to C cast

	dynamic_cast<new_type>(expression)  	- checked at comp. and runtime - for POLIMORPHIC TYPES (have virtual methods)
		..can only be used with pointers and references to classes (or with void*)
		..it allows:
		  -pointer upcast -> converting from pointer-to-derived to pointer-to-base
		  -downcast       -> convert from pointer-to-base to pointer-to-derived, for polymorphic 
		                     classes (those with virtual members)
		..requires Run-Time Type Information (RTTI) to keep track of dynamic types
		  (*) Run-time type information (RTTI) is a mechanism that allows the type of an object to be determined during program execution.

	reinterpret_cast<new_type>(expression)  - 
	..used to convert one pointer of another pointer of any type, no matter either the class is related to each other or not.
	..no checks are done to perform the cast - dangerous
	.. Returns a value of type new_type. 
	.. is a very special and dangerous type of casting operator
	.. Misuse of the reinterpret_cast operator can easily be unsafe. Unless the desired conversion is inherently low-level, you should use one of the other cast operators.


	const_cast <new_type> (expression)		- 
	..used to cast away the constness of variables
	..can be used to change non-const class members inside a const member function
	..can be used to pass const data to a function that doesn’t receive const
	..const_cast can also be used to cast away VOLATILE attribute.
*/

using namespace std;

class Base1
{
	void f(){}
};

class Deriv11 : public Base1
{
	void g(){}
};

class Deriv12 : public Base1
{
	void h(){}
};


//----------------------------------------------------------------------
void staticCastTest()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;


	Base1 * d1 = new Deriv11();

	Base1 * d2 = new Deriv12();

	Deriv11 * d3 = new Deriv11();


	Base1 * b1  = static_cast<Base1 *>(d1);

	cout << "type of d1=" << typeid(d1).name() << endl;  // non polym. -> prints Base1
	cout << "type of d2=" << typeid(d2).name() << endl;  // non polym. -> prints Base1
	cout << "type of d3=" << typeid(d3).name() << endl;  // non polym. -> prints Deriv11
	cout << "type of b1=" << typeid(b1).name() << endl;  // non polym. -> prints Base1

	static_cast<void>(*d1);
	static_cast<void>(*d2);
	static_cast<void>(*d3);
	static_cast<void>(*b1);
}

//----------------------------------------------------------------------
class Base 
{ 
	virtual void dummy() {} 
};

class Derived: public Base 
{ 
	int a; 
};

//----------------------------------------------------------------------
void dynamicCastTest()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	try 
	{
	    Base * pba = new Derived;
	    Base * pbb = new Base;
	    Derived * pd;


	    // this is OK - we can cast a derived(obj) to a derived
	    pd = dynamic_cast<Derived*>(pba);
	    if (pd==0) 
	    	cout << "Null pointer on first type-cast.\n";

	    //pbb is a base object - so, IMCOMPLET -> we can't cast it to a derived (complete) object
	    //this will return NULL
	    pd = dynamic_cast<Derived*>(pbb);
	    if (pd==0) 
	    {
	    	cout << "Null pointer on second type-cast.\n";
	    }

		Base * pbc = dynamic_cast<Base *>(pba);
	    if (pbc==0)
	    {	    
	    	cout << "Null pointer coud not convert derived to base.\n";
		} 

	} 
	catch (exception& e) 
	{
		cout << "Exception: " << e.what();
	}

	//cout << "type of d1=" << typeid(d1).name() << endl;  // non polym. -> prints Base1
}


//----------------------------------------------------------------------
void dynamicCastTest2()
{
	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;


	Base * b = nullptr;
	for(auto i=0; i<10; ++i)
	{
		b = (rand() % 2 == 0) ? new Derived : new Base;

		cout << "\n>>>>>typeid(*b)=" << typeid(*b).name() << endl;
	    Derived * pd = dynamic_cast<Derived*>(b);

	    //VIP: we can't cast a base object (IMCOMPLETE) to a derived - it does not have the derived content !!!
	    if (pd==0) 
	    	cout << "could not cast to a derived -> original typeid(*b)=" << typeid(*b).name() << endl;
	    else
	    	cout << "cast executed to derived succcessfully" << endl;
    
	}

	//cout << "type of d1=" << typeid(d1).name() << endl;  // non polym. -> prints Base1
}

//----------------------------------------------------------------------

// used to pass const data to a function that doesn’t receive const

int bar(int* ptr)
{
    return (*ptr + 10);
}

void constCastTest1()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	const int val = 10;
    const int *ptr = &val;

    //can't pass a const int to a non-const function - so remove the cast before
    int *ptr1 = const_cast <int *>(ptr);
    cout << bar(ptr1);

}

//----------------------------------------------------------------------

// It is undefined behavior to modify a value which is initially declared as const

int bar2(int* ptr)
{

	(*ptr) = (*ptr + 10); // WRONG !!!
    return (*ptr + 10);
}

void constCastTest2()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	const int val = 10;
    const int *ptr = &val;

    //can't pass a const int to a non-const function - so remove the cast before
    cout << ">>>>>val BEFORE=" << val << endl;;
    int *ptr1 = const_cast <int *>(ptr);

    int res = bar2(ptr1);

    cout << ">>>>>val AFTER=" << val << endl;
    cout << ">>>>>res=" << res << endl;;


}

//----------------------------------------------------------------------

// ..const_cast can also be used to cast away VOLATILE attribute.

void constCastVolatile()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;


	int a1 = 40;

	const int* b0 = &a1;
	cout << ">>>>>typeid of b0=" << typeid(b0).name() << '\n';	// PKi -> pointer to a constant int
    
    const volatile int* b1 = &a1;
    cout << ">>>>>typeid of b1=" << typeid(b1).name() << '\n'; // PVKi -> pointer to a volatile constant int

	int* c1 = const_cast <int *> (b1);    
    cout << "typeid of c1=" << typeid(c1).name() << '\n';	// Pi -> pointer to an int 

}

/*
//----------------------------------------------------------------------

// const_cast can be used to change non-const class members inside a const member function
class student
{
private:
    int roll;
public:
    // constructor
    student(int r):roll(r) {}
  
    // A const function that changes roll with the help of const_cast
    void fun() const
    {
        ( const_cast <student*> (this) )->roll = 5;
    }
  
    int getRoll()  { return roll; }
};
*/

//----------------------------------------------------------------------
void reinterpretCast1()
{
	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	int* p = new int(65);
    char* ch = reinterpret_cast<char*>(p);

    cout << *p << endl; 	// 65
    cout << *ch << endl; 	// A
    cout << p << endl;		// 0x5560479fd4a0
    cout << ch << endl;		// A
    cout << &ch << endl;	// 0x7ffcdd1ec668
}

/*
//----------------------------------------------------------------------

// Returns a hash code based on an address
unsigned short Hash( void *p ) 
{

   unsigned int val = reinterpret_cast<unsigned int>( p );

   cout << "val=" << val << endl;
   
   return ( unsigned short )( val ^ (val >> 16));
}


void reinterpretCast2()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	int a[20];

	for ( int i = 0; i < 20; i++ )
		cout << ">>>>>Hash=" << Hash( a + i ) << endl;

}
*/

//----------------------------------------------------------------------
int main()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	staticCastTest();

	dynamicCastTest();

	dynamicCastTest2()	;

	constCastTest1();
	
	constCastTest2();

	constCastVolatile();

	reinterpretCast1();

	//reinterpretCast2();

	return 0;
}

