//------------------------------------------------
// file.........: bitset.cpp
// description..: bitset
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <stdexcept>  // throw, catch, logic_error
#include <cstddef> // C Standard definitions; size_t exact
#include <string>
#include <bitset>

using namespace std;

  /*
    bitset + sizeof:
    Each bitset is implemented by logically packing bits 
    in an array of integral types (typically unsigned longs, 
    which contain at least 32 bits). - in my machine 8 bytes = 64 bits
    In addition, the only conversion from a bitset to a 
    numerical value is to an unsigned long 
    (via the function to_ulong( )).
    e.g.:

    sizeof(bitset<1>) = 8
    sizeof(bitset<64>) = 8
    sizeof(bitset<65>) = 16
  */



/*
------------------------------------------------
*/
void test001()
{
  std::bitset<16> foo;
  std::bitset<16> bar{0xfa2};
  std::bitset<16> baz{std::string("0101111001")};

  cout << "foo: " << foo << endl;
  cout << "bar: " << bar << endl;
  cout << "baz: " << baz << endl;
}

/*
------------------------------------------------
*/
const int SZ = 32;
typedef bitset<SZ> BitSet;

template<int TBits>
bitset<TBits> randBitset()
{

  bitset<TBits> r(rand());

  for (int i=0; i< TBits/16-1; i++)
  {
      r<<=16;

      //OR together with a new lower 16 bits
      r |= bitset<TBits>(rand());
  }

  return r;
}

/*
------------------------------------------------
*/
void test002()
{
  srand(time(0));

  auto t16 = bitset<16>{}; 

  /*
    Each bitset is implemented by logically packing bits 
    in an array of integral types (typically unsigned longs, 
    which contain at least 32 bits). - in my machine 8 bytes = 64 bits
    In addition, the only conversion from a bitset to a 
    numerical value is to an unsigned long 
    (via the function to_ulong( )).
  */

  cout << "sizeof(unsigned long)=" 
    << sizeof(unsigned long) << endl;

  auto t1 = bitset<1>{}; 
  cout << "sizeof(bitset<1>=" 
    << sizeof(bitset<1>) 
    << " - size()=" << t1.size()
    << endl;

  cout << "sizeof(bitset<16>=" 
    << sizeof(bitset<16>) 
    << " - size()=" << t16.size()
    << endl;

  auto t32 = bitset<32>{}; 
  cout << "sizeof(bitset<32>=" 
    << sizeof(bitset<32>) 
    << " - size()=" << t32.size()
    << endl;

  auto t48 = bitset<48>{}; 
  cout << "sizeof(bitset<48>=" 
    << sizeof(bitset<48>) 
    << " - size()=" << t48.size()
    << endl;

  auto t64 = bitset<64>{}; 
  cout << "sizeof(bitset<64>=" 
    << sizeof(bitset<64>) 
    << " - size()=" << t64.size()
    << endl;

  auto t65 = bitset<65>{}; 
  cout << "sizeof(bitset<65>=" 
    << sizeof(bitset<65>) 
    << " - size()=" << t65.size()
    << endl;

  auto t128 = bitset<128>{}; 
  cout << "sizeof(bitset<128>=" 
    << sizeof(bitset<128>) 
    << " - size()=" << t128.size()
    << endl;

  auto t129 = bitset<129>{}; 
  cout << "sizeof(bitset<129>=" 
    << sizeof(bitset<129>) 
    << " - size()=" << t129.size()
    << endl;

  cout << endl;
  cout << ">>>>>getting random bitset rb1" << endl;
  auto rb1 = randBitset<SZ>();
  std::bitset<SZ> a(rb1);
  cout << "\t\trb1=" << rb1 << endl;
  cout << "\t\t  a=" << a << endl;

  cout << ">>>>>getting random bitset rb2" << endl;
  auto rb2 = randBitset<SZ>();
  std::bitset<SZ> b(rb2);
  cout << "\t\trb2=" << rb2 << endl;
  cout << "\t\t  b=" << b << endl;

  // converting from a bitset:
  cout << endl;
  cout << ">>>>>converting from bitset to unsigned long" << endl;
  unsigned long ul = a.to_ulong();
  cout << ">>>>>a as ul=" << ul << endl;
  ul = b.to_ulong();
  cout << ">>>>>b as ul=" << ul << endl;
  std::bitset<SZ> t000 = std::bitset<SZ>{ul};
  cout << ">>>>>t000=" << t000 << endl;

  // converting a string to a bitset
  string cbits("111011010110111");
  cout << ">>>>>cbits as a string=" 
    << cbits << endl;

  cout << ">>>>>std::bitset<SZ>(cbits)="
    << std::bitset<SZ>(cbits);
}

/*
------------------------------------------------
*/
int main()
{

  cout << "_____________________" << endl;  
  test001();

  cout << endl;
  cout << "_____________________" << endl;  
  test002();

  return 0;
}



