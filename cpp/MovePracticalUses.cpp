//------------------------------------------------
// description..: move semantics practical uses
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>
#include <vector>
#include <tuple>
#include <thread>

using namespace std;

/*
	A tuple ia a gneralization of a pair, an ordered set of heterogeneous elements.
	std::pair is a class template that provides a way to store two heterogeneous 
	objects as a single unit. 
	A pair is a specific case of a std::tuple with two elements. 
	Tuple - use case: keep a row of a database

	-std::tuple & std::pair are copy & move aware !!!!!!!
*/
//---------------------------------------------------------------------
//tuple to keep 3 elements
typedef std::tuple<int, int, int> i3Tuple;

auto getTuple000()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<i3Tuple> v;
	for(auto i{0}; i < 10; ++i)
	{
		v.emplace_back(i, i*2, i*3);
	}

	return v;
	
}

//---------------------------------------------------------------------
void displayIt(const std::vector<i3Tuple> & v)
{
	cout << ">>>>>vector content:" << endl;
	for(auto el:v )
	{
		cout << std::get<0>(el) << "; " << 
				std::get<1>(el) << "; " <<
				std::get<2>(el) << endl;
	}
	cout << endl;
}

//---------------------------------------------------------------------
struct foo
{
	int x=0;
};

//--- we can use copy & move with tuple
void tuple001()
{

	cout << __PRETTY_FUNCTION__ << endl;

	// will call the correct function on the foo
	// element, according to the use of copy or move !!!

	std::tuple<foo,int, char> t;
	auto tCopy = t;
		(void)tCopy;	// to avoid comp. warn.
	auto tMove = std::move(t);
		(void)tMove;	// to avoid comp. warn.
}

//---------------------------------------------------------------------
// Containers in std:
// -are move-aware
// -you can move entire content or only items insed the container

void containers()
{

	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<foo> v;
	auto vCopy = v;
		(void)vCopy;	// to avoid comp. warn.
	auto vMove = std::move(v);
		(void)vMove;	// to avoid comp. warn.

	// moving the temporary foo inside the vector
	// foo temp is rvalue expression, so push_back knows
	// that it can be moved - because it knows that
	// foo temp is about to expire
	v.push_back(foo{});

	// will do a copy, f is a lvalue
	foo f;
	v.push_back(f);

	// but, you can be explicit, and force the move (cast)
	v.push_back(std::move(f));	

}

//----------------------------------------------------------------------
/*
	-Some classes in the standard library can be only MOVED
	-they represent UNIQUE OWNERSHIP -> so, NO COPY AVAILABLE
	-e.g.: std::thread, std::unique_ptr, std::mutex, etc
*/
void moveOnly()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::thread t{
		[] {cout << "hello!!!" << endl;}
	};

	//ERROR comp. - try to copy it
	//auto tCopy =t;

	//but we can move it
	auto tMove = std::move(t);
	tMove.join();

	// idem for: unique_ptr, unique_lock, etc -> are move only !

}



//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "_______________________________" << endl;
	auto v = getTuple000();
	displayIt(v);

	cout << "_______________________________" << endl;
	tuple001();

	cout << "_______________________________" << endl;
	containers();

	cout << "_______________________________" << endl;
	moveOnly();

	return 0;

}

