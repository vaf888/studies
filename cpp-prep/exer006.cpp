#include <iostream>
#include <cassert>

using namespace std;


//What is the output of the program below?


int main()
{
	int found = 0, count = 5;

	if (!found || --count == 0)
		cout << "danger" << endl;			// danger<LF>

	cout << "count = " << count << endl;	// count = 5<LF>
}