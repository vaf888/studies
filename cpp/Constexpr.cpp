//------------------------------------------------
// description..: constexpr studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <array>
#include <type_traits>	//static_assert

using namespace std;

//----------------------------------------------------------------------
constexpr int five() {return 5;}

void constexpression1()
{
	cout << __PRETTY_FUNCTION__ << endl;
	std::array<int, five()> foo;
	foo[0]=1;
	cout << "foo[0]=" << foo[0] << endl;
}

constexpr int fibonacci(int n)
{
	int nMinus2=0; 
	(void)nMinus2;
	int nMinus1=1;

	for(auto i=0; i < n; ++i)
	{
		auto tmp = nMinus1;
		nMinus1 = (nMinus1 + nMinus2);
		nMinus2 = tmp;
	}

	return nMinus2;
}

constexpr int fibonacci2(int n)
{

	if (n<=1)
		return n;

	return fibonacci2(n-1) + fibonacci2(n-2);
}


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "__________________________________________________" << endl;
	constexpression1();

	cout << "__________________________________________________" << endl;
	// fibonacci - NO recursion
	cout << "fibonacci - NO recursion..." << endl;
	cout << "fibonacci(0)=" << fibonacci(0) << endl;
	static_assert(fibonacci(0) == 0);
	cout << "fibonacci(1)=" << fibonacci(1) << endl;
	static_assert(fibonacci(1) == 1);
	cout << "fibonacci(2)=" << fibonacci(2) << endl;
	static_assert(fibonacci(2) == 1);
	cout << "fibonacci(6)=" << fibonacci(6) << endl;
	static_assert(fibonacci(6) == 8);
	cout << "fibonacci(7)=" << fibonacci(7) << endl;	
	static_assert(fibonacci(7) == 13);

	cout << endl;
	cout << "__________________________________________________" << endl;
	// fibonacci - using recursion
	cout << "fibonacci - using recursion..." << endl;
	cout << "fibonacci2(0)=" << fibonacci2(0) << endl;
	static_assert(fibonacci2(0) == 0);
	cout << "fibonacci2(1)=" << fibonacci2(1) << endl;
	static_assert(fibonacci2(1) == 1);
	cout << "fibonacci2(2)=" << fibonacci2(2) << endl;
	static_assert(fibonacci2(2) == 1);
	cout << "fibonacci2(6)=" << fibonacci2(6) << endl;
	static_assert(fibonacci2(6) == 8);
	cout << "fibonacci2(7)=" << fibonacci2(7) << endl;	
	static_assert(fibonacci2(7) == 13);




	return 0;
}

