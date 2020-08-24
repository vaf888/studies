//------------------------------------------------
// file.........: strc.cpp
// description..: simple string wrapper class 
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include "strc.h"
#include <utility>
#include <iostream>  // std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
#include <algorithm> 
using namespace std;

strc::strc()
{
	cout << ">>>>> default ctor" << endl; 
}

strc::strc(const char * s)
{
	cout << ">>>>> ctor * s - s=" << s << endl; 
	size_t sLen = strnlen(s,MAXLEN);
	_data = new char[sLen + 1];
	_data[sLen]=0;
	memcpy(_data, s, sLen);
}

strc::strc(const strc & other)
{
	cout << ">>>>> copy ctor" << endl; 
	size_t sLen = strnlen(other._data, MAXLEN);
	_data = new char[sLen + 1];
	_data[sLen]=0;
	memcpy(_data, other._data, sLen);
}

strc::strc(strc && other)
{
	cout << ">>>>> move ctor" << endl;
	_data = std::move(other._data); 
}

strc::~strc()
{
	string  dataOut = (_data==nullptr) ? "" : _data;

	cout << ">>>>> destructor ->  data=[" << dataOut << "]"  << endl;
	//cout << __PRETTY_FUNCTION__ << endl;
	
	delete [] _data;
}

strc & strc::operator = (strc other)
{
	cout << ">>>>> copy & swap" << endl;
	swap(other);
	return *this;
}

const char * strc::getData() const
{
	return _data;
}

strc::operator const char * () const
{
	return getData();
}

void strc::swap(strc & other)	
{
	cout << ">>>>> swap" << endl;
	std::swap(this->_data, other._data);	
}

void strc::msg(const char * s)
{
	if(_data)
		cout << __strc_class << s << _data << endl;
	else
		cout << __strc_class << s << endl;
}

/*
// TESTS-ONLY
int main()
{
	return 0;
}
*/

