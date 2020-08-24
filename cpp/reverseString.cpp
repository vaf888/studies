//------------------------------------------------
// file.........: reverseString.cpp
// description..: reverse string (recursion)
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

string reverseString(string s)
{
	//cout << "DEBUG:" << "Starting ... s=" << s << endl;

	if (s=="")
	{
		return "";
	}

	string sb = s.substr(1, s.size()-1);
	string res = reverseString(sb) + s[0];
	cout << "res=" << res << endl;
	return res;
}

int main (int argc, char *argv[])
{
	string res {""};
	string s {"abc"};
	message(s);
	res = reverseString(s);
	assert("cba" == res);
	cout << "converted string=" << res << endl;


	//message(">>>>> End of Calls !!!");
}

