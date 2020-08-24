//------------------------------------------------
// file.........: type-trait000.cpp
// description..: Type Traits - general studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>

using namespace std;

/*
//////////////////////////////////////////////
Type Traits:
	-this is a way to get information about types, so that
	 you can make decisions based on type capabilities


*/

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


//example-1:
// check if a type parameter is a char type
template<typename T>
struct is_char
{
	static const bool value = false;
};

//--- specializations ---
// ..the value member = true for characters (char & wchar)
//   and false, otherwise
template<>
struct is_char<char>
{
	static const bool value = true;
};

template<>
struct is_char<wchar_t>
{
	static const bool value = true;
};

// simple function using the trait
template<typename T>
void foo(T data)
{
	if(is_char<T>::value)
		cout << "!!! OK , this is a char" << endl;
	else
		cout << "!!! NOP , this is NOT a char" << endl;
}

template <typename T>
class Test000
{

public:
	Test000(T pValue)	: value(pValue)
	{
		assert(std::is_integral<T>::value);
	}

private:
	T value;
};

int main()
{
	message(">>>>> Traits !!!");

	char c='a';
	foo(c);

	int i=0;
	foo(i);

	// using traits from <type_traits>
	std::cout << std::boolalpha;

	bool res = std::is_floating_point<int>::value;
	cout << "std::is_floating_point<int>::value is " << res << endl;

	res = std::is_floating_point<float>::value;
	cout << "std::is_floating_point<float>::value is " << res << endl;

	res = std::is_floating_point<double>::value;
	cout << "std::is_floating_point<double>::value is " << res << endl;

	// using is_integral type trait
	Test000<int> t1(10);
	Test000

	<double> t2(10.0);

	message(">>>>> End of Calls !!!");

	return 0;
}

