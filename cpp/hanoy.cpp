//------------------------------------------------
// file.........: hanoy.cpp
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

void displayMove(int from, int to)
{
	cout << "moving " << from << " -> to:" << to << endl;
}

void towers(int n, int from, int to, int temp)
{
	// if this is a stack of size one, just move it: from -> to
	if(n == 1)
	{
		displayMove(from, to);
	}
	else
	{
		// move top n-1 items from -> temp, using to as temp
		towers(n-1, from, temp, to);

		// move top (left item = bigest one) - from -> to
		towers(1,from, to, temp);

		// move all the items in the temp -> to (using from as temp)
		towers(n-1,temp, to, from);
	}
}

void towersWrapper(int n)
{
	int from = 1;
	int to = 2;
	int temp = 3;

	message();
	cout << "from=1 - to=2 - temp=3" << endl;

	towers(n, from, to, temp);
}

int main (int argc, char *argv[])
{
	
	int n = 3;
	towersWrapper(n);

	message(">>>>> End of Calls !!!");
}

