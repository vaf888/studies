//------------------------------------------------
// description..: move semantics 001
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>

using namespace std;

/*
-The Big Five are the following functions, which every class should  define, if at least one of these functions are defined (that is, if  you define one, you must define them all):
-The author of these classes need not implement these functions but  instead should—at a minimum—define the functions, explicitly stating  how deletions, copying, and moving should take place (if at all).

-This ensures that if one of these functions is defined, the rest of
 the class's move, copy, and destruction semantics are correct.

// destructor
~the_answer() = default;

// move constructor
the_answer(the_answer &&) noexcept = default;

//move assignment operator
the_answer &operator=(the_answer &&) noexcept = default;

// copy constructor
the_answer(const the_answer &) = default;

// copy assignment operator
the_answer &operator=(const the_answer &) = default;

*/

//----------------------------------------------------------------------
// Issues: ????????????????????????????????
// a) this class define a destructor but not the other 4 (from the group of five)
class TheAnswer
{
    int m_answer{42};

public:

/*
    ~TheAnswer()
    {
        std::cout << "The answer is: " << m_answer << '\n';
    }
  */
};




//----------------------------------------------------------------------
int main()
{
	cout << ">>>>>main() ..." << endl;

	TheAnswer a{};

	TheAnswer b = a;
	//b=b;
	void(&b);

	TheAnswer c;
	c=a;

	
	cout << ">>>>>main() - End !" << endl;

	return 0;

}

