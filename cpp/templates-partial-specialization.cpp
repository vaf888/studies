//------------------------------------------------
// file.........: templates-partial-specialization.cpp
// description..: templates - general studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <type_traits>

using namespace std;






void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

void swap(char & c1, char & c2)
{
	char tmp = c1;
	c1 = c2;
	c2 = tmp;
}

template<typename T, typename U>
class Pair
{
	public:
		Pair():a(), b(){}
		Pair(T a1, U b1):a(a1), b(b1)
		{
			cout << ">>>>> using base specialization (2 parms) !" << endl;
		}

		T first() {return a; }
		U second() {return b;}
	private:
		T a;
		U b;
};

///////////////////////////////////////////////
// Partial specialization for T= std::string
template<typename U>
class Pair<std::string, U>
{
	public:
		Pair():a(), b(){}
		Pair(std::string a1, U b1):a(a1), b(b1)
		{
			cout << ">>>>> using string specialization !" << endl;
		}

		std::string first() {return a; }
		U second() {return b;}
	private:
		std::string a;
		U b;
};

///////////////////////////////////////////////
// Partial specialization -> both template parms of one type
template<typename U>
class Pair<U, U>
{
	public:
		Pair():a(), b(){}
		Pair(U a1, U b1):a(a1), b(b1)
		{
			cout << ">>>>> using one type parm specialization !" << endl;
		}

		U first() {return a; }
		U second() {return b;}
	private:
		U a;
		U b;
};


////////// function specialization ////////////////
template <typename T>
T  max1(T a, T b)
{
	cout << ">>>>>in primary template..." << endl;
	return a >= b ? a : b;
}

template<>
double max1(double a, double b)
{
	cout << ">>>>>in DOUBLE specialization" << endl;
	return a >= b ? a : b;
}

template<>
int * max1(int * a, int * b)
{
	cout << ">>>>>in INT * specialization" << endl;
	return (*a) >= (*b) ? a : b;
}
 
/*
template<>
const double& max1(const double& a, const double& b)
{
	cout << ">>>>>in double specialization" << endl;
	return a >= b ? a : b;
}

template<>
const int * max1(const int * a, const int * b)
{
	cout << ">>>>>in pointer specialization" << endl;
	return ((*a) >= (*b)) ? a : b;
}
*/

int main()
{
	Pair<int,int> p1(1,2);
	cout << "first=" << p1.first() << "; second=" << p1.second() <<endl;


	Pair<double, double> p2(55.0,99.0);
	cout << "first=" << p2.first() << "; second=" << p2.second() <<endl;

	// using specialized version for string
	Pair<std::string, double> p3("hello",9999.0);
	cout << "first=" << p3.first() << "; second=" << p3.second() <<endl;

	// using only one parm specialized version
	Pair<int, int> p4(123, 456);
	cout << "first=" << p4.first() << "; second=" << p4.second() <<endl;

	cout << ">>>>> using function specialization..." << endl;

	cout << "...int type" << endl;
	int a=5, b=6;
	int res0 = max1(a,b);
	cout << "result=" << res0 << endl;

	cout << "...double type" << endl;
	double c=7.5d, d=8.5d;
	double res1 = max1(c,d);
	cout << "result=" << res1 << endl;

	cout << "...int * type" << endl;
	int * res2 = max1(&a, &b);
	cout << "result=" << res2 << endl;

/*
	cout << "...int * type" << endl;
	int * res2 = max1(&a, &b);
	cout << "result=" << res2 << endl;
*/

	//double c=7.0d, d=8.0d;

	//double res1 = max1(c, d);
	//cout << "result=" << res1 << endl;

	//int * res3 = max(&a, &b);
	//cout << "result=" << res3 << endl;

	message(">>>>> End of Calls !!!");

	return 0;
}

