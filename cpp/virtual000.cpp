//------------------------------------------------
// file.........: virtual000.cpp
// description..: virtual - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

using namespace std;

class Abase 
{
public:
  void x() {cout<<"Abase::x()"<<endl;}; 
  virtual void y() {cout<<"Abase::y()" << endl;}
  Abase() {cout << "in Abase::Abase() constructor !" << endl;}
  virtual ~Abase() {cout << "in Abase::~Abase() destructor !" << endl;}
};

class Bderiv : public Abase 
{
public:
  void x() {cout<<"Bderiv::x()"<<endl;};
  virtual void y() {cout<<"Bderiv::y()"<<endl;}
  Bderiv() {cout << "in Bderiv::Bderiv() constructor !" << endl;}
  ~Bderiv() {cout << "in Bderiv::~Bderiv() destructor !" << endl;}
};

int main() 
{
  cout << endl;
  cout << ">>>>>constructing a Bderiv..." << endl;
  Bderiv bDeriv;

  cout << ">>>>>constructing a Abase..." << endl;
  Abase  aBase;

  // no pointer or reference -> no virtual used - stat. comp.
  cout << endl;
  cout << ">>>>>calls statically comp. ..." << endl;
  cout << "expected: Abase::x(),Abase::y(),Bderiv::x(),Bderiv::y()" << endl;
  aBase.x(); // prints 'Abase::x()'
  aBase.y(); // prints 'Abase::y()'
  bDeriv.x(); // prints 'Bderiv::x()'
  bDeriv.y(); // prints 'Bderiv::y()'

  // using virtual overrides - if pointer or reference
  Bderiv *bDerivPt1 = new Bderiv{};
  Abase  *aBasePt1 = bDerivPt1; 
  cout << endl;
  cout << ">>>>>calls statically comp. ..." << endl;
  cout << "expected: Abase::x(),Bderiv::y(),Bderiv::x(),Bderiv::y()" << endl;
  aBasePt1->x();    // prints 'Abase::x()'
  aBasePt1->y();    // prints 'Bderiv::y()'
  bDerivPt1->x();   // prints 'Bderiv::x()'
  bDerivPt1->y();   // prints 'Bderiv::y()'


  cout << endl;
  cout << ">>>>>calling destructors on pointers - Begin..." << endl;
  cout << "aBasePt1..." << endl;
  cout << "BEFORE - aBasePt1=" << aBasePt1 << ", bDerivPt1=" << bDerivPt1 << endl;
  delete aBasePt1;
  bDerivPt1 = nullptr;
  aBasePt1 = nullptr;
  cout << "AFTER - aBasePt1=" << aBasePt1 << ", bDerivPt1=" << bDerivPt1 << endl;
  cout << "aBasePt1 - Done!" << endl;

  cout << "bDerivPt1..." << endl;
  if (bDerivPt1 != nullptr)
  {
    delete bDerivPt1;
    cout << ">>>>>calling destructors on pointers - End" << endl;
  }
  else
  {
    cout << "bDerivPt was already destructed - nothing to do!" << endl;
  }
  cout << "bDerivPt1..." << endl;
  cout << ">>>>>calling destructors on pointers - End" << endl;

  //calls polimorphycally
  cout << endl;
  cout << ">>>>>calls via base or derived pointers ..." << endl;
  cout << "expected results: Abase::y(), Bderiv::y(), Abase::y()" << endl;
  Abase * x[] = {new Abase, new Bderiv, new Abase };
  for (auto c:x)
  {
    c->y();
    delete c;
  }

   return 0;
}

