//------------------------------------------------
// file.........: vtable000.cpp
// description..: virtual functions + vtable - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

using namespace std;

struct test000
{
  // empty struct -> sizeof=1
  //int x;
};

class NoVirtual 
{   
  int a; // 4 bytes in the sizeof
  //int b;
  //int c;

public:   
  void x() const {}   
  int i() const { return 1; } 
}; 

class OneVirtual 
{   
  int a; 

public:   
  virtual void x() const {}   
  int i() const { return 1; }
}; 

class TwoVirtuals 
{   
  int a;

public:   
  virtual void x() const {}   
  virtual int i() const { return 1; } 
}; 

int main() 
{
   cout << "int_____________: " << sizeof(int) << endl;

   // empty struct -> expected sizeof = 1 !!!
   cout << "struct test000__: " << sizeof(test000) << endl;

   //With no virtual functions, the size of the object is exactly what you’d expect: 
   //the size of a single int (the only field in the class)
   cout << "NoVirtual_______: " << sizeof(NoVirtual) << endl;   

   //expected size = 8 - pointer size
   cout << "void*___________: " << sizeof(void*) << endl;   

   //expected size = 16 = 8  + 8 (vptr - pointer to the VTABLE)
   cout << "OneVirtual______: " << sizeof(OneVirtual) << endl;   

   //expected size = 16 = 8  + 8 (vptr - pointer to the VTABLE)
   // VIP: only one vptr per class/obj - no matter how many virtual
   //      methods the class have
   cout << "TwoVirtuals_____: " << sizeof(TwoVirtuals) << endl; 
} 
