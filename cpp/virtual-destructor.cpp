//------------------------------------------------
// file.........: palindrome.cpp
// description..: check if string is a palindrome (e.g.: anna)
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <string>
//#include <typeinfo>
#include <iomanip> // for std::setprecision()
 
using namespace std;
class Base
{
    public:

    virtual ~Base()

    //TESTS ONLY: if Base destructor is not virtual, only the Base destructor will
    //            be called, missing the call to the derived's destructor.
    //~Base() 
    {
        cout << ">>>>>in Base - Destructor\n"; 
    }
};

class Derived:public Base
{
    public:
    ~Derived() 
    { 
        cout<< ">>>>>in Derived - Destructor\n"; 
    }
}; 

int main()
{
    cout<< ">>>>>in Main - begin\n"; 
    Base* b = new Derived;     // Upcasting
    delete b;
    cout<< ">>>>>in Main - end\n"; 
}

