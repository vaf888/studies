//------------------------------------------------
// description..: lvalues - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>
#include <vector>


using namespace std;

/*
	lvalues:
	-called lvalues because the can appear on the left side of the
	 built in operator 

*/


void lvaluesA()
{
	int a;

	//called lvalues because the can appear on the left side of the
	//built in operator 
	a = 0; // I can take its address
	cout << "*&a=" << &a << endl;

	// the address of lvalues can be taken
	int * aPtr = &a;
	cout << "*aPtr=" << *aPtr << endl;

	//lvalues can bind to lvalue references
	int& a_ref = a;
	cout << "&a_ref=" << &a_ref << endl;

	// example of lvalues = NAME OF VARIABLES
	//a;
	cout << "&(a)=" << &a << endl;

	// example of lvalues = "member of object" expression
	struct foo { int _b;};
	foo f;
	//f._b;  // this is a lvalue I can take its address
	cout << "&(f._b)=" << &f._b << endl;



	// lvalue -> a function call returning a lvalue reference
	int & bar(); 	//returns a ref. to int -> lvalue - declaration
	//&bar(); 		// so, I can take its address
	cout << "&bar()" << &bar() << endl;
	bar() = 5;		// I can assign values to its return
}

int & bar() 
{ 
	static int i=0; 
	return i;
}

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "_______________________________" << endl;
	lvaluesA();

	return 0;

}

