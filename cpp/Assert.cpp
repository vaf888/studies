//------------------------------------------------
// description..: testing asserts
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>


using namespace std;
/*

	The assert macro comes with a small performance cost that is incurred each time the assert condition is checked.

	display error & calls abort - if assert failed 

	asserts should (ideally) never be encountered in production code (because your code should already be thoroughly tested)

	Consequently, many developers prefer that asserts are only active in debug builds.

	C++ comes with a way to turn off asserts in production code. 
	 -> If the macro NDEBUG is defined, ---> the assert macro gets disabled.

	Some IDEs set NDEBUG by default as part of the project settings for release configurations

	asserts should have no side effects -- that is, the program should run the same with and without the assert

	Also note that the abort() function terminates the program immediately, without a chance to do any further cleanup (e.g. close a file or database). Because of this, asserts should be 
	used only in cases where corruption isn’t likely to occur if the program terminates unexpectedly.




Static_assert -> c++11

-A static_assert is an assertion that is checked at compile-time rather than at runtime, 
 with a failing static_assert causing a compile error.

A static_assert takes the following form:

static_assert(condition, diagnostic_message)


*/


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	
	bool isValid = true;

	//assert(isValid == true);


	//IF isValid == false will trigger the assert !
	//VIP: the string after && below, is always TRUE !!!!
	assert(isValid && "is valid is false!!!!!!");

	//--- static assert ---
	static_assert(sizeof(long) == 8, "long must be 8 bytes");
	static_assert(sizeof(int) == 4, "int must be 4 bytes");

	//static_assert(sizeof(int) == 99, "int must be 4 bytes"); // COMP ERROR HERE !!!	
	
	return 0;
}

