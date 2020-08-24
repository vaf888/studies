//------------------------------------------------
// file.........: set.cpp
// description..: stl map (internal representation: red black tree (*)
//                (*) a self-balancing binary search tree
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
#include <map>

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

template<typename T>
void showIt(const T & s, bool isMultimap=false)
{
  if(isMultimap)
    cout << ">>>>> multimap content..." << endl;  
  else
    cout << ">>>>> map content..." << endl;

  for(auto it=s.begin(); it != s.end(); ++it)
    cout << "key=" << it->first << " value=" << it->second << endl;

  //or...
  //for (auto item:s)
  //  cout << item << " ";

  cout << endl;    
}

int main() 
{
  
  message("MAP:");
  map<string,string> m0 {{"Maria","Mae"}, {"Isabel","irma"}, {"Marcilio","pai"} };
  showIt(m0);

  // adding item
  m0["Joao"]="irmao";
  showIt(m0);

  cout << "number of items in the map=" << m0.size() << endl;

  // find item
  cout << "finding Joao... result value=" << (m0.find("Joao"))->second << endl;

  // insert via pair
  auto p0 = make_pair("Vilma", "irma");
  m0.insert(p0);
  showIt(m0);
  cout << "number of items 'Joao' in the map=" << m0.count("Joao") << endl;

  // try to insert duplicate & test results
  p0 = make_pair("Roseli", "irma");
  auto res = m0.insert(p0);
  if(res.second)
  {// success with the insert
    //cout << "OK - inserted -> key=" << *res.first << " value=" << (res.first)->second <<endl;
    //cout << "OK - inserted !!!" << endl;
    cout << "OK - inserted -> key=" << (res.first)->first << " value=" << (res.first)->second << endl;
  }
  else
  {    
    //cout << "ERROR - NOT inserted -> key=" << res.first << " value=" << (res.first)->second <<endl;
    //cout << "ERROR - NOT inserted !!!" << endl;
    cout << "ERROR - NOT inserted -> key=" << (res.first)->first << endl;
  }

  // find item (key) in map
  //auto itResFind = m0.find("Joao");
  auto itResFind = m0.find("XXXXX");
  if (itResFind != m0.end())
  {
    cout << "OK - found -> key=" << itResFind->first << " value=" << itResFind->second << endl;
  }
  else
  {
    cout << "ERROR - NOT found !!!" << endl;
  }

//--- multimap ---

  message("MULTIMAP:");
  multimap<string,string> m1 {{"Maria","Mae"}, {"Isabel","irma"}, {"Marcilio","pai"} };
  showIt(m1,true);

  // adding item
  // !!!!!!!!! [] not allowed in multimpa -> m1["Joao"]="irmao";
  auto p1 = make_pair("Joao", "irmao");
  m1.insert(p1);
  showIt(m1,true);
  cout << "number of items in the map=" << m1.size() << endl;

  //erase
  m1.erase("Maria");
  showIt(m1,true);

  p1 = make_pair("Maria", "mae");
  m1.insert(p1);
  showIt(m1,true);  

  // inserting duplicates
  cout << "inserting duplicates..." << endl;
  m1.insert(p1);
  m1.insert(p1);
  showIt(m1,true);  

  // counting items - including duplicates
  auto numItems = m1.count("Maria")  ;
  assert(3 == numItems);

  p1 = make_pair("Joao", "irmao");
  m1.insert(p1);
  showIt(m1,true);  

	return 0;

}

