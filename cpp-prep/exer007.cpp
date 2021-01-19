#include <iostream>
#include <cassert>

using namespace std;


//What is the output of the program below?


int main()
{
	const int LENGTH = 21;

	char message[LENGTH];

	cout << "Enter a sentence on the line below." << endl;
	cin >> message;
	
	//Suppose that in response to the prompt, the interactive user types the following line and presses Enter:
	//Please go away.
	//What will the output of the code fragment look like?

	cout << message << endl;	// output -> Please go away.
	
	return 0;
}