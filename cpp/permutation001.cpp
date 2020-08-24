//------------------------------------------------
// file.........: permutation000.cpp
// description..: string permutation - procedural
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

	for( auto i=0; i < (int)(s.size()); ++i)
	{		
		for( auto j=i; j < (int)(s.size()); ++j)
		{	
			string sin {s};
			::swap(sin[i], sin[j]);
			cout << "permutation-" << ++numPermutations << ":[" << sin << "]" << endl;
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

