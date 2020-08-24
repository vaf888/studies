//------------------------------------------------
// file.........: movesemantics000.cpp
// description..: move semantics studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <cstdio>
#include <vector>
#include <string>
#include <utility>
#include <iostream>  // std::cout, std::endl
using namespace std;

void message(const string & s)
{
	//puts(s.c_str());
	//fflush(stdout);
    cout << s << endl;
}

void dispVector(vector<string> & aVector)
{
	if(aVector.empty())
	{
		cout << ("[empty]") << endl;
	}
	else
	{
		for( string item:aVector)
			cout << item << endl;
	}
}

template <typename T>
void swap(T & a, T & b)
{
	message(">>>>> swap()");
	T _tmp(std::move(a));
	a = std::move(b);
	b = std::move(_tmp);
}

int main()
{
	vector<string> v1 = {"one","two","three","for","five"};
	vector<string> v2 = {"six","seven","eight","nine","ten"};
   
	message("__________________________________");
	message(">>>>>initial state"); 
    message(">>>>>>>>>>>>>>>>>> v1:");	
	dispVector(v1);
    message(">>>>>>>>>>>>>>>>>> v2:");	
	dispVector(v2);
/*
    v2 = std::move(v1);
	message("__________________________________");
	message(">>>>>after - v2 = std::move(v1)"); 
    message(">>>>>>>>>>>>>>>>>> v1:");	
	dispVector(v1);
    message(">>>>>>>>>>>>>>>>>> v2:");	
	dispVector(v2);
*/

/*
	// using a third temp vector
	auto & v2Ref = v2;
    auto v3  = std::move(v2Ref);

	message("__________________________________");
	message(">>>>>after - auto v3  = std::move(v2)"); 
    message(">>>>>>>>>>>>>>>>>> v1:");	
	dispVector(v1);
    message(">>>>>>>>>>>>>>>>>> v2:");	
	dispVector(v2);
    message(">>>>>>>>>>>>>>>>>> v3:");	
	dispVector(v3);
*/
	// accessing LOCAL swap function (not std's),
    // via ::swap(...)
	swap(v1, v2);
	message("__________________________________");
	message(">>>>>after - v2 = std::move(v1)"); 
    message(">>>>>>>>>>>>>>>>>> v1:");	
	dispVector(v1);
    message(">>>>>>>>>>>>>>>>>> v2:");	
	dispVector(v2);

 
	return 0;
}





