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

static int numPermutations = 0;

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

void permut2(std::string & s, int start, int end)
{

	cout << "DEBUG: ->s=[" << s << "]" << endl;

	if ( start == end)
	{
		cout << "permutaion-" << ++numPermutations << "=[" << s << "]" << endl;
		return;
	}
	else
	{
		for( auto i=start; i < end; ++i)
		{	
			swap(s[i], s[start]);
			permut2(s, start+1, end);			
			swap(s[i], s[start]);
		}
	}
}

void permutWrapper(std::string s)
{
	cout << endl;
	cout << "DEBUG: permutWrapper - Start; s=[" << s << "]" << endl;
	//auto res = permut(s);
	int n = (int)(s.size());
	permut2(s, 0, n);
	cout << "DEBUG: permutWrapper - End" << endl;
}

int main (int argc, char *argv[])
{
	numPermutations = 0;
	string s1 = "abc";
	message("permutation for:" + s1);
	permutWrapper(s1);

	numPermutations = 0;
	s1 = "abcd";
	message("permutation for:" + s1);
	permutWrapper(s1);

	
//	string s2 = "abcd";
//	message("permutation for:" + s2);
//	permut(s2, 0, (int)(s2.size())-1);

	message(">>>>> End of Calls !!!");
}

