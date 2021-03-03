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

	-A rvalue represents a temporary object that has no identity.
	-We can assume that an rvalue is ready to give away ownership of its resources

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


//
//------------- Rvalues - cont . ---------------------------------------
//
//---------------------------------------------------------------------

std::vector<int> getVector()
{
	std::vector<int> v0{1,2,3,4,5};
	return v0;
}

void rValuesB()
{
	// -the lvalue v0 is a std::vector which owns a dynamic allocated buffer
	//  that stores ower values
	std::vector<int> v0{1,2,3,4,5};

	// if we try to allocate a new vector v1 using the lvalue v0
	// we are forced to perform a COPY of v0 buffer into v1
	auto v1 = v0;
	(void)v1; // to avoid comp. warning var not used

	//but - we can force the use of move
	// std::move cast v0 (lvalue) to a rvalue
	// std::vector has a MOVE CONSTRUCTOR - that will be used
	// to contruct objectos from a RVALUE (as in the case, when we use the cast)
	auto v00 = std::move(v0);
	(void)v00; // to avoid comp. warning var not used

	// we can mimic std:move - as it is only a cast
	//https://en.cppreference.com/w/cpp/utility/move
	auto v10 = static_cast<std::vector<int>&&>(v1); // similar to std:move(v1)
	(void)v10; // to avoid comp. warning var not used	

	// IMPORTANT:
	// using v0 or v1 (sources for the move) after the move can
	// lead to undefined behaviour !!!


	//another option: use std::move to MOVE the content of v0's buffer to
	//                the destination vector, and release v0
	// can we do this safetly ?
	// -> Only when the source is a rvalue -> because it has NO IDENTITY
	//    and it is about to "expire"
	
	// Why this work ?
	// because std:vector is moveable (has a move constructor) 
	// moves content of source (a rvalue returned by the function)
	// to the newly created vector - v2.

	auto v2 = getVector();
	(void)v2; // to avoid comp. warning var not used

	// NOW using MOVE the vector returned by getVector = rvalue = about to expire
	// we can, via std::mov , steal the ownership of the returned vector and
	// give it away to the vector v3
	
}

//----------------------------------------------------------------------
// showing that std::move is only a cast - no operation is performed
void noopExample()
{
	std::vector<int> v0{1,2,3,4,5};
	std::move(v0); // this is a NO-OP just a cast

	// so a can safely access v0 after the move (cast) as the resource is still valid
	v0.size();

	//but, if I perform an operation with the rvalue generated by the std:movie
	// as below (constructor) - the move operation will be executed
	//and, after that, the source object v0 will be left in a undefined state, we
	// should not use it anymore !!!
	auto v1 = std::move(v0);
	//vo.size() // error -> v0 is in an invalid state now - can't be used !
	(void)v1; // to avoid comp. warning var not used
}


//----------------------------------------------------------------------

// returning from function - NO NEED OF std::movie - compiler is optimized 
// already to the return the best way

//VIP: this only applies for local variables and NOT FOR MEMBER VARIABLES and CLASSES


std::vector<int> returnExample()
{
	std::vector<int> v0{1,2,3,4,5};

	//WRONG: return std::move(v0); -> see example below !!!!!!!!!
	// It would DISABLE Return Value Optimization (RVO)

	//correct
	return v0;
}


//----------------------------------------------------------------------
//VIP: this only applies for local variables and NOT FOR MEMBER VARIABLES and CLASSES
//e.g.:

struct foo
{
	std::vector<int> v;

	std::vector<int> moveV()
	{
		// ERROR -> similar to: return this->v;
                            // and it is not a local variable (this is a member variable)
                            // so RVO will no be applied
		//return v; 
		
		//CORRECT: in this case, use std::move to provide a move
                             //functionality for a data member
		return std::move(v);
	}
};



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

