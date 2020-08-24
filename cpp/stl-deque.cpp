//------------------------------------------------
// file.........: stl-deque.cpp
// description..: deque - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>
#include <deque>

using namespace std;

/*
	deque - double ended queue:
	-same functionalites as in vector but
	 optimized for push & pop at the begin and end
	 (vector -> optimized for random access)
	-default container for stack and queue


*/

void showIt(deque<int> & d)
{
	for(auto item:d)
		cout << item << " ";

	cout << endl;
}

int main() 
{

  	deque<int> d1{9,8,7,6,5,4};
  	cout << endl << ">>>>> Initial deque content:" << endl;
  	showIt(d1);
  	d1.push_back(3);
  	d1.push_front(10);
  	cout << endl << ">>>>> after changes:" << endl;
  	showIt(d1);

  	//
	d1.push_back(2);
	d1.push_back(2);
	d1.push_back(2);
	d1.push_back(1);
  	cout << endl << ">>>>> before erase-remove:" << endl;
  	showIt(d1);

  	//using erase-remove idiom - to remove all 2's
  	// i) remove - shift all 2's to the end + returns the start of
  	//    the shifted area
  	// ii) erase: remove all items from the shifted area.
  	std::erase((std::remove(d1.begin(),d1.end(),2), d1.end());
  	cout << endl << ">>>>> after erase-remove:" << endl;
  	showIt(d1);
  	
	return 0;
}

