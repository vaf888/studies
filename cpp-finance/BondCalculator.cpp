//------------------------------------------------
// description..: finance - bond calculator 
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

/*
	-Bonds are structured in such a way that the investor deposits the principal 
	 value at the beginning of the term of the bond. 
	-Frequently, the principal is repaid in its entirety at maturity. 
	 Between the period between the initial investment and its maturity, investors 
	 are paid a constant value, also called the coupon value, which determines 
	 the interest rate paid by the bond.

	 For example, consider a 30-year, $100,000 bond investment in company XYZ, with an 
	 annual coupon of $5,000. 
	 This translates into a fixed income investment that pays a 5% interest on the 
	 principal. Company XYZ has the right to use the principal during the specified 
	 period of time, and the total value of the principal is returned to the 
	 investor in 30 years at maturity.
*/


//----------------------------------------------------------------------
class BondCalculator 
{
public:
	BondCalculator(const std::string institution, int numPeriods, double principal, 
	double couponValue);
	BondCalculator(const BondCalculator& v);
	BondCalculator &operator =(const BondCalculator& v);
	~BondCalculator();

	double interestRate();

	void showIt()
	{
		cout << "________________________________" << endl;
		cout << "parameters received" << endl;
	    cout << "issue=" << m_institution << endl;
	    cout << "principal=" << m_principal << endl;
	    cout << "coupon=" << m_coupon << endl;
	    cout << "num_periods=" << m_numPeriods << endl << endl;
	}

private:
	std::string m_institution;
	double m_principal{0.0};
	double m_coupon{0.0};
	int m_numPeriods{0};
};

//----------------------------------------------------------------------
BondCalculator::BondCalculator(const std::string institution,
                               int numPeriods, double principal, double couponValue)
: m_institution(institution),
  m_principal(principal),
  m_coupon(couponValue),
  m_numPeriods(numPeriods)
{
}

//----------------------------------------------------------------------
BondCalculator::BondCalculator(const BondCalculator& v)
: m_institution(v.m_institution),
  m_principal(v.m_principal),
  m_coupon(v.m_coupon),
  m_numPeriods(v.m_numPeriods)
{
}

//----------------------------------------------------------------------
BondCalculator::~BondCalculator()
{
}

//----------------------------------------------------------------------
BondCalculator &BondCalculator::operator =(const BondCalculator& v)
{
    if (this != &v)
    {
        this->m_institution = v.m_institution;
        this->m_principal = v.m_principal;
        this->m_numPeriods = v.m_numPeriods;
        this->m_coupon = v.m_coupon;
    }
    return *this;
}

//----------------------------------------------------------------------
double BondCalculator::interestRate()
{
    return m_coupon / m_principal;
}


//----------------------------------------------------------------------
int main(int argc, const char * argv[])
{    
	if (argc != 5)    
	{	std::cout << "usage: progName <institution> <principal> <coupon> <num periods>" << std::endl;
        return 1;
    }    
	
	std::string issuer = argv[1];
    double principal = atof(argv[2]);
    double coupon = atof(argv[3]);
	int num_periods = atoi(argv[4]);
	
    BondCalculator bc(issuer, num_periods, principal, coupon);
    bc.showIt();

	cout << ">>>>>" << endl;
    std::cout << "reading information for bond issued by " << issuer << std::endl;
    std::cout << "the internal rate of return is " << bc.interestRate() << std::endl;
    
	return 0;
}