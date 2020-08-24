//------------------------------------------------
// file.........: std-vector.cpp
// description..: std::vector - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
//#include <cstring>
#include <vector>
#include <string>
//#include <typeinfo>
 
using namespace std;

void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

void message(const int v[], int n)
{
    cout << "__________________________________" << endl;
    cout << "content=";

    for(auto i=0; i < n; ++i)
    	cout << v[i] << " ";
    cout << endl;
}

template <typename T>
void displayIt(std::vector<T> & v)
{
	if (v.empty())
		return;

	for(T & item:v)
		cout << item << " ";
	cout << endl;
}

int main (int argc, char *argv[])
{
	std::vector<int> v1 {3,4,5,7,8};
	displayIt(v1);

	std::vector<string> v2 {"a","b","c"};
	displayIt(v2);

	//message(">>>>> End of Calls !!!");
}

