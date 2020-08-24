//------------------------------------------------
// file.........: power.cpp
// description..: base**n -> as (base**(n/2)*base(n/2)) recursion
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

void swap(char & c1, char & c2)
{
	char tmp = c1;
	c1 = c2;
	c2 = tmp;
}

int power(int base, int n)
{
	cout << "DEBUG: -> base=" << base << "; n=" << n << endl;

	if ( n == 0)
	{
		cout << "DEBUG: -> base case !!!" << endl;
		return 1;
	}
	else
	{
		if (n%2 == 0)
			return power(base, n/2)*power(base, n/2);
		else
			return power(base, n/2)*power(base, n/2)*base;
	}
}


int main (int argc, char *argv[])
{
	
	message();
	int base = 2;
	int n = 4;
	int res = power(base,n);
	assert(16 == res);

	message(">>>>> End of Calls !!!");
}

