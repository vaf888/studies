//------------------------------------------------
// file.........: DP-FactoryMethod.cpp
// description..: studies - Desing Pattern - Factory Method
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <stdexcept>  // throw, catch, logic_error
#include <cstddef> // C Standard definitions; size_t exact
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
------------------------------------------------
Factory Method:
-to force the creation of objects to occur through a common factory
 (rather than to allow the creational code to be spread throughout your system.)
-If all the code in your program must go to this factory whenever it needs to create one 
 of your objects,  all you must do when you add a new object is modify the factory. 
-The factory method pattern is a creational pattern that uses factory methods to deal 
 with the problem of creating objects without having to specify the exact class of the object 
 that will be created. 
 This is done by creating objects by calling a factory method—either specified in an interface 
 and implemented by child classes, or implemented in a base class and optionally overridden 
 by derived classes -> rather than by calling a constructor. 
------------------------------------------------
*/

/*
------------------------------------------------
*/
void message(const string s="")
{
  cout << endl << "________________________________" << endl;
  cout << ">>>>> " << s << endl;
}

class Shape
{
public:
  virtual void draw()=0;
  virtual void erase()=0;
  virtual ~Shape(){}

  static Shape* factory(const string& type);
};

class Circle : public Shape
{
public:
  void draw() {cout << "Circle::draw" << endl;}
  void erase() {cout << "Circle::erase" << endl;}
  ~Circle() {cout << "~Circle" << endl;}
private:
  Circle(){} // private constructor

  //to allow Shape class call this private constructor
  //in factory method - so, need friend !
  friend class Shape; 
};

class Square : public Shape
{
public:
  void draw() {cout << "Square::draw" << endl;}
  void erase() {cout << "Square::erase" << endl;}
  ~Square() {cout << "~Square" << endl;}
private:
  Square(){} // private constructor

  // to allow calls in factory Shape::factory
  // this way, class Shape can make instances
  // of private constructor from derived classes
  // [ Circle(), Square() ]
  // e.g: return new Circle()
  // for Shape, without the friend, new Circle
  // would be private !!!
  friend class Shape;
};

/*
------------------------------------------------
*/
Shape * Shape::factory(const string& type)
{

  if (type == "Circle")
    return new Circle();
  if (type == "Square")
    return new Square();

  throw std::invalid_argument("Invalid type informed");
}

/*
------------------------------------------------
*/
// Delete pointers in an STL sequence container.
/*
template<class Seq> 
void purge(Seq& c) 
{
  typename Seq::iterator i;
  for(i = c.begin(); i != c.end(); ++i) {
  delete *i;
  *i = 0;
}
*/
void purge(std::vector<Shape *> & c) 
{
  for(auto i = c.begin(); i != c.end(); ++i) 
  {
    delete *i;
    *i = nullptr;
  }
}

/*
------------------------------------------------
*/
int main()
{

  //char* sl[] = 
  string sl[] =
  { 
    "Circle", "Square", "Square",
    "Circle", "Circle", "Circle", "Square" 
  };

  vector<Shape *> shapes;

  try
  {
    for(size_t i=0; i < (sizeof(sl))/sizeof(sl[0]); ++i)
    {
      cout << "adding - " << sl[i] << endl;
      auto tmp = Shape::factory(sl[i]);
      //shapes.push_back(Shape::factory(sl[i]));
      shapes.push_back(tmp);
    }
  }
  catch (const std::invalid_argument& e)
  {
    cout << e.what() << endl;
    purge(shapes);
    return -1;
  }

  cout << "_____________________" << endl;
  for (size_t i=0; i < shapes.size(); ++i)
  {
    shapes[i]->draw();
    shapes[i]->erase();
    cout << endl;
  }
  
  cout << endl;
  purge(shapes);

  return 0;
}



