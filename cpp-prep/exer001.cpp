#include <iostream>
#include <cassert>

using namespace std;


int main()
{
	int n = 4, k = 2;
	cout << ++n << endl;  	//	5
	cout << n << endl;    	//	5

	cout << n++ << endl;  	// 5
	cout << n << endl;	  	// 6

	cout << -n << endl;		// -6
	cout << n << endl;		// 6

	cout << --n << endl;	// 5
	cout << n << endl;		// 5

	cout << n-- << endl;	// 5
	cout << n << endl;		// 4

	cout << n + k << endl;	// 6
	cout << n << endl;		// 4

	cout << k << endl;		// 2
	cout << n << k << endl;	// 42
	cout << n << endl;		// 4

	cout << " " << n << endl; 	// sp4
	cout << " n" << endl;		// spn
	cout << "\n" << endl;		// LF
	cout << " n * n = "; //CAREFUL!	// n * n = 16LF
	cout << n * n << endl;
	cout << 'n' << endl;	// 'n'

	return 0;
}