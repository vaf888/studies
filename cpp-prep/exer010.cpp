#include <iostream>
#include <cassert>
#include <cstring> // memset

using namespace std;


//What is the output of the program below?


int main()
{
	const int LENGTH = 21;
	char message[LENGTH];
	int i;

	cout << "Enter a sentence on the line below." << endl;
	cin >> message[0];
	
	i = 0;
	while (i < LENGTH - 1 && message[i] != '\n')
	{
		++i;
		cin >> message[i];
	}

	message[i] = '\0'; // Replace '\n' if that was read.
	
	// Otherwise replace the last character read.
	cout << message << endl;
	
	return 0;
}