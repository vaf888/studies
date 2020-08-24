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
    {
        cout << "Base Destructor\n"; 
    }
};

class Derived:public Base
{
    public:
    ~Derived() 
    { 
        cout<< "Derived Destructor"; 
    }
}; 

int main()
{
    Base* b = new Derived;     // Upcasting
    delete b;
}

