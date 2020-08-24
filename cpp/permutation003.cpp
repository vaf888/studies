//------------------------------------------------
// file.........: permutation003.cpp
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

void permut3(string input, string output)
{
	//cout << "DEBUG: ->s=[" << input << "]" << endl;

	if ( input == "")
	{
		cout << "permutation-" << ++numPermutations << "=[" << output << "]" << endl;
		return;
	}
	else
	{
		int size = (int)(input.size());
		for( int i=0; i < size; ++i)
		{	
			//string next = output + input[i]; 

			string leftChoices = input.substr(0,i) + input.substr(i+1);

			permut3(leftChoices, output + input[i]);
			//permut3(leftChoices, next);
		}
	}

}

void permutWrapper(std::string s)
{
	cout << endl;
	cout << "DEBUG: permutWrapper - Start; s=[" << s << "]" << endl;
	string result="";
	permut3(s, result);
	cout << "DEBUG: permutWrapper - End" << endl;
}

int main (int argc, char *argv[])
{
	numPermutations = 0;
	string s1 = "abcd";
	message("permutation for:" + s1);
	permutWrapper(s1);

/*
	numPermutations = 0;
	s1 = "abcd";
	message("permutation for:" + s1);
	permutWrapper(s1);
*/
	
//	string s2 = "abcd";
//	message("permutation for:" + s2);
//	permut(s2, 0, (int)(s2.size())-1);

	message(">>>>> End of Calls !!!");
}

