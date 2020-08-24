//------------------------------------------------
// file.........: slice000.cpp
// description..: object slicing - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

using namespace std;

class Pet 
{   
  string pname; 

public:   
  Pet(const string& name) : pname(name) {}   
  virtual string name() const { return pname; }   
  virtual string description() const 
  {     
    return "This is " + pname;   
  } 
}; 

class Dog : public Pet 
{   
  string favoriteActivity; 

public:   
  Dog(const string& name, const string& activity)
    : Pet(name), favoriteActivity(activity) {}   

  string description() const 
  {     
    return Pet::name() + " likes to " + favoriteActivity;   
  } 
}; 

void describe(Pet p) 
{ // Slices the object   
  cout << p.description() << endl; 
} 

void describeFixed(Pet & p) 
{ // Slices the object   
  cout << p.description() << endl; 
} 

/*
  The function describe():
  ..is passed an object of type Petby value. 
  ..It then calls the virtual function description() for the Pet object. 

  In main():
  ..you might expect the first call to produce “This is Alfred,” 
    and the second to produce “Fluffy likes to sleep.” 
  >>>>> In fact, both calls use the base-class version of description(). 
        (due to slicing)
*/

/*
------------------------------------------------
*/
int main() 
{   
  Pet aPet("Alfred");   
  Dog aDog("Fluffy", "sleep");   

  cout << endl;
  cout << "__________________________________" << endl;
  cout << ">>>>>ERROR slicing - call by value..." << endl;
  //error - passing parm as object - by value - slicing will occurs
  //        (only base = Pat part of the object will be available)
  describe(aPet);   
  describe(aDog); 

  cout << endl;
  cout << "__________________________________" << endl;
  cout << ">>>>>OK - passing parm via reference or pointer (no slicing)" << endl;
  //passing parms via pointer or ref - it will work fine
  //the correct description method (virtual) will be called
  //acording to the object type Pet or Dog
  describeFixed(aPet);   
  describeFixed(aDog); 
}
