//------------------------------------------------
// file.........: std-list.cpp
// description..: std::list - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
//#include <cstring>
#include <list>
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
void displayIt(std::list<T> & l)
{
	if (l.empty())
		return;

	for(T & item:l)
		cout << item << " ";
	cout << endl;
}

// template specialization for printing pairs
//template <>
template <typename T1, typename T2>
void displayIt(std::list<std::pair<T1, T2>> & l)
{
	if (l.empty())
		return;

	for(auto & p:l)
	{
		cout << "(" << p.first << ", " << p.second << ")" << endl;
	}
	cout << endl;
}

int main (int argc, char *argv[])
{

	std::list<int> l1 {1,2,3,4,5,6,7,8};
	displayIt(l1);

	cout << endl;
	cout << "list operations:" << endl;

	cout << "l1.front()=" << l1.front() << endl;
	cout << "l1.back()=" << l1.back() << endl;

	l1.pop_front();
	l1.pop_back();
	cout << "l1.front()=" << l1.front() << endl;
	cout << "l1.back()=" << l1.back() << endl;

	l1.erase(l1.begin());
	cout << "l1.front()=" << l1.front() << endl;
	cout << "l1.back()=" << l1.back() << endl;



	std::list<std::pair<int,string>> l2;
	l2.emplace_back(1,"aaaaa");
	l2.emplace_back(2,"bbbbb");
	l2.emplace_back(3,"ccccc");
	displayIt(l2);
/*	
	for(auto & p:l2)
	{
		cout << "(" << p.first << ", " << p.second << ")" << endl;
	}
*/
	//displayIt(l2);


	//message(">>>>> End of Calls !!!");
}

