//------------------------------------------------
// description..: studies - lambda functions
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
#include <map>
#include <tuple>
//#include <format>

using namespace std;


//----------------------------------------------------------------------
struct Something
{

	bool initializeNoLambda();
	bool initializeWithLambda();
};

bool initStep0() 
{
	cout << __PRETTY_FUNCTION__ << endl;
	return true;
}

bool initStep1() 
{
	cout << __PRETTY_FUNCTION__ << endl;
	return true;
}

bool Something::initializeNoLambda()
{
	cout << __PRETTY_FUNCTION__ << endl;
	if(!initStep0())
	{
		std::cerr << "Step 0 failed !!!" << endl;
		return false;
	}

	if(!initStep1())
	{
		std::cerr << "Step 1 failed !!!" << endl;
		return false;
	}

	return true;
}

bool Something::initializeWithLambda()
{
	cout << __PRETTY_FUNCTION__ << endl;

	//VIP: CAN'T be & s -> (???) but works if using const & s
	const auto tryStep = 
	[](std::string_view && s, auto f)
	{
		if (f())
			return true;

		cerr << s << " Failed !!!" << endl;
		return false;
	};

	auto res = 	tryStep(std::move(std::string_view("Step-0")), 
				[](){return initStep0();})
		 		&&
				tryStep(std::move(std::string_view("Step-1")), 
				[](){return initStep1();});
		
	return res;
}

//--- using lambdas to avoid repetition ---

//----------------------------------------------------------------------
struct WebSite
{
	std::string m_name;
	std::string m_type;
	std::string m_url;

	WebSite() = default;
	WebSite(string name, string type, string url):
		m_name(name), m_type(type), m_url(url)
	{
	}
};

void printStatusNoLambda(const WebSite* w, string start, string end)
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::cout << start << endl;

	if(!w->m_name.empty())
		std::cout << w->m_name << endl;
	if(!w->m_type.empty())
		std::cout << w->m_type << endl;
	if(!w->m_url.empty())
		std::cout << w->m_url << endl;

	std::cout << end << endl;
}

void printStatusWithLambda(const WebSite* w, string start, string end)
{

	cout << __PRETTY_FUNCTION__ << endl;

	auto field = [](auto&& x) 
		{
			//cout << __PRETTY_FUNCTION__ << endl;
			cout << x << endl;
		};

	auto nullableField = 
		[&](auto&& x) 
		{
			//cout << __PRETTY_FUNCTION__ << endl;
			if (x.size())
				cout << x << endl;
			else
				cout << " " << endl;
		};

	field(start);
	nullableField(w->m_name);
	nullableField(w->m_type);
	nullableField(w->m_url);
	field(end);
}

//----------------------------------------------------------------------
//-deserealizing

/*
struct Json
{
	std::string m_name;
	string m_age;
	std::string m_city;

	Json() = default;
	Json(std::string m_name, std::string m_age)

};
*/
//---no lambda ---
auto deserealizeNoLambda(std::map<std::string,std::string>& j)
{
	auto name = (j.count("name") > 0) ? j["name"] : "not available";
	int age  = (j.count("age") > 0) ? std::stoi(j["age"]) : -1;
	auto city = (j.count("city") > 0) ? j["city"] : "not available";

	return std::make_tuple(name, age, city);
}


//---using lambda ---


auto deserealizeWithLambda(std::map<std::string,std::string>& j)
{

	auto isNumber=[](const std::string &s) 
		{
			return !s.empty() && 
					std::all_of(s.begin(), s.end(), ::isdigit);
		};

	auto setOr = [&](const char * key, auto & dest, auto def)
		{
			//cout << "typeid(res).name()=" << typeid(res).name() << endl;
			//decltype(dest) test000 = dest;
			//cout << "typeid(test000).name()=" << typeid(test000).name() << endl;

			//TODO: FIX CODE BELOW - to accept string & int
			if(j.count(key) > 0)
			{
				//if constexpr (std::is_same_v<decltype(dest), int>)
				if(isNumber(j[key]))
					dest = std::stoi(j[key]);
				else
					dest = j[key];
			} 
			else
			{
				dest = def;
			}
		};

	std::string name{};
	int age{0};
	std::string city{""};

	setOr("name", name, "not available");
	//setOr("age", age, -1); //TODO FIX THIS
	setOr("city", city, "no city");

	return std::make_tuple(name, age, city);
}


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "________________________________"	<< endl;
	Something().initializeNoLambda();

	cout << "________________________________"	<< endl;
	Something().initializeWithLambda();
	
	cout << "________________________________"	<< endl;
	WebSite w{string("XXXXX"), string("forbiden"), 
		string("www.xxxxx.com")};
	printStatusNoLambda(&w, string("START"), string("END"));

	
	cout << "________________________________"	<< endl;
	printStatusWithLambda(&w, string("START"), string("END"));
	
	cout << "________________________________"	<< endl;
	std::map<std::string,std::string> json
		{{"name","Antonio"}, {"age","25"}, {"city","Sao Paulo"}};
	auto t = deserealizeNoLambda(json);	
	cout << "name=" << get<0>(t) << endl;
	cout << "age=" << get<1>(t) << endl;
	cout << "city=" << get<2>(t) << endl;

	cout << "________________________________"	<< endl;
	std::map<std::string,std::string> json2
		{{"name","Antonio"}, {"age","25"}, {"city","Sao Paulo"}};
	auto t2 = deserealizeWithLambda(json2);	
	cout << "name=" << get<0>(t2) << endl;
	cout << "age=" << get<1>(t2) << endl;
	cout << "city=" << get<2>(t2) << endl;




	return 0;
}

