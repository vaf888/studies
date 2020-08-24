//------------------------------------------------
// file.........: futureAndPromise.cpp
// description..: async. operations - future + promise - studies
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
#include <future>

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
--------------------------------------------------
  main
--------------------------------------------------  
*/

int main()
{

  // promise - will provide the result to future
  std::promise<int> rc;

  //promise = thread parm
  auto add = [&rc] (int a, int b) 
  {
      rc.set_value(a + b);
  };

  std::thread { add, 1, 2 }.join();

  // get thread results provided by promise
  std::future<int> f = rc.get_future();

  std::cout << "response=" << f.get() << std::endl;

  return 0;
}


