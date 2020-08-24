//------------------------------------------------
// file.........: virtual.cpp
// description..: virtual classes studies studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>
#include <stdexcept>
#include <iterator>
#include <algorithm>  // for std::find
#include <utility>    // make_pair
#include <mutex>
#include <thread>
#include <atomic>

using namespace std;

void message(string s)
{
  cout << endl << "________________________________" << endl;
  cout << ">>>>> " << s << endl;
}

/*
------------------------------------------------
*/
using namespace std;


/*
  a bit faster version using temporary var
*/

/*
It has always been possible to overload a function in one class with
   a member function from another class.
   With inheritance,you can overload a base class member
   function with a member function in a subclass as well.
   e.g.:
*/
class Student
{
public:
  float calcTuition()
  {
    cout << ">>>>>in BASE - Student::calcTuition(...)" << endl;
    return 77.0f;
  }

  virtual float calcTuitionVirtual()
  {
    cout << ">>>>>in BASE - Student::calcTuitionVirtual(...)" << endl;
    return 77.0f;
  }

  // required - mostly when upcasting is done ( cast derived to base)
  virtual ~Student()
  {
    cout << ">>>>>in Student::~Student() ..." << endl;
  }

  //...otherstuff
};

class GraduateStudent : public Student
{
public:
  float calcTuition()
  {
    cout << ">>>>>in DERIVED - GraduateStudent::calcTuition(...)" << endl;
    return 99.0f;
  }

  float calcTuitionVirtual() override  //override - optional
  {
    cout << ">>>>>in DERIVED - GraduateStudent::calcTuitionVirtual(...)" << endl;
    return 99.0f;
  }

  ~GraduateStudent()
  {
    cout << ">>>>>in GraduateStudent::~GraduateStudent() ..." << endl;
  }

};

/*
  But what if the exact class of the object can't be determined at 
  compile time?
  To demonstrate how this can occur,let's change the preding program
*/

//this is not a virtual function, so parm x type is define
//at compilation time - and x is type Student (base)
//so, all the calls will be done to Student::calcTuition
// !!! it does not matter if the type passed at run time
//     is a Student or a GraduateStudent !!!

//Normally the compiler decides which function to call at
//compile time. Even when a function is overloaded,the compiler uses the 
//different argument types to decide at compile time.

void func(Student& x)
{
  x.calcTuition();//to which calcTuition does this refer?
}//(answer -> base class Student::calcTuition)

// error: overload - return type does not play a role
//        so: ERROR if I have 2 functions with same name & parms
//            difference only in the return type - as below


void func2(Student& x)
{
  // virtual - which call to do will defined at run time
  // if at runtime:
  // x is a Student   -> calls Student::calcTuition(...)
  // x is GradStudent -> calls GradStudent::calcTuition(...)
  x.calcTuition(); // virtual - which call to do will defined at run time
}//(answer -> base class Student::calcTuition)

// calling the virtual methods
void func3(Student& x)
{
  // virtual - which call to do will defined at run time
  // if at runtime:
  // x is a Student   -> calls Student::calcTuition(...)
  // x is GradStudent -> calls GradStudent::calcTuition(...)
  x.calcTuitionVirtual(); // virtual - which call to do will defined at run time
}//(answer -> base class Student::calcTuition)

void func4(Student * x)
{
  // virtual - which call to do will defined at run time
  // if at runtime:
  // x is a Student   -> calls Student::calcTuition(...)
  // x is GradStudent -> calls GradStudent::calcTuition(...)
  x->calcTuitionVirtual(); // virtual - which call to do will defined at run time
}//(answer -> base class Student::calcTuition)


// ERROR ERROR ERROR
/*
int foo(int p)
{
  return 0;
}

double foo(int p)
{
  return 0.0;
}
*/

/*
--------------------------------------------------
  main
--------------------------------------------------  
*/

int main()
{
  {
    Student s;
    GraduateStudent gs;
    cout << endl;
    cout << "_________________________________" << endl;
    cout << ">>>>>first call" << endl;
    s.calcTuition();  //callsStudent::calcTuition()
    gs.calcTuition(); //callGraduateStudent::calcTuition()
  }

  {
    // using func(Student& x)
    cout << endl;
    cout << "_________________________________" << endl;
    cout << ">>>>>call using NON-virtual function" << endl;
    Student s2;
    GraduateStudent gs2;
    func2(s2);
    func2(gs2);
  }
  
  {
    // call using virtual function
    cout << endl;
    cout << "_________________________________" << endl;
    cout << ">>>>>call using virtual function" << endl;
    Student s3;
    GraduateStudent gs3;
    func3(s3);
    func3(gs3);
  }

  {
    // using upcasting - to test virtual distructor
    cout << endl;
    cout << "_________________________________" << endl;
    cout << ">>>>>using upcasting..." << endl;
    Student * s4 = new GraduateStudent();
    func4(s4);
    delete s4;
  }

  cout << endl;

  return 0;
}



/*
int main() 
{

  auto newInstanceV0 = getInstanceV0();
  cout << "instance=" << newInstanceV0 << endl;

  pInstance=nullptr;

  auto newInstanceV1 = getInstanceV1();
  cout << "instance=" << newInstanceV1 << endl;

  auto newInstanceV2 = getInstanceV2();
  cout << "instance=" << &newInstanceV2 << endl;


	return 0;

}
*/

