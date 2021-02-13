//------------------------------------------------
// description..: finance - FinancialStatement class + smart pointers
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <algorithm>	// for_each
#include <vector>
#include <cmath>		//pow
#include <memory>		// unique_ptr

using namespace std;


class FinancialStatement {
public:
    FinancialStatement() : m_return(0)
    {}

    ~FinancialStatement()
    {}

    FinancialStatement(const FinancialStatement& other) :
    	m_return(other.m_return), m_transactions(other.m_transactions)
    {}


    FinancialStatement &operator=(FinancialStatement& other)
    {
    	if(this != &other)
    	{
    		m_return = other.m_return;
    		m_transactions = other.m_transactions;
    	}

    	return *this;
    }

    double getReturn()
    {
    	return m_return;
    }

    void addTransaction(const std::string& security, double val)
    {

    	 m_transactions.push_back(std::make_pair(security, val));
    }

private:
    double m_return;
    std::vector<std::pair<std::string,double> > m_transactions;
};


std::unique_ptr<FinancialStatement> getSampleStatement()
{    
	//std::unique_ptr<FinancialStatement> fs = = make_unique<FinancialStatement>();
	//auto fs = make_unique<FinancialStatement>(new FinancialStatement()); 
	auto fs{ std::make_unique<FinancialStatement>() };

	fs->addTransaction("IBM", 102.2);    
	fs->addTransaction("AAPL", 523.0);    

	return fs;
}


//----------------------------------------------------------------------
void transferFinancialStatement(std::unique_ptr<FinancialStatement> statement)
{

}


//----------------------------------------------------------------------
int main(int argc, const char * argv[])
{
    return 0;
}


