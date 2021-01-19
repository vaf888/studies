#include <iostream>
#include <cassert>

using namespace std;


//What is the output of the program below?



/*
VIP VIP VIP:
However, cin considers a space (whitespace, tabs, etc) as a terminating 
character, which means that it can only display a single word 
(even if you type many words):

Example
string fullName;
cout << "Type your full name: ";
cin >> fullName;
cout << "Your name is: " << fullName;

// Type your full name: John Doe
// Your name is: John 
*/


int main()
{
	const int LENGTH = 21;

	char message[LENGTH];

	cout << "Enter a sentence on the line below." << endl;
	cin >> message;
	
	//Suppose that in response to the prompt, the interactive user types the following line and presses Enter:
	//Please go away.
	//What will the output of the code fragment look like?

	cout << message << endl;	// output -> Please  -> only first word - cin stops at a space
	
	return 0;
}