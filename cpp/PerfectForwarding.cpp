//------------------------------------------------
// description..: perfect forwarding
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>
#include <vector>
#include <map>
#include <utility>



using namespace std;

/*
	perfect forwarding (using in templates parameters):
	-binds to everything and also remembers the value category of the passed object
	-allows writing more generic codes - avoiding repetitions (overloads)
*/

// Examples:

/*
	In the Dictionary class below we want to add a method class
	to add the string m_words in the vector, using move, when possible

	Possible solutions:

	a) BAD - add 2 overloads for LVALUE and RVALUE -> bad DUPLICATIONS
	   hard to maitain
	   e.g.:
	   void add (const std::string & s);	//for copy
	   void add (std::string && s);			//for move

	b) NOT TOO BAD - "pass-by-value movie" idiom
	   cons: not optimal - has extra moves - not good for libraries,
	         as you don't know how users will call/use it.
	   e.g.:
       void add(std::string s)
       {
			m_words.push_back(std::move(s));
       }

	c) best solution: using perfect forwarding
	   -we write the function as a template and pass the parm string as a T&& = forward reference
	   E.g.:
	   template <typename T>
	   void add(T&& s)
	  	{
	  		// this will copy s - if an lvalue received or move s,
	  		// if an rvalue was received as parameter.
			m_words.push_back(std::forward<T>(s));
	  	}


*/

class Dictionary
{

private:
	std::vector<std::string> m_words;

public:
	   template <typename T>
	   void add(T&& s)
	  	{
			cout << __PRETTY_FUNCTION__ << endl;
			cout << "s=" << s << endl;

	  		// this will copy s - if an lvalue received or move s,
	  		// if an rvalue was received as parameter.
			m_words.push_back(std::forward<T>(s));
	  	}

		template <typename T>
	   	void add1(T&& s);
};

template <typename U>
void Dictionary::add1(U&& s)
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "s=" << s << endl;

	// this will copy s - if an lvalue received or move s,
	// if an rvalue was received as parameter.
	m_words.push_back(std::forward<U>(s));
}

// 


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	//desired usage for the Dictionary class:
	cout << "___________________________________" << endl;
	Dictionary d;
	std::string s{"Hello World I"};
	d.add(s); // will use copy

	cout << "___________________________________" << endl;
	d.add(std::string{"Hello World I"}); // will use move

	cout << "___________________________________" << endl;
	Dictionary d1;
	std::string s1{"Hello World I"};
	d.add1(s1); // will use copy

	cout << "___________________________________" << endl;
	d.add1(std::string{"Hello World I"}); // will use move	

	
	return 0;
}

