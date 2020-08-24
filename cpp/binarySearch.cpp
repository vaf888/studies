//------------------------------------------------
// file.........: binarySearch.cpp
// description..: binary search (precondition: input 
//                array is sorted) (recursion)
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

void message(const int v[], int n)
{
    cout << "__________________________________" << endl;
    cout << "content=";

    for(auto i=0; i < n; ++i)
    	cout << v[i] << " ";
    cout << endl;
}

int getSmallest(int v[], int n)
{
	int smallestIdx=0;
	for(int i=0; i < n; ++i)
	{
		if(v[i] < v[smallestIdx])
			smallestIdx=i;
	}

	return smallestIdx;
}

void selectionSort(int v[], int n)
{
	cout << endl << "DEBUG:" << "in selectionSort - begin ..." << endl;
	message(v, n);

	if ( n <= 1)
	{
		return;
	}

	int smallestIdx = getSmallest(v, n);
	std::swap(v[0], v[smallestIdx]);
	selectionSort(&v[1], --n);
}

bool binarySearch(int v[], int begin, int end, int searchFor)
{
	cout << "DEBUG: begin=" << begin << "; end=" << end << endl;

	if(begin > end)
		return false;

	int middle = (begin + end)/2;

	if (v[middle] == searchFor)
		return true;

	if(searchFor < v[middle])
		return binarySearch(v, begin, middle-1, searchFor);
	else
		return binarySearch(v, middle+1, end, searchFor);
}

bool binarySearchWrapper(int v1[], int v1Size, int searchFor)
{ 
	cout << endl;
	cout << "DEBUG: in binarySearchWrapper - searchFor = " << searchFor << endl;

	bool res = false;
	res = binarySearch(v1, 0, v1Size-1, searchFor);	
	cout << "DEBUG: in binarySearchWrapper - res = " << std::boolalpha << res << endl;
	return res;
}

int main (int argc, char *argv[])
{
	int a[] = {3,4,5,7,8};
	int sizeofA = sizeof(a)/sizeof(a[0]);
	message(a, sizeofA);

	bool res = binarySearchWrapper(a, sizeofA, 3);
	assert(true == res);

	res = binarySearchWrapper(a, sizeofA, 4);
	assert(true == res);

	res = binarySearchWrapper(a, sizeofA, 5);
	assert(true == res);

	res = binarySearchWrapper(a, sizeofA, 7);
	assert(true == res);

	res = binarySearchWrapper(a, sizeofA, 8);
	assert(true == res);

	res = binarySearchWrapper(a, sizeofA, 9);
	assert(false == res);


	//message(">>>>> End of Calls !!!");
}

