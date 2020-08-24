//------------------------------------------------
// file.........: hanoy002.cpp
// description..: hanoy tower recursion
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
 
using namespace std;

static int discNumber=0;
static int totalDiscsInTarget=0;

void message(const string & s)
{
	cout << endl;
    cout << "__________________________________" << endl;
    cout << s << endl;
}

void message()
{
	cout << endl;
    cout << "__________________________________" << endl;
}

void displayMove(string from, string to)
{
	cout << "moving " << from << " ---> " << to << endl;
}

void towers(int n, string source, string target, string temp)
{
	// if this is a stack of size one, just move it: source -> target
	if(n == 1)
	{
		displayMove(source, target);
	}
	else
	{
		// move top n-1 items from source to temp, using target as temporary/spare
		towers(n-1, source, temp, target);

		// move top (left item = bigest one) - from source to target
		towers(1,source, target, temp);

		// move all the items in the temp to the target (using source as temporary/spare)
		towers(n-1, temp, target, source);
	}
}

void towersWrapper(int n)
{
	message();
	cout << "towers layout: Source - Target - Temp" << endl;
	
	discNumber=n; // first/biggest disk to be moved
	totalDiscsInTarget=0;

	towers(n, "source", "target", "temp");
}

int main (int argc, char *argv[])
{
	string line="";
	cout << "number of disks:";
	std::getline(cin, line);
	int n = stoi(line);

	towersWrapper(n);

	message(">>>>> End of Calls !!!");
}

