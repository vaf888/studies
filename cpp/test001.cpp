//------------------------------------------------
// file.........: movesemantics000.cpp
// description..: move semantics studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <string>
#include <iostream>  // std::cout, std::endl
using namespace std;


//-------------------------------------------------------------------
/*
	In this example, there is no user-defined default constructor. However, when an object x of class X is created, 
    a default constructor is needed. In this case, the compiler will implicitly declare a default constructor X::X（）{ },
    which is parameterless and has an empty body.
*/
class X
{

private:

int a;

};

//-------------------------------------------------------------------
/*
	However, if you have defined any constructors but a default constructor for a 
	class, the compiler will not implicitly declare a default constructor when one is needed. For example, the following code fails the compilation because no default constructor exists.

	Although example below works - when I define manually a default constructor, it has two drawbacks:
	i)  You have to manually define the default constructor, which requires more 
	    coding effort.
    ii) The user-defined default constructor is less efficient than the compiler 
        implicitly defined default constructor.

    (*) To address these two drawbacks, C++11 introduced the defaulted functions feature.	
*/
class Y
{

public:

	// to make the example work, I' ahve to define a default constructor

	// only a non default constructor defined - will hide the
	// compiler generated default constructor -> to fix, I will have to a add one
	// as above
	Y(int i)
	{

		a = i;
	}

private:
	int a;

};

//-------------------------------------------------------------------
/*

	Defaulted functions

	The C++11 standard introduced defaulted function declaration as a new form of 
	function declaration.

    To declare a defaulted function, you can append the “=default;” specifier to the 
    end of a function declaration. 
    The compiler will generate the default implementations for defaulted functions. 
    Explicitly defaulted functions can save your effort of defining those functions 
    manually. For example:
*/

class Z
{

public:

	Z()= default; // defaulted constructor

	Z(int i)
	{
		a = i;
	}

private:
	int a;

};

//-------------------------------------------------------------------
int main()
{
	X x; // fine, compiler implicitly defined default
	cout << "sizeof(x)=" << sizeof(x) << endl;
	X * x0 = new X();
	X * x1 = x0;
	cout << "sizeof(x0)=" << sizeof(x0) << endl;
	cout << "sizeof(x1)=" << sizeof(x1) << endl;

	//Y y; // comp error - default constructor hidden
	//cout << "sizeof(y)=" << sizeof(y) << endl;

	Z z; // fine, compiler implicitly defined default
	cout << "sizeof(z)=" << sizeof(z) << endl;




	return 0;
}





