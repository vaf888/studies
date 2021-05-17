//------------------------------------------------
// file.........: Return000.cpp
// description..: return smart pointer
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <string>
#include <iostream>  // std::cout, std::endl
#include <vector>

using namespace std;


//--------------------------------------------------------------
struct My
{  

//private:
	int m_field1{0};

public:

	My() { cout << ">>>>>My constructor..." << endl; }
	My(int val) : m_field1(val) { cout << ">>>>>My constructor + int..." << endl; }

   ~My() { cout << ">>>>>My destructor..." << endl; }

   My(const My& other) : m_field1(other.m_field1)
   {
		cout << ">>>>>My copy const..." << endl; 
   }

   My& operator = (const My& other)
   {
   		cout << ">>>>>My copy assignment operator..." << endl;  	
   		if(this != &other)
   		{
   			m_field1 = other.m_field1;
   		}

   		return *this;
   	}
			

   My(My&& other) : m_field1(std::move(other.m_field1))
   {
		cout << ">>>>>My move contructor..." << endl; 
   }

   My& operator = (My&& other)
   {
   		cout << ">>>>>My move assignment operator..." << endl;	
   		if(this != &other)
   		{
   			m_field1 = 0;
   			std::swap(m_field1, other.m_field1);
   		}

   		return *this;
   }


};

//--------------------------------------------------------------
std::vector<struct My> getMy() 
{ 
	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	vector<struct My> ret{My(3)};
	
	cout << ">>>>>My function - End !!!" << endl; 

	return ret; 
}

//--------------------------------------------------------------
std::vector<struct My> getMyByMove() 
{ 
	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;

	vector<struct My> ret{My(999)};
	
	cout << ">>>>>My function - End !!!" << endl; 

	return std::move(ret); 
}



//--------------------------------------------------------------
int main()
{

	cout << "\n________________________________________\n";
	cout << __PRETTY_FUNCTION__ << endl;
	auto res = getMy();
	for(auto item : res)
		cout << ">>>>>item=" << item.m_field1 << endl;

	cout << "\n________________________________________\n";
	auto res1 = getMyByMove();
	for(auto item : res)
		cout << ">>>>>item=" << item.m_field1 << endl;

	return 0;
}





