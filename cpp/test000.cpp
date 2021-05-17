//------------------------------------------------
// file.........: movesemantics000.cpp
// description..: move semantics studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <string>
#include <iostream>  // std::cout, std::endl
#include <array>

using namespace std;


int func1(int x, bool y)
{
	(void) y;
	return x;
}

/*
error -> return type not used to differentiate overloads !
double func1(int x, bool y)
{
	(void) y;
	return static_cast<double>(x);
}
*/

void func001()
{
		//malloc
	int * arr = static_cast<int*>(malloc (10 * sizeof(int)));
	arr[0]=127;
	arr[9]=127;
	delete arr;

	int * arr2 = static_cast<int *>(calloc(100, sizeof(int)));
	arr2[0]=127;
	arr2[9]=127;
	delete arr2;



}

int main()
{

	cout << "________________________________-" << endl;
	int res1 = func1(1, true);
	(void) res1;

	double res2 = func1(2, false);
	(void)res2;

	cout << "________________________________-" << endl;
	short s = -4;
	unsigned short us = s;
	cout << ">>>>>s=" << s << endl;
	cout << ">>>>>us=" << us << endl;

	



	/*
	//malloc
	int * arr = static_cast<int*>(malloc (10 * sizeof(int)));
	arr[0]=127;
	arr[9]=127;

	int * ptSize = arr - 1;
	cout << "arr[0]=" << arr[0] << "; size=" << *ptSize << endl;
	*/

	//func001();

	cout << "________________________________" << endl;
	/*
	int array[][] ={{1,2}, {3,4}, {5,6}};
	for(int i=0; i < sizeof(array))
	*/
	string sarray[]={"aa", "bbbb", "cccccc", "b", "dddddddddddddddd"};
	cout << "sizeof(sarray)/sizeof(sarray[0])....=" << sizeof(sarray)/sizeof(sarray[0]) << endl;
	cout << "sizeof(sarray)=" << sizeof(sarray) << endl;
	cout << "sizeof(sarray[0])=" << sizeof(sarray[0]) << endl;
	cout << "sarray[0]=" << sarray[0] << endl;
	cout << "sizeof(sarray[4])=" << sizeof(sarray[4]) << endl;
	cout << "&sarray[0]=" << &sarray[0] << endl;
	cout << "&sarray[1]=" << &sarray[1] << endl;
	cout << "&sarray[2]=" << &sarray[2] << endl;

	const char * carray[]={"aa", "bbbb", "cccccc", "b", "dddddddddddddddd"};

	cout << "sizeof(carray)/sizeof(carray[0])....=" << sizeof(carray)/sizeof(carray[0]) << endl;
	cout << "sizeof(carray)=" << sizeof(carray) << endl;
	cout << "sizeof(carray[0])=" << sizeof(carray[0]) << endl;
	cout << "sizeof(carray[4])=" << sizeof(carray[4]) << endl;

	cout << "&carray[0]=" << &carray[0] << endl;
	cout << "&carray[1]=" << &carray[1] << endl;
	cout << "&carray[2]=" << &carray[2] << endl;

	for(auto item : carray)
	{
		cout << "item=" << item << endl;
	}

	cout << "sizeof(char)=" << sizeof(char) << endl;
	cout << "sizeof(char *)=" << sizeof(char *) << endl;
	cout << "sizeof(int)=" << sizeof(int) << endl;
	cout << "sizeof(int *)=" << sizeof(int *) << endl;
	cout << "sizeof(double)=" << sizeof(double) << endl;
	cout << "sizeof(double *)=" << sizeof(double *) << endl;
	cout << "sizeof(string)=" << sizeof(string) << endl;
	cout << "sizeof(string *)=" << sizeof(string *) << endl;
	cout << "sizeof(string * [1])=" << sizeof(string * [1]) << endl;
	cout << "sizeof(string[1])=" << sizeof(string[1]) << endl;


	std::array<std::string,3> a3 = { std::string("aaaaaaa"), "bbbbbbbbbbb" };

	cout << "________________________________" << endl;
	std::array<std::array<int,3>,2> a =
	{
		{ {{11,12,13} }, 
	    { {4,5,6}} }
	};

	for(int i=0; i < 2; ++i)
	{
		for(auto j=0; j < 3; ++j)
		{
			cout << "item=" << a[i][j] << endl;
		}
	}


	return 0;
}





