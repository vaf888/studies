//------------------------------------------------
// file.........: decimalToBinary.cpp
// description..: convert decimal do binary (recursion)
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

int decimalToBinary(int n)
{
	//cout << "DEBUG:" << "Starting ... s=" << s << endl;

	if (n < 2)
	{
		return n;
	}

	return 10*(decimalToBinary(n/2)) + n%2;
}

int main (int argc, char *argv[])
{
	int res = 0;
	int n = 0;
	message(std::to_string(n));
	res = decimalToBinary(n);
	assert(0 == res);
	cout << "decimal in binary=" << res << endl;

	n = 1;
	message(std::to_string(n));
	res = decimalToBinary(n);
	assert(1 == res);
	cout << "decimal in binary=" << res << endl;

	n = 5;
	message(std::to_string(n));
	res = decimalToBinary(n);
	assert(101 == res);
	cout << "decimal in binary=" << res << endl;

	n = 7;
	message(std::to_string(n));
	res = decimalToBinary(n);
	assert(111 == res);
	cout << "decimal in binary=" << res << endl;

	n = 128;
	message(std::to_string(n));
	res = decimalToBinary(n);
	assert(10000000 == res);
	cout << "decimal in binary=" << res << endl;

	//message(">>>>> End of Calls !!!");
}

