//------------------------------------------------
// file.........: palindrome.cpp
// description..: check if string is a palindrome (e.g.: anna)
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

bool isPalindrome(std::string s)
{
	//cout << "DEBUG:" << "Starting ... s=" << s << endl;

	int size = (int)(s.size());

	if (size <= 1)
	{
		cout << ">>>>> IS a palindrome !!!!!" << endl;		
		return true; // base case
	}

	if(s[0] != s[size-1])
	{
		cout << ">>>>> IS NOT a palindrome !!!!!" << endl;		
		return false;
	}

	//cout << "DEBUG:" << "s=" << s << endl;
	string newString (s.substr(1,size-2));
	//cout << "DEBUG:" << "newString=" << newString << endl;

	return isPalindrome(newString);
}

int main (int argc, char *argv[])
{
	string s1 = "anna";
	message(s1);
	assert(isPalindrome(s1) == true);

	s1 = "civic";
	message(s1);
	assert(isPalindrome(s1) == true);

	s1 = "kayak";
	message(s1);
	assert(isPalindrome(s1) == true);

	s1 = "ana";
	message(s1);
	assert(isPalindrome(s1) == true);

	s1 = "anua";
	message(s1);
	assert(isPalindrome(s1) == false);

	s1 = "repaper";
	message(s1);
	assert(isPalindrome(s1) == true);

	s1 = "rotator";
	message(s1);
	assert(isPalindrome(s1) == true);

	s1 = "noon";
	message(s1);
	assert(isPalindrome(s1) == true);

	s1 = "a";
	message(s1);
	assert(isPalindrome(s1) == true);

	//message(">>>>> End of Calls !!!");
}

