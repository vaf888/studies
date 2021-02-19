//------------------------------------------------
// description..: assync + future
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <chrono>
#include <ctime>
#include <vector>
#include <thread>
#include <cstdlib>

using namespace std;


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*
	pointer in interfaces:
	-should only be used to represent a single item
	-should passe it - if you NEED TO TEST it against NULL
 	(an optional item)
*/

//----------------------------------------------------------------------
//issue: user could send the wrong valu for count - e.g. bigger than the vector size
void printIntsBadIdea1(const int* s, int count)
{
	cout << __PRETTY_FUNCTION__ << endl;

	for(auto i{0}; i < count; ++i)
	{
		cout << s[i] << endl;
	}

}

//----------------------------------------------------------------------
//issue: also bad - expecting a 0 as the end of the vector
void printIntsBadIdea2(const int* s)
{
	cout << __PRETTY_FUNCTION__ << endl;
	for(; *s != 0; ++s)
	{
		cout << *s << endl;
	}

}

//----------------------------------------------------------------------
//solution: use a container
void printIntsSolution1(const std::vector<int>& v)
{
	cout << __PRETTY_FUNCTION__ << endl;
	for(auto i:v)
	{
		cout << i << endl;	
	}
}

//----------------------------------------------------------------------
// pass a pointer, as we need to test it if == NULL - item could be optional
void printIntsSolution2(const int* s)
{
	cout << __PRETTY_FUNCTION__ << endl;

	if (s != nullptr)
	{
		for(; *s != 0; ++s)
		{
			cout << *s << endl;
		}
	}
}

//----------------------------------------------------------------------
// pass a reference, when input is not optional (no need to test it against NULL)
// use references for things that are NOT OPTIONAL !!! - compiler does checks for you !
void printIntsSolution3(const std::string & s)
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "string content=" << s << endl;
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// RAII
bool complexCalculation()
{
	for(auto i{0}; i < 5 ; ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return false; // success during the calculation
}

class MyTimer
{

public:
	explicit MyTimer() : m_start{std::chrono::system_clock::now()}
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	~MyTimer()
	{
		std::cout <<
			std::chrono::duration<double>
			{
				std::chrono::system_clock::now() - m_start
			}.count() <<
			" s" << endl;
	}

	void operator()() const
	{
		cout << __PRETTY_FUNCTION__ << endl;
		cout << "() operator called !!!" << endl;
	}

private:
	const std::chrono::time_point<std::chrono::system_clock> m_start;

	//const std::chrono::time_point<std::chrono::system_clock> m_start =
	//	std::chrono::system_clock::now();

};

//----------------------------------------------------------------------
int raii001()
{
	cout << __PRETTY_FUNCTION__ << endl;

	const auto start = std::chrono::system_clock::now();

	// run a complex calculation
	if( complexCalculation())
	{
		const auto stop = std::chrono::system_clock::now();	
		std::cout <<
			std::chrono::duration<double>{stop-start}.count() <<
			" s" << endl;

		return EXIT_FAILURE;
	}
	else
	{
		const auto stop = std::chrono::system_clock::now();	
		std::cout <<
			std::chrono::duration<double>{stop-start}.count() <<
			" s" << endl;

		return EXIT_SUCCESS;

	}
}

//----------------------------------------------------------------------
int raii002()
{
	cout << __PRETTY_FUNCTION__ << endl;

	MyTimer t;

	t();

	if( complexCalculation())
	{
		return EXIT_FAILURE;
	}
	else
	{
		return EXIT_SUCCESS;
	}
}

//----------------------------------------------------------------------
int main()
{
	cout << ">>>>>main() ..." << endl;

	const int ints1[] = {1,2,3,4,5};
    printIntsBadIdea1(ints1, 5);
	
	const int ints2[] = {1,2,3,4,5,0};
    printIntsBadIdea2(ints2);

	std::vector<int> v1 = {1,2,3,4,5,0};
    printIntsSolution1(v1);

    printIntsSolution2(ints2);

	printIntsSolution3(std::string{"abcdef ghi"});  

	//--- RAII ---
	raii001();

	raii002();


	cout << ">>>>>main() - End !" << endl;

	return 0;

}

