//------------------------------------------------
// file.........: templates000.cpp
// description..: templates - general studies
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
Templates:

a0) utilities:
	..nm ./templates000  -> show symbol names
	  (*) look for generated instantions: nm ./templates000 | grep -i stream
	      -stream = base template name

    ..to display correct name ( it is mangled in nm utility):
      c++filt _ZN6streamIcE1fEv
      result -> stream<char>::f()
      (*) _ZN6streamIcE1fEv is the mangled name


a0) Template instantiation
    -The process of instantiating a template (that is, of conceptually 
     "filling in" the template parameters with concrete types and values) 
     is the responsibility of the compiler, in general. 
    -It is possible to manually control it to optimize separate compilation. 
     For instance, this program:
     	Vector<int> a(10);



a) Class Template Specialization
   -In some cases it is possible to override the template-generated code 
    by providing special definitions for specific types -> This is called 
    template specialization. The following example defines a template class 
    specialization for template class stream. (see example-1)
	e.g.:
	template <> !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	class stream<char> !!!!!!!!!!!!!!!!!!!!!!!!
	{
		public:
			void f() { cout << "stream<char>::f()"<< endl ;}
	} ;

	(*) the original class template is:
	    template <class T> !!!!!!!!!!!!!!!!!!!
		class stream !!!!!!!!!!!!!!!!!!!!!!!!!   
		{...}

b) Template Class Partial Specialization
   -Partial template specialization is a particular form of class template 
    specialization; it allows the programmer to specialize only some arguments 
    of a class template, as opposed to explicit full specialization, where all 
    the template arguments are provided.

   -You may want to generate a specialization of the class for just one 
    parameter, for example :

	//base template class
	template<typename T1, typename T2> !!!!!!!!! 2 parms
	class X 
	{
	} ;

	template<typename T1> 
	class X<T1, int> 
	{
	} ; //C2989 here    

	// partial specialization - cont..
	//partial specialization !!!!!!!!!!!!! ONE parm. only
	template <typename T, int size>
	class Array { }
	...
	template <int size>
	class Array<bool, size> { } // partially specialized: T is bool, size remains


a) -When you instantiate a class template, the compiler creates a definition 
    based on the template arguments you have passed. Alternatively, if all those 
    template arguments match those of an explicit specialization, the compiler 
    uses the definition defined by the explicit specialization.
   -An explicit specialization only has a template argument list. 
   
b) partial specialization:
   -is a generalization of explicit specialization.
   -has both a template argument list and a template parameter list
   (*) You cannot partially specialize function templates.


//////////////////////////////////////////////
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

/*
///////////////////////////////////////////////
example-1
..class template specialization - 
///////////////////////////////////////////////
*/

template <class T>
class stream
{
	public:
		void f() { cout << "stream<T>::f()"<< endl ;}
} ;

// template class specialization for template class stream
template <>
class stream<char>
{
	public:
		void f() { cout << "stream<char>::f()"<< endl ;}
} ;
//////////////////////////////////////////////////////////
//example-2


int main()
{
	// example-1
	// template class specialization
	// In the below example, stream<char> is used as the definition of streams of 
	// chars; other streams will be handled by the template class generated from 
	// the class template.
	stream<int> si ;
	stream<double> sd ;
	stream<char> sc ; // using the template specialization (class char version)
	si.f() ;
	sd.f();
	sc.f() ;

	message(">>>>> End of Calls !!!");

	return 0;
}

