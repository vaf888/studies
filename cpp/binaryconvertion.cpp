//------------------------------------------------
// file.........: countsetbits.cpp
// description..: count number of bits sets in number (recursion)
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
    cout << "__________________________________" << endl;
    cout << s << endl;
}

int countsetbits(int n)
{
	//cout << "DEBUG:" << "Starting ... s=" << s << endl;

	if (n == 0)
	{
		return 0;
	}

	return (n%2) + countsetbits(n/2);
}

int main (int argc, char *argv[])
{
	int res = 0;
	int n = 25;
	message(std::to_string(n));
	res = countsetbits(n);
	assert(3 == res);
	cout << "number of bits set=" << countsetbits(n) << endl;

	n = 7;
	message(std::to_string(n));	
	res = countsetbits(n);
	assert(3 == res);
	cout << "number of bits set=" << countsetbits(n) << endl;

	n = 1024;
	message(std::to_string(n));
	res = countsetbits(n);
	assert(1 == res);
	cout << "number of bits set=" << countsetbits(n) << endl;

	//message(">>>>> End of Calls !!!");
}

