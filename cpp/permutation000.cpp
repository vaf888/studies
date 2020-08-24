//------------------------------------------------
// file.........: permutation000.cpp
// description..: string permutation - recursive
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

void swap(char & c1, char & c2)
{
	char tmp = c1;
	c1 = c2;
	c2 = tmp;
}

void permut(std::string & s, int left, int right)
{
	int numPermutations=0;

	cout << endl << "TESTS ONLY: s=" << s << endl;
	cout << "TESTS ONLY: left=" << left << endl;
	cout << "TESTS ONLY: right=" << right << endl;

	if(left == right)
	{
		cout << "permutation-" << ++numPermutations << ":[" << s << "]" << endl;
	}
	else
	{	
		std::string pivot {s[left]};
		cout << "TESTS ONLY: pivot=" << pivot << endl;

		for( auto i=left; i <= (int)(s.size()); ++i)
		{		
			::swap(s[i], pivot[0]);
			permut(s, left+1, right);		
		}
	}
}

int main (int argc, char *argv[])
{
	string s1 = "abc";
	message("permutation for:" + s1);
	permut(s1, 0, (int)(s1.size())-1);
	
//	string s2 = "abcd";
//	message("permutation for:" + s2);
//	permut(s2, 0, (int)(s2.size())-1);

	message(">>>>> End of Calls !!!");
}

