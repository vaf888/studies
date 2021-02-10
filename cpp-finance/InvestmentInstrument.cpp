//------------------------------------------------
// description..: finance - InvestmentInstrument 
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <algorithm>	// for_each
#include <vector>
#include <cmath>		//pow

using namespace std;


//----------------------------------------------------------------------
class IInstrument 
{
	virtual double getMonthlyPayment() = 0;
	virtual double getPrincipal() = 0;
};


//----------------------------------------------------------------------
template <class T>
class IntRateEngine 
{
public:    
		IntRateEngine(){}    
		~IntRateEngine(){}

		IntRateEngine(const IntRateEngine<T> &a) : m_instrument(a.m_instrument)
		{
		}   

		IntRateEngine<T> &operator =(const IntRateEngine<T>& a)
		{

			if (this != &a)    
			{        
				m_instrument = a.m_instrument;    
			}    

			return *this;
		}

		void setInstrument(T &inv);
		double getAnnualIntRate();

private:    
	T m_instrument;
};

//----------------------------------------------------------------------
template <class T>
void IntRateEngine<T>::setInstrument(T& inv)    
{    
	m_instrument = inv;
}

//----------------------------------------------------------------------
template <class T>
double IntRateEngine<T>::getAnnualIntRate()
{    
	double payment = m_instrument.getMonthlyPayment();    
	double principal = m_instrument.getPrincipal();    
	return (12 *payment) / principal;
}

//----------------------------------------------------------------------
class BondInstrument : public IInstrument
{
public:
    BondInstrument() 
    {
    }

    BondInstrument(double principal, double monthlyPayment):
    	m_monthlyPay(monthlyPayment), m_principal(principal)
    {
    }

    ~BondInstrument()
    {
    }
 
    BondInstrument(const BondInstrument &a) : m_monthlyPay(a.m_monthlyPay),
    				m_principal(a.m_principal)
    {
    }
 
    BondInstrument &operator =(const BondInstrument & other)
    {

    	if(this != &other)
    	{
    		m_monthlyPay = other.m_monthlyPay;
    		m_principal = other.m_principal;	
    	}

    	return *this;
    }

    double getMonthlyPayment()
    {
    	return m_monthlyPay;
    }

    double getPrincipal()
    {
    	return m_principal;

    }

private:
    double
        m_monthlyPay,
        m_principal;
};

//----------------------------------------------------------------------
class MortgageInstrument  : public IInstrument
{
public:    
	MortgageInstrument() {}

	MortgageInstrument(double monthlyPay, double propertyValue, double downpayment):
		m_monthlyPay(monthlyPay), m_propertyValue(propertyValue), m_downPayment(downpayment)
	{
	}

	~MortgageInstrument() {}

	MortgageInstrument(const MortgageInstrument &a) : 
		m_monthlyPay(a.m_monthlyPay),
		m_propertyValue(a.m_propertyValue),
		m_downPayment(a.m_downPayment)
	{
	}   


	MortgageInstrument &operator =(const MortgageInstrument& a)
	{
		if (this != &a)
    	{
	        m_downPayment = a.m_downPayment;
	        m_propertyValue = a.m_propertyValue;
	        m_monthlyPay = a.m_monthlyPay;
    	}
    	return *this;		

	}   

	double getMonthlyPayment()
	{
		return m_monthlyPay;
	}   

	double getPrincipal()
	{
		return m_propertyValue - m_downPayment;
	}    
	
private:    
	double	m_monthlyPay,
			m_propertyValue,
			m_downPayment;
};


//----------------------------------------------------------------------
int main(int argc, const char * argv[])
{

	IntRateEngine<BondInstrument> engineForBond;
	BondInstrument bond(40000, 250);
	engineForBond.setInstrument(bond);

    IntRateEngine<MortgageInstrument> engineForMortgage;
    MortgageInstrument mortgage(250, 50000, 5000);
    engineForMortgage.setInstrument(mortgage);

    std::cout << " bond annual int rate: " << engineForBond.getAnnualIntRate()*100 << "%" << std::endl;
    std::cout << " mortgage annual int rate: " << engineForMortgage.getAnnualIntRate()*100 << "%" << std::endl;

    return 0;
}


