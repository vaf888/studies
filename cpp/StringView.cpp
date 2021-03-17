//------------------------------------------------
// description..: studies - string_view c++17
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iomanip> //std::boolalpha;
#include <string_view>
//#include <format>

using namespace std;

/*
	We want to sort a vector of persons, by age:
*/

void stringView000()
{
	std::string s1{"red"};
	std::string s2{s1};

	string_view v1{s1}; 	//v1 sees the content of s1
	//cout << fmt::format("s1:{}\ns2: {}\nv1: {}\n\n",s1, s2, v1);
	cout << "s1=" << s1 << endl;
	cout << "s2=" << s2 << endl;	
	cout << "v1=" << v1 << endl;

	//string_view sees changes in the string they are vewing
	cout << ">>>>>" << endl;
	s1[0]='B';
	cout << "s1=" << s1 << endl;
	cout << "s2=" << s2 << endl;	
	cout << "v1=" << v1 << endl;

	//string_views are comparable with std::tring ou string_views
	cout << std::boolalpha;
	cout << "s1==s2=" << (s1==s2) << endl;
	cout << "s1==v1=" << (s1==v1) << endl;
	cout << "s2==v1=" << (s2==v1) << endl;
	cout << "v1==v1=" << (v1==v1) << endl;

	//string_view can remove prefix or sufix
	cout << ">>>>>" << endl;
	cout << "before removing prefix v1=" << v1 << endl;
	v1.remove_prefix(1); // remove 1 char from the front
	cout << "after removing prefix v1=" << v1 << endl;
	v1.remove_suffix(1); // remove 1 char from the back
	cout << "after removing suffix v1=" << v1 << endl;

	//string_view s are iterable
	std::string s3{"Antonio Fernandes"};
	std::string_view v3{s3};
	for(const auto & c:v3)
		cout << c << ' ';
	cout << endl;

	//sring_view allows operations on C-strings
	char c4[] = "V. Antonio";
	std::string_view v4{c4};
	cout << "v4=" << v4 << endl;
	cout << "v4.find(\".\")=" << v4.find('A') << endl;
	cout << "v4.size()=" << v4.size() << endl;






}

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "________________________________"	<< endl;
	stringView000();

	
	return 0;
}

