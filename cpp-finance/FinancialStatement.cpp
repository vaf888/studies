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

    ~FinancialStatement() = default;
    
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
    	//m_transactions.push_back(std::make_pair(security, val));
        m_transactions.emplace_back(std::make_pair(security, val));

    }

    friend std::ostream& operator<<(std::ostream& out, const FinancialStatement& fs);


private:
    double m_return;
    std::vector<std::pair<std::string,double> > m_transactions;
};

//----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& out, const FinancialStatement& fs)
{
    std::string trxs="";
    for (auto pair:fs.m_transactions)
    {
        trxs += ("ticket=" + pair.first + " -> value=" + std::to_string(pair.second) + "\n");
    }

    out << "m_return=" << fs.m_return << endl;
    out << trxs << endl;

    return out;
}

//----------------------------------------------------------------------------
std::unique_ptr<FinancialStatement> getSampleStatement()
{    
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

    auto fs = std::move(getSampleStatement());

    cout << "return=" << std::to_string(fs->getReturn()) << endl;

    cout << "financial statement content..." << endl;
    cout << *fs << endl;

    fs->addTransaction(std::move("GOOGLE"), 999.0);

    cout << "NEW financial statement content..." << endl;
    cout << *fs << endl;


    // do some real work here...    

    return 0;    // the autopointer is released at the end of the scope...
    
}


