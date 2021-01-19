#include <iostream>
#include <cassert>

using namespace std;


//What is the output of the program below?


int main()
{
	int n;

	cout << (n = 4) << endl;	// 4
	cout << (n == 4) << endl;	// 1
	cout << (n > 3) << endl;	// 1
	cout << (n < 4) << endl;	// 0
	cout << (n = 0) << endl;	// 0
	cout << (n == 0) << endl;	// 1
	cout << (n > 0) << endl;	// 0
	cout << (n && 4) << endl;	// 0  -> n is diff. of 4
	cout << (n || 4) << endl;	// 1  -> 4 is true (diff. 0)

	//! 	Called Logical NOT Operator. 
	//      Use to reverses the logical state of its operand. 
	//      If a condition is true, then Logical NOT operator will make false.
	cout << (!n) << endl;		// 1  -> n==0 -> so == FALSE -> !n = TRUE

	return 0;
}