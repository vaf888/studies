//------------------------------------------------
// file.........: set.cpp
// description..: stl set (binary search tree) and unordered_set(hash) - studies
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
#include <set>
#include <unordered_set>
#include <algorithm>  // for std::find

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
void showIt(const T & s)
{
  cout << ">>>>> set content..." << endl;

  std::copy(s.begin(), s.end(), std::ostream_iterator<string>{std::cout, " "});

  //or
  //for(auto it=s.begin(); it != s.end(); ++it)
  //  cout << *it << " ";

  //or...
  //for (auto item:s)
  //  cout << item << " ";

  cout << endl;    
}

int main() 
{
  
  message("SET - ordered");
  set<string> s0{"aa","bb","cc","dd","ee","ff"};
  showIt(s0);
  assert(s0.size() == 6);
  
  //--insert gg and hh
  s0.insert("gg")	;
  s0.insert("hh") ;
  showIt(s0);
  assert(s0.size() == 8);

  //remove dd
  s0.erase("dd");
  showIt(s0);
  assert(s0.size() == 7);

  //insert dd
  s0.insert("dd") ;
  showIt(s0);
  assert(s0.size() == 8);

  //check if key exists, before erasing
  auto it = s0.find("dd");
  if (it != s0.end())
  {
    cout << "erasing ->" << *it << endl;
  }
  else
  {
    cout << "Not found !!!" << endl;
  }

  // erase + not found
  it = s0.find("xx");
  if (it != s0.end())
  {
    cout << "erasing ->" << *it << endl;
  }
  else
  {
    cout << "Not found !!!" << endl;
  }

  // inserting duplicates - no change
  s0.insert("dd") ;
  showIt(s0);
  assert(s0.size() == 8);

  // sarch for item - another way
  if (s0.count("dd"))
   cout << "Found 'dd' in the set !!!" << endl; 
  else
   cout << "'dd' Not found !!!" << endl; 

  string findThis="dd";
  auto it2 = std::find(s0.begin(), s0.end(), findThis);
  if (it2 != s0.end())
   cout << "Found 'dd' in the set !!!" << endl; 
  else
   cout << "'dd' Not found !!!" << endl; 

  //--- unordered_set - (internal implementation = hash) ---
  message("UNORDEREED_SET:");
  unordered_set<string> s2{"aa","bb","cc","XXXXX","dd","ee","ff"};
  showIt(s2);
  assert(s2.size() == 7);
 
  // delete XXXXX
  s2.erase("XXXXX");
  showIt(s2);
  assert(s2.size() == 6);

  //insert XXXXX 2 times - only one inserted (duplication)
  s2.insert("XXXXX");
  s2.insert("XXXXX");
  showIt(s2);
  assert(s2.size() == 7);

  // find 'dd'
  findThis="dd";
  auto it3 = std::find(s2.begin(), s2.end(), findThis);
  if (it3 != s2.end())
   cout << "Found 'dd' in the set !!!" << endl; 
  else
   cout << "'dd' Not found !!!" << endl; 

// multiset - allows duplications
  message(">>>>>MULTISET:");
  multiset<string> s3{"aa","bb","cc","XXXXX","dd","ee","ff"};
  showIt(s3);
  assert(s3.size() == 7);
 
  // delete XXXXX
  s3.erase("XXXXX");
  showIt(s3);
  assert(s3.size() == 6);

  //insert XXXXX 2 times - 2 times inserted - allows duplication !
  s3.insert("XXXXX");
  s3.insert("XXXXX");
  showIt(s3);
  assert(s3.size() == 8);

  auto numItems = s3.count("XXXXX");
  assert ((int)numItems == 2);

  s3.insert("hh");
  showIt(s3);
  assert(s3.size() == 9);

  s3.insert("gg");
  showIt(s3);
  assert(s3.size() == 10);


	return 0;

}

