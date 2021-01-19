#include <iostream>
#include <cassert>
#include <cstring> // memset

using namespace std;


//What is the output of the program below?




int main()
{

	//Remove all the unnecessary tests from the nested conditional statement 
	//below.
	
	float income;
	cout << "Enter your monthly income: ";
	cin >> income;

	if (income < 0.0)
		cout << "You are going farther into debt every month." << endl;
	else if (income >= 0.0 && income < 1200.00)
		cout << "You are living below the poverty line." << endl;
	else if (income >= 1200.00 && income < 2500.00)
		cout << "You are living in moderate comfort." << endl;
	else
		cout << "You are well off." << endl;

}