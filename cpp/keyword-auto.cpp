//------------------------------------------------
// file.........: keyword-auto.cpp
// description..: studies: keyword auto + variable type deduction
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <stdexcept>  // throw, catch, logic_error
#include <string>
#include <typeinfo>   // for typeid
#include <regex>
#include <initializer_list> 
#include <map> 
#include <list>
#include <deque>    

using namespace std;

/*
--- auto keyword ---
https://docs.microsoft.com/en-us/cpp/cpp/auto-cpp?view=vs-2019

-Deduces the type of a declared variable from its initialization expression.
-To use the auto keyword, use it instead of a type to declare a variable, and specify an initialization   expression. 
-In addition, you can modify the auto keyword by using specifiers and declarators such as  const,  volatile, pointer (*), reference (&), and rvalue reference (&&). 
-The compiler evaluates the  initialization expression and then uses that information to deduce the type  of the variable.
-The auto keyword is a simple way to declare a variable that has a complicated type. 
 For example, you can use auto to declare a variable where the initialization expression 
 involves templates, pointers to functions, or pointers to members.
-References and cv-qualifiers
 Note that using auto drops references, const qualifiers, 
 and volatile qualifiers. 

 -To use the auto keyword, use it instead of a type to declare a variable, 
  and specify an initialization expression. 
  In addition, you can modify the auto keyword by using specifiers and 
  declarators such as const, volatile, pointer (*), reference (&), and 
  rvalue reference (&&). The compiler evaluates the initialization 
  expression and then uses that information to deduce the type of the variable. 

 -Note that using auto drops references, const qualifiers, and volatile 
  qualifiers. -> see test001() !!!
*/

/*
------------------------------------------------
*/
void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

/*
------------------------------------------------
*/
// to use the template below:
// print_T<const int * const **>();
// will print void print_T() [T = const int *const **]
template<typename T> 
string print_T() 
{
  std::smatch m;
  std::regex re("T = .*;");

  string s = __PRETTY_FUNCTION__ ;

  if (std::regex_search (s,m,re))
    return m.str();
  else
    return "";
}

/*
------------------------------------------------
*/
void test001()
{
  {
    /*
    References and cv-qualifiers:
    -Note that using auto DROPS references,
     const qualifiers, and volatile qualifiers. 

    -results running he example below:
     ..myAuto -> is an int, not an int reference, so 
                 the output is 11 11
       (**) and not 11 12 as would be the case if the 
            reference qualifier had not been dropped by 
            auto.
    */
    int count =10;
    int& countRef = count;
    auto myAuto = countRef;

    countRef=11;
    cout << "count=" << count << endl;

    //Ops: myAuto is just an INT not a int& 
    //(auto ignore/skip the reference)
    myAuto = 12; myAuto=myAuto;
    cout << "count=" << count << endl;    

    std::cout << "typeid(count).name()=" << typeid(count).name() << '\n';
    std::cout << "typeid(countRef).name()=" << typeid(countRef).name() << '\n';
    std::cout << "typeid(myAuto).name()=" << typeid(myAuto).name() << '\n';
  }
}

/*
------------------------------------------------
*/
void test002()
{
  int myI;
  int * myPi;
  int & myIref = myI;

  //print_T<int>();
  //std::cout << "int is: " << print_T<int>() << '\n';
  //std::cout << "  i is: " << print_T<i>() << '\n';
  std::cout << "    int myI is: " << typeid(myI).name() << '\n';
  std::cout << "         pi is: " << typeid(myPi).name() << '\n';
  std::cout << "        *pi is: " << typeid(*myPi).name() << '\n';
  std::cout << "int& myIref is: " << typeid(myIref).name() << '\n';
}

/*
------------------------------------------------
*/
void test003()
{
  /*
    Type deduction with braced initializers (C++14)
    -The following code example shows how to initialize an auto variable 
     using braces. 
     Note the difference between B and C and between A and E.
  */

  // std::initializer_list<int>
  auto A = { 1, 2 };

  // std::initializer_list<int>
  auto B = { 3 };

  // int
  auto C{ 4 };

  // C3535: cannot deduce type for 'auto' from initializer list'
  // error: unable to deduce ‘std::initializer_list<auto>’ 
  //        from ‘{5, 6.7000000000000002e+0}’
  //auto D = { 5, 6.7 };
  auto D = {5.5,6.7}; // fixing !!!

  // C3518 in a direct-list-initialization context the type for 'auto'
  // can only be deduced from a single initializer expression
  // error: direct-list-initialization of ‘auto’ requires exactly one element [-fpermissive]
  // auto E{ 8, 9 };
  auto E = {8,9}; // fixing

  std::cout << "typeid(A).name()=" << typeid(A).name() << '\n';
  std::cout << "typeid(B).name()=" << typeid(B).name() << '\n';
  std::cout << "typeid(C).name()=" << typeid(C).name() << '\n';
  std::cout << "typeid(D).name()=" << typeid(D).name() << '\n';
  std::cout << "typeid(E).name()=" << typeid(E).name() << '\n';
}

