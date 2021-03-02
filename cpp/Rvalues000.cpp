//------------------------------------------------
// description..: Rvalues - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>
#include <vector>


using namespace std;

/*
	Rvalues:
	-CAN NOT APPEAR on the left side of the built-in assignment operator
	-we CAN'T take its address 
*/

//---------------------------------------------------------------------
int bar()
{

	// test only - check if below does not generate warning!
	int a=0;
	//(void)a;
	//or
	static_cast<void>(a);

	return 5;
}

//---------------------------------------------------------------------
void rValuesA()
{
	// Rvalues -> CAN NOT APPEAR on the left side of the built-in assignment operator
	//5 = 0;   	-> !!! COMP ERROR !!!
	//bar() = 0 -> !!! COMP ERROR !!! -> bar returns an int (not a ref to int)

	//The address of Rvalues CAN'T be taken !!!
	//&5;		-> !!! COMP ERROR !!!
	//&bar(); 	-> !!! COMP ERROR !!!

	//Rvalues DO NOT bind to lvalue references
	//int & lvalue_ref0 = 5;		-> !!! COMP ERROR !!!
	//int & lvalue_ref1 = bar();	-> !!! COMP ERROR !!!

	// VIP: there is a distinction between Lvalue ref and const Lvalue ref +
	//      bind to rvalue
	//BUT: exception case - you can bind a CONST lvalue ref to a Rvalue !!!
	const int& const_lvalue_ref0 = 5; // OK !!!!!
		static_cast<void>(const_lvalue_ref0);	// // to avoid unused var warning

		//Rvalues bind to Rvalues references - introduced in c++11
	int && rvalue_ref0 = 5;
		(void)rvalue_ref0;		// to avoid unused var warning
	int && rvalue_ref1 = bar();
		(void)rvalue_ref1;		// to avoid unused var warning
		// or
		static_cast<void>(rvalue_ref1);

	//examples of Rvalues -> numeric literals
	//5;
	//10.33f;

	// examples of Rvalues -> bult-in arithmetic expressions:
	// 5 + 10*3;

	// examples of Rvalues -> function calls returning NON-REFERENCES
	bar();

}

//----------------------------------------------------------------------
// references cases :
// You can overload a function with a Rvalue ref and a Lvalue ref

void foo(int&)
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "non-cont LVALUE reference !!!" << endl;
}

void foo(int&&)
{
	cout << __PRETTY_FUNCTION__ << endl;
	(void)0; // tests only
	cout << "RVALUE reference !!!" << endl;
}

//VIP: a CONST LVALUE reference parm - anything can bind to it !!!
void bar(const int&)
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "CONST LVALUE reference !!!" << endl;
}


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "_______________________________" << endl;
	rValuesA();


	//references + overloads Rvalue ref and Lvalue ref
	//the compiler will select the best match according to
	//the informed arguments
	cout << "_______________________________" << endl;
	int a =0;
	foo(a); // a = lvalue ref -> calls foo(int&)

	cout << "_______________________________" << endl;
	foo(5); // 5 = rvalue ref -> calls foo(int&&)

	cout << "_______________________________" << endl;
	bar(a); // a = lvalue ref -> but calls bar(const int&) 
	
	cout << "_______________________________" << endl;	
	bar(5); // 5 = rvalue ref -> also calls bar(const int&) - special case

	return 0;

}

