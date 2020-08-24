//------------------------------------------------
// file.........: tuple.cpp
// description..: tuple - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
//#include <cstring>
//#include <list>
#include <tuple>
#include <stdexcept>
#include <string>
//#include <typeinfo>
 
using namespace std;

void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

void message(const int v[], int n)
{
    cout << "__________________________________" << endl;
    cout << "content=";

    for(auto i=0; i < n; ++i)
    	cout << v[i] << " ";
    cout << endl;
}

template <typename T1, typename T2, typename T3>
void showIt(T1 & t1, T2 & t2, T3 & t3)
{
	cout << endl;
    cout << "__________________________________" << endl;
    cout << "Student name......=" << t3 << endl;
    cout << "Grade value.......=" << t1 << endl;
    cout << "Grade.............=" << t2 << endl;
}

template <>
void showIt<tuple<double, char, std::string>>(T1 & t1, T2 & t2, T3 & t3)
{
	cout << endl;
    cout << "__________________________________" << endl;
    cout << "Student name......=" << t3 << endl;
    cout << "Grade value.......=" << t1 << endl;
    cout << "Grade.............=" << t2 << endl;
}

tuple<double, char, std::string> getStudent(int id)
{
	switch(id)
	{
		case 0:
			return make_tuple(99.0, 'A', "Antonio");
		break;

		case 2:
			return make_tuple(88.0, 'B', "Maria");
		break;

		case 3:
			return make_tuple(77.0, 'C', "Jose");
		break;

		default:
			throw "ERROR: Invalid student id received !";
		break;
	}
}


int main (int argc, char *argv[])
{
	//double gradeValue = 0.0;
	//char grade;
	//std::string studentName="";

	//c++17 - structured binding
	auto [gradeValue, grade, studentName] = getStudent(0);

	auto res = make_tuple(gradeValue, grade, studentName);
	showIt(gradeValue, grade, studentName);

	//message(">>>>> End of Calls !!!");
}

