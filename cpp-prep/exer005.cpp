#include <iostream>
#include <cassert>

using namespace std;


//What is the output of the program below?


int main()
{
	int i = 5, j = 6, k = 7, n = 3;
	cout << i + j * k - k % n << endl;	//46
	cout << i / n << endl;				// 5/3=1

	return 0;
}