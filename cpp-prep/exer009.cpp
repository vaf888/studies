#include <iostream>
#include <cassert>
#include <cstring> // memset

using namespace std;


//What is the output of the program below?



/*
Suppose that the following code fragment is executed.
const int LENGTH = 21;
char message[LENGTH];
cout << "Enter a sentence on the line below." << endl;
cin.getline(message, LENGTH, '\n');
cout << message << endl;
a. Suppose that in response to the prompt, the interactive user types the following line and presses Enter:
Please go away.
What will the output of the code fragment look like?
b. Suppose that in response to the prompt, the interactive user types the following line and presses Enter:
Please stop bothering me.
What will the output of the code fragment look like?
*/


int main()
{
	//Suppose that the following code fragment is executed.
	const int LENGTH = 21;
	char message[LENGTH];
	
	//a) Suppose that in response to the prompt, the interactive user types 
	//the following line and presses Enter:
	//Please go away.
	//What will the output of the code fragment look like?
	memset(message,'\0', LENGTH);
	cout << "Enter a sentence on the line below." << endl;
	cin.getline(message, LENGTH, '\n');
	cout << message << endl;	// output = lease go away.

	//b) Suppose that in response to the prompt, the interactive user types the following line and presses Enter:
	//Please stop bothering me.
	//What will the output of the code fragment look like?

	//VIP: A null character ( '\0' ) is automatically appended to the written sequence 
	//     if n is greater than zero, even if an empty string is extracted

	memset(message,'\0', LENGTH);
	cout << "Enter a sentence on the line below." << endl;
	cin.getline(message, LENGTH, '\n');
	cout << message << endl;	// Please stop botherin(20+NULL chars)

	
	return 0;
}