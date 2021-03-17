//------------------------------------------------
// description..: lambda and algorithms - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iomanip> //std::boolalpha;

using namespace std;

/*
	We want to sort a vector of persons, by age:
*/

//----------------------------------------------------------------------
struct Person
{
	std::string m_name{};
	int m_age{0};

	Person() = default;
	Person(std::string name, int age) : m_name(name), m_age(age)
	{
	}

	Person(const Person& other) = default;
	Person& operator=(const Person& other) = default;

	Person(Person&& other) = default;
	Person& operator=(Person&& other) = default;
	~Person() = default;

	void displayIt(const std::vector<Person> & v, string&& title) const
	{
		cout << title << endl;
		for(auto el:v)
			cout << "name=" << el.m_name << "; age=" << el.m_age << endl;

		cout << endl;
	}


	// adding funciontal operator inside the class
	bool operator()(const Person& a, const Person& b) const
	{
		return a.m_age < b.m_age;
	}

};

//----------------------------------------------------------------------
bool AllOf(std::vector<Person>& v )
{
	cout << __PRETTY_FUNCTION__ << endl;
	return std::all_of(v.begin(), v.end(),
				[](const Person & p) {return p.m_age < 20;});
}

//----------------------------------------------------------------------
bool canDrink(std::vector<Person>& v )
{
	cout << __PRETTY_FUNCTION__ << endl;

	bool allowedToDrink =
		std::all_of(v.begin(), v.end(),
				[](const Person & p) 
				{
					return p.m_age >= 20;
				});

	return allowedToDrink;
}

//----------------------------------------------------------------------
//using non-stable partition - original order not guaranteed
void partition000(std::vector<Person>& people )
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::partition(people.begin(), people.end(),
				[](Person & people) 
				{
					std::size_t found = (people.m_name).find('.');
					//cout << "people.m_name=" << people.m_name << ";res=" 
					//	 << tmp << endl;

					return (found!=std::string::npos);
				});
}

//----------------------------------------------------------------------
//using stable partition - original order guaranteed !!!
void stablePartition(std::vector<Person>& people )
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::stable_partition(people.begin(), people.end(),
				[](Person & people) 
				{
					std::size_t found = (people.m_name).find('.');
					//cout << "people.m_name=" << people.m_name << ";res=" 
					//	 << tmp << endl;

					return (found!=std::string::npos);
				});
}

//----------------------------------------------------------------------
int apply000(const std::tuple<int,int>& t0)
{
	const auto sum = std::apply
	(
		[](int a, int b) {return a + b;}, //function object/lambda
		t0 // tuple
	);

	return sum;
}

//----------------------------------------------------------------------
// c++17 - fold expressions
// Fold expressions offer a compact syntax to apply a 
// binary operation to the elements of a parameter pack
template <typename... Args>
auto addAll(Args... args)
{
	//using fold expressions
	//will apply +  (left expression) to all received arguments
	//e.g.
	// addAll(1,2,3,4,5); // returns 15.
	// is equivalent to:
	// ((((1+2)+3)+4)+5)

	return (... + args);
}

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "________________________________"	<< endl;
	//setup
	std::vector<Person> p1;
	p1.emplace_back("ccc",19);
	p1.emplace_back("aaa",17);
	p1.emplace_back("bbb",18);
	p1.emplace_back("ddd",19);

	//act
	bool result1=false;
	cout << endl;
	result1=AllOf(p1);

	cout << ">>>>>AllOf(p1)="  << std::boolalpha << result1 << endl;

	//assert
	bool expected1 = true;
	assert(expected1 == result1);

	cout << "________________________________"	<< endl;
	//setup
	std::vector<Person> p2;
	p2.emplace_back("ccc",22);
	p2.emplace_back("aaa",25);
	p2.emplace_back("bbb",23);
	p2.emplace_back("ddd",25);

	//act
	bool result2=false;
	cout << endl;
	result2=canDrink(p2);

	cout << ">>>>>canDrink(p2)="  << std::boolalpha << result2 << endl;

	//assert
	bool expected2 = true;
	assert(expected2 == result2);

cout << "________________________________"	<< endl;
	//setup
	std::vector<Person> p3;
	p3.emplace_back("Mary C. Stuart",22);
	p3.emplace_back("Mary Stuart",33);
	p3.emplace_back("Bruce Lee",23);
	p3.emplace_back("John Wayne",19);
	p3.emplace_back("Mary Ellen",20);
	p3.emplace_back("Bruce Willis",30);
	p3.emplace_back("Bruce M. Lee",25);
	p3.emplace_back("Mary B. Ellen",29);
	Person().displayIt(p3, "items Before partition");

	//act
	auto result3=p3.size();
	cout << endl;
	partition000(p3);

	cout << ">>>>>calling partition000(p3)..." << endl;

	//assert
	Person().displayIt(p3, "items After partition");
	auto expected3 = p3.size();
	assert(expected3 == result3);

	cout << "________________________________"	<< endl;
	//setup
	std::vector<Person> p4;
	p4.emplace_back("Mary C. Stuart",22);
	p4.emplace_back("Mary Stuart",33);
	p4.emplace_back("Bruce Lee",23);
	p4.emplace_back("John Wayne",19);
	p4.emplace_back("Mary B. Ellen",29);	
	p4.emplace_back("Mary Ellen",20);
	p4.emplace_back("Bruce Willis",30);
	p4.emplace_back("Bruce M. Lee",25);
	Person().displayIt(p4, "items Before partition");

	//act
	auto result4=p4.size();
	cout << endl;
	stablePartition(p4);

	cout << ">>>>>calling partition000(p4)..." << endl;

	//assert
	Person().displayIt(p4, "items After partition");
	auto expected4 = p4.size();
	assert(expected4 == result4);

	cout << "________________________________"	<< endl;
	//setup
	std::tuple<int,int> t5{1,3};

	//act
	cout << ">>>>>calling apply(t5) ..." << endl;
	int result5 = apply000(t5);
	cout << ">>>>>result5=" << result5 << endl;

	//assert
	int expected5 = 4;
	assert(result5 == expected5);

	//---using make_tuple---
	cout << "________________________________"	<< endl;
	//setup
	
	//act
	cout << ">>>>>calling apply(std::make_tuple(1,3)) ..." << endl;
	int result6 = apply000(std::make_tuple(1,3));
	cout << ">>>>>result6=" << result6 << endl;

	//assert
	int expected6 = 4;
	assert(result6 == expected6);


	//---using fold expressions
	cout << "________________________________"	<< endl;
	//setup
	
	//act
	cout << ">>>>>calling addAll(1,2,3,4,5)..." << endl;
	int result7 = addAll(1,2,3,4,5);
	cout << ">>>>>result7=" << result7 << endl;

	//assert
	int expected7 = 15;
	assert(result7 == expected7);


	return 0;
}

