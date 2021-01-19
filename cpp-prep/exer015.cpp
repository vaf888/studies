#include <iostream>
#include <cassert>
#include <cstring> // memset

using namespace std;


int main()
{

	//Rewrite the following code fragment so that it uses a "do...while..." 
	//loop to accomplish the same task.

	int n;

/*	
	cout << "Enter a non-negative integer: ";
	cin >> n;

	while (n < 0)
	{
		cout << "The integer you entered is negative." << endl;
		cout << "Enter a non-negative integer: ";
		cin >> n;
	}
*/

	do
	{
		cout << "Enter a non-negative integer: ";
		cin >> n;

		if( n < 0)
			cout << "The integer you entered is negative." << endl;

	}
	while (n<0);

}