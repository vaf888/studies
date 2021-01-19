#include <iostream>
#include <cassert>
#include <cstring> // memset

using namespace std;


int main()
{

	//Answer the questions below concerning the following fragment of code.
	int n;

	cout << "Enter an integer: ";
	cin >> n;

	if (n < 10)
		cout << "less than 10" << endl;
	else if (n > 5)
		cout << "greater than 5" << endl;
	else
		cout << "not interesting" << endl;

	//a. What will be the output of the fragment above 
	//   if the interactive user enters the integer value 0 ?
	//   answer: less than 10

    //b. What will be the output of the fragment above 
    //   if the interactive user enters the integer value 15 ?
    //   answer:greater than 5

    //c. What will be the output of the fragment above if the 
    //   interactive user enters the integer value 7 ?
    //   answer:less than 10

    //d. What values for n will cause the output of the fragment above to 
    //   be "not interesting"?
    //   answer: none

}