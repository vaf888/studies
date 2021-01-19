#include <iostream>
#include <cassert>

using namespace std;


//What is the output of the program below?


int main()
{
	int n = 3;

	while (n >= 0)			// 9 4 1 0 one LF after each number
	{
		cout << n * n << endl;
		--n;
	}
	
	cout << n << endl;		//-1

	while (n < 4)
		cout << ++n << endl; // 0 1 2 3 4 (*) 1 lf after each #

	cout << n << endl;		// 4

	//while (n >= 0)			// 2,1,0,0..0 loop ?
	//	cout << (n /= 2) << endl;

	//fixing loop above
	while (n > 0)			// 2 1 0
		cout << (n /= 2) << endl;


	return 0;
}