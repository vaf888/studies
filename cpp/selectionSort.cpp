//------------------------------------------------
// file.........: selectionSort.cpp
// description..: selection sort (recursion)
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

bool isEqual(int v1[], int v1Size, int v2[], int v2Size)
{
	if (v1Size != v2Size)
		return false;

	if(v1Size==0)
		return true;

	for(int i=0; i < v1Size; ++i)
	{
		if(v1[i] != v2[i])
			return false;
	}

	return true;
}

int main (int argc, char *argv[])
{
	int a[] = {7,5,3,8,4};
	int sizeofA = sizeof(a)/sizeof(a[0]);
	int res[] = {3,4,5,7,8};
	int sizeofRes = sizeof(res)/sizeof(res[0]);

	selectionSort(a, sizeofA);

	message(a, sizeofA);
	assert(true == isEqual(a, sizeofA, res, sizeofRes));

	//message(">>>>> End of Calls !!!");
}