/*
------------------------------------------------
*/
void test004()
{
  int j = 0;  // Variable j is explicitly type int.
  auto k = 0; // Variable k is implicitly type int because 0 is an integer.
  std::cout << "typeid(j).name()=" << typeid(j).name() << '\n';
  std::cout << "typeid(k).name()=" << typeid(k).name() << '\n';
}

/*
------------------------------------------------
*/
void test005()
{
  /*
  The following declarations are equivalent, but the second 
  declaration is simpler than the first. 
  One of the most compelling reasons to use the auto keyword i
  s simplicity !!!!!!!!!!!!!!!!!
  */

  list<string> l1{"aaaaa"};
  list<string> l2{"bbbbb"};

  map<int,list<string>> m{{1,l1},{2,l2}};

  map<int,list<string>>::iterator i = m.begin();
  auto j = m.begin();

  std::cout << "i=" << typeid(i).name() << endl;
  std::cout << "j=" << typeid(j).name() << endl;
}

/*
------------------------------------------------
*/
void test006()
{
  /*
  The following code fragment declares the type of variables iter and elem when the for and range for 
  loops start.  
  */

  deque<double> dqDoubleData(2, 0.1);

  std::cout << "<<<<<" << endl;
  for (auto iter = dqDoubleData.begin(); iter != dqDoubleData.end(); ++iter)
  {
    std::cout << "iter=" << typeid(iter).name() << endl;
  }

  // prefer range-for loops with the following information in mind
  // (this applies to any range-for with auto, not just deque)
  std::cout << "<<<<<" << endl;

  // COPIES elements, not much better than the previous examples
  for (auto elem : dqDoubleData) 
  {
    std::cout << "elem=" << typeid(elem).name() << endl;
  }

  std::cout << "<<<<<" << endl;
  // observes and/or modifies elements IN-PLACE  
  for (auto& elem : dqDoubleData)
  {
    std::cout << "elem=" << typeid(elem).name() << endl;
  }

  std::cout << "<<<<<" << endl;
  // observes elements IN-PLACE  
  for (const auto& elem : dqDoubleData)
  {
    std::cout << "elem=" << typeid(elem).name() << endl; 
  }  
}

/*
------------------------------------------------
*/
void test007()
{
  /*
  The following code fragment uses the new operator and 
  pointer declaration to declare pointers.
  */
  double x = 12.34;
  auto  *y = new auto(x), 
       **z = new auto(&x);

  std::cout << "x=" << typeid(x).name() << endl;
  std::cout << "y=" << typeid(y).name() << endl;
  std::cout << "z=" << typeid(z).name() << endl;

}

/*
------------------------------------------------
*/
void test008()
{
  /*
  The next code fragment declares multiple symbols in each declaration 
  statement. 
  Notice that all of the symbols in each statement resolve to the same type.  
  */
  auto x = 1, 
      *y = &x, 
     **z = &y;  // Resolves to int.
  auto a(2.01), 
       *b(&a);  // Resolves to double.
  auto c = 'a', 
       *d(&c);  // Resolves to char.
  auto m = 1, 
      &n = m;   // Resolves to int.

  std::cout << ">>>>>" << endl;
  std::cout << "x=" << typeid(x).name() << endl;
  std::cout << "y=" << typeid(y).name() << endl;
  std::cout << "z=" << typeid(z).name() << endl;
  
  std::cout << ">>>>>" << endl;
  std::cout << "a=" << typeid(a).name() << endl;
  std::cout << "b=" << typeid(b).name() << endl;

  std::cout << ">>>>>" << endl;
  std::cout << "c=" << typeid(c).name() << endl;
  std::cout << "d=" << typeid(d).name() << endl;

  std::cout << ">>>>>" << endl;
  std::cout << "m=" << typeid(m).name() << endl;
  std::cout << "n=" << typeid(n).name() << endl;

}

/*
------------------------------------------------
*/
int main()
{
  message("test001");
  test001();  

  message("test002");  
  test002();  

  message("test003");    
  test003(); 

  message("test004");    
  test004(); 

  message("test005");    
  test005(); 

  message("test006");    
  test006(); 

  message("test007");    
  test007(); 

  message("test008");    
  test008(); 

  return 0;
}



