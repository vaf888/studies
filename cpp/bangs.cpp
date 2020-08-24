//------------------------------------------------
// file.........: bangs.cpp
// description..: generate a tower of '#' chars - recursive
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

void bangs(int height)
{
	//cout << "DEBUG:" << "Starting ... s=" << s << endl;

	if (height == 0)
	{
		return; // base case
	}

	bangs(height -1);

	//for (int i:height)
	for (int i=0; i < height; ++i)
	{
		cout << "#";
	}
	cout << endl;

}

int main (int argc, char *argv[])
{
	int height = 6;
	message(std::to_string(height));
	bangs(height);

	//message(">>>>> End of Calls !!!");
}

