//------------------------------------------------
// file.........: reduce.cpp
// description..: stl reduce & accumulate studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <string>
#include <stdexcept>
#include <array>
#include <vector>
#include <iterator>
#include <numeric>    // for std::reduce, std::accumulate

using namespace std;

/*
------------------------------------------------
*/
void message(const string s="")
{
  cout << endl << "________________________________" << endl;
  cout << ">>>>> " << s << endl;
}

/*
------------------------------------------------
*/

//rounding errors issues - linked to float
// issue: In some installations results can be different, depending on the
//        order os the items in the array of floats
// reason: flots + roundings
// e.g. - in SOME environments
// (a) will give result = 4 -> error - due to roundings
//     std::array<float,10> a{4.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f};
//     auto res = std::accumulate(a.begin(), a.end(), 0.0f);
//
// (b) will give result = 5 -> OK - roundings smaller effect when 4.1 is at the end.
//     std::array<float,10> a{0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,4.1f};
//     auto res = std::accumulate(a.begin(), a.end(), 0.0f);
void myAccumulate()
{
  cout << ">>>>>std::accumulate using float ..." << endl;
  cout << "input=";
  std::array<float,10> a{4.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f,0.1f};
  for(auto f:a)
    cout << f << " ";
  cout << std::endl;

  cout << "command executed -> std::accumulate(a.begin(), a.end())" << endl;

  auto res = std::accumulate(a.begin(), a.end(), 0.0f);

  cout << "output=" << res << endl;

}

/*
------------------------------------------------
*/
void myAccumulate2()
{
  cout << ">>>>>std::accumulate using int ..." << endl;
  cout << "input=";
  std::array<int,3> a{1,2,3};
  for(auto f:a)
    cout << f << " ";
  cout << std::endl;

  cout << "command executed -> std::accumulate(a.begin(), a.end())" << endl;

  auto res = std::accumulate(std::begin(a), std::end(a), 0);

  cout << "output=" << res << endl;

}

/*
------------------------------------------------
*/
void myAccumulateNonNumericType()
{
  /*
  Nothing prevents using std::accumulate on other types than numeric types. 
  Every type that implements an operator+ is a good candidate.
  On std::string, operator+ does a concatenation:
  */

  cout << ">>>>>std::accumulate using strings..." << endl;
  cout << "input=";
  std::vector<std::string> a{"today", "is", "saturday"};

  for(auto f:a)
    cout << f << " ";
  cout << std::endl;

  cout << "command executed -> std::accumulate(std::begin(a), std::end(a), \"\")" << endl;

  //auto res = std::accumulate(std::begin(a), std::end(a), std::string(""));
  auto res = std::reduce(std::begin(a), std::end(a), std::string(""));
  cout << "output=" << res << endl;

}


/*
------------------------------------------------
*/
int main()
{

  message ();
  myAccumulate();

  message ();
  myAccumulate2();

  message ();
  myAccumulateNonNumericType();

  cout << endl;

  return 0;
}



