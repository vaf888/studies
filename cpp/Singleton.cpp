//------------------------------------------------
// description..: singleton
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <random>	//rnadom_device
#include <numeric>	//std::reduce
#include <chrono>   //time
#include <iomanip>  // set precision

using namespace std;

//----------------------------------------------------------------------
// magic singleton - use static initialization
// GetInstance() which now contains a local static variable (magic static). C++11 guarantees that this will be initialized in a thread-safe way
class CSingleton final
{

public:
	static CSingleton& GetIntance();

	CSingleton() = default;
	~CSingleton() = default;

	static void showIt()
	{
		cout << "instance=" << &CSingleton::GetIntance() << endl;
	}

private:
	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;
	CSingleton(CSingleton&&) = delete;
	CSingleton& operator=(CSingleton&&) = delete;


};

CSingleton& CSingleton::GetIntance()
{
	static CSingleton instance;
	return instance;
}

//----------------------------------------------------------------------
class MySingleton
{

public:
	
	static MySingleton * getInstance()
	{
		if(!m_instance)
			m_instance = new MySingleton();

		return m_instance;
	}

	int getData() {return m_data;}
	void setData(int value) {m_data = value;}
	
private:
	MySingleton() : m_data(0) {}

	static MySingleton * m_instance;
	int m_data;
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
MySingleton *MySingleton::m_instance = 0;



//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	CSingleton& c = CSingleton::GetIntance();
	c.showIt();

	CSingleton& c1 = CSingleton::GetIntance();
	c1.showIt();

	CSingleton& c2 = CSingleton::GetIntance();
	c2.showIt();

	//assert((c1==c2)==c));

	MySingleton * m0 = MySingleton::getInstance();
	m0->setData(5);
	cout << "instance=" << "data=" << m0->getData() << "; instance=" << m0 << endl;


	MySingleton * m1 = MySingleton::getInstance();
	//m0->setData(5);
	cout << "instance=" << "data=" << m1->getData() << "; instance=" << m1 << endl;

	MySingleton * m2 = MySingleton::getInstance();
	m0->setData(12345);
	cout << "instance=" << "data=" << m2->getData() << "; instance=" << m2 << endl;
	

	return 0;
}

