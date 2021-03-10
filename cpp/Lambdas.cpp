//------------------------------------------------
// description..: lambda expressions - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <typeinfo>


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
struct ByAge
{
	bool operator()(const Person& a, const Person& b) const
	{
		return a.m_age < b.m_age;
	}
};

//----------------------------------------------------------------------
//a)Before, in c++03 - we had to use a functional object - in another struct
void usingFunctionalObject()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<Person> people;
	people.emplace_back("ccc",24);
	people.emplace_back("aaa",20);
	people.emplace_back("bbb",35);
	people.emplace_back("bbb",25);

	Person p{};
	p.displayIt(people, std::string(">>>>>vector before sort:"));
	std::sort(std::begin(people), std::end(people), ByAge{});
	p.displayIt(people, std::string(">>>>>vector AFTER sort:"));
}

//----------------------------------------------------------------------
//a1)Before, in c++03 - using functional object inside Person struct
void usingFunctionalObjectInternanl()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<Person> people;
	people.emplace_back("ccc",24);
	people.emplace_back("aaa",20);
	people.emplace_back("bbb",35);
	people.emplace_back("bbb",25);

	Person p{};
	p.displayIt(people, std::string(">>>>>vector before sort:"));
	std::sort(std::begin(people), std::end(people), Person());
	p.displayIt(people, std::string(">>>>>vector AFTER sort:"));
}

//----------------------------------------------------------------------
//b)in C++11 - using lambdas  - creates a functional object on the spot
void usingLambda()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<Person> people;
	people.emplace_back("ccc",24);
	people.emplace_back("aaa",20);
	people.emplace_back("bbb",35);
	people.emplace_back("bbb",25);

	Person p{};
	p.displayIt(people, std::string(">>>>>vector before sort:"));
	std::sort(std::begin(people), std::end(people), 
		[](const Person& a, const Person& b)
		{
			return a.m_age < b.m_age;
		});
	p.displayIt(people, std::string(">>>>>vector AFTER sort:"));
}

//----------------------------------------------------------------------
//lambdas + creating assynchronous pipelines of actions
void lambdaPipelines()
{
	auto fut = httpGetRequest("xxxxx.com")
		.then()
		.then()
		.then()
}

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "________________________________"	<< endl;
	usingFunctionalObject();

	cout << "________________________________"	<< endl;
	usingFunctionalObjectInternanl();

	cout << "________________________________"	<< endl;
	usingLambda();

	cout << "________________________________"	<< endl;
	processFields(Person{"ccc",24});

	return 0;
}

