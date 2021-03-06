//------------------------------------------------
// description..: move into containers - best practices
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>
#include <vector>
#include <map>



using namespace std;

/*
	moving into containers -> can be a huge performance hit !!!
*/

//---------------------------------------------------------------------
//Example1: read large file contents into a string, then put string in a vector
std::string readLargeFile(int i)
{
	//tests only
	return std::to_string(i);
}

auto largeFiles()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<std::string> files;

	// small optimization to avoid realocations at the beginning
	files.reserve(10);

	//case-I -> using copy - low performance as files are huge !!!
	for( int i=0; i < 10; ++i)
	{
		std::string s = readLargeFile(i);

		//do some processing in s

		// not using move here will force the string to be copied to the vector
		files.push_back(s);
	}

	//case-II - using move - much more efficient way - does not create temp copies
	for( int i=0; i < 10; ++i)
	{
		std::string s = readLargeFile(i);

		//do some processing in s

		files.push_back(std::move(s));

		//VIP: can't use s after the move - because s will have invalid content !!!
	}

	//(void)tCopy;	// to avoid comp. warn.
}

//---------------------------------------------------------------------
//map with container inside

std::vector<int> getMultiples(int i)
{
	std::vector<int> v;
	for(int j=0; j<i; ++j)
		v.push_back(j*j);

	return v;
}

// passing the map by valeu - so, we can assume that the 
// function will consume+store it somewhere
void consumeMultiples(std::map<int, std::vector<int>> m)
{
	(void)m; //to avoid comp. warning
	return;
}


void mapWithContainer()
{

	std::map<int, std::vector<int>> mapContainer1;

	//BAC - using copy 
	for(int i=0; i<10; ++i)
	{
		auto vMultiples = getMultiples(i);

		//here we are forcing the compiler to user a copy
		//because vMultiples is a LVALUE !
		mapContainer1[i] = vMultiples;

	}

	std::map<int, std::vector<int>> mapContainer2;

	//OK - using MOVE
	for(int i=0; i<10; ++i)
	{
		// mow getMultiples(i) is a RVALUE, so move will be used !!!
		mapContainer2[i] = getMultiples(i);
	}

	//calling consumeMultiples - using move - to avoid copies
	consumeMultiples(std::move(mapContainer2));
 
}

//----------------------------------------------------------------------

//providing 2 overloads as below:
//-PROS: convenient for users can selec copy or move, according to needs
//-CONS: very cumbersome to develop this to all functions

//Unfortunately, it is very cumbersome to provide multiple overloads for everything, this is why the 
//pass-by-value move idiom exists.


void bar(const std::vector<int>& v){(void)v;} // parm. by const ref
void bar(std::vector<int>&& v){(void)v;}		  // parm by rvalue reference

//better approach: 

void vectorRef()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<int> v;

	// we can chose pass v to var by & or &&

	//by ref
	bar(v);

	//by rvalue ref
	// use this if we don't need to use v anymore, after the std::move
	// because it will be moved to bar - so, after, will have invalid content
	cout << "before move - v.size()=" << v.size() << endl;
	bar(std::move(v));
	cout << "after move - v.size()=" << v.size() << endl;
}

//----------------------------------------------------------------------

/*
-goal: to avoid generating overloads for functions as below:
	 void bar(const std::vector<int>& v); // parm. by const referece (copy)
     	void bar(std::vector<int>&& v);      // parm. by rvalue reference(move)
     (*) I will need to provide a combination of overloads for all the parameters 2**N
-allows users run calls using copy or move semantics without generating
     overloads.
    -See exemplo below: passByValueMoveIdiom()
*/

struct Person
{
	std::string m_name;

	Person() = default;
	

	Person(std::string name) : m_name{std::move(name)}
	{
	}

	void setName(std::string name)
	{
		m_name = std::move(name);
	}

	void displayIt()
	{
		cout << "m_name=" << m_name << endl;
	}
};

/*
	By taking "sink arguments" by value and then unconditionally moving the,
	we can achieve close-to-optional behavior:

	a) in setValue -> if user pass a LVALUE, we will have:
	   1 copy (in constructor) to generate the function param. + 1 move in setName body

	b) in setValue -> if user pass a RVALUE, we will have:
	   1 move (in constructor) to generate the function param. + 1 move in setName body

	(*) this is not optimal (we have 1 extra move in both cases) - but this is
	    OK, because MOVES are way cheaper (pointers swaps) then copies !
	(**) But the extra moves are better than generating 2**N overloads, if
	     not using this technique

	
*/

void passByValueMoveIdiom()
{

	cout << __PRETTY_FUNCTION__ << endl;	

	Person p{};

	//using copy - lvalue parm
	//when setName is called - in setName the parameter will be "copied"
	//using copy in the constructor (because the parm is a LVALUE)
	std::string s{"string 001"};
	p.setName(s);
	p.displayIt();

	//using move - rvalue parm
	//in setValue - the parameter will be "copied" using MOVE in the constructor
	//as we are sending an RVALUE param.
	p.setName(std::string{"string 002"});
	p.displayIt();
}



//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "_______________________________" << endl;
	largeFiles();

	cout << "_______________________________" << endl;
	mapWithContainer();

	cout << "_______________________________" << endl;
	vectorRef();

	cout << "_______________________________" << endl;
	passByValueMoveIdiom();

	return 0;
}

