//fixed income - interest rate calculator


//The IntRateCalculator class, determines the calculation of single period interest rates
//general formula: V=P(1+R)
//-V = he future value after a single period
//-P = the present value of the deposit
// (*) With this formula, you can calculate the interest rate for a single period.


#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;


//-----------------------------------------------------------
class IntRateCalculator
{
public:
	explicit IntRateCalculator(double rate);
	
	IntRateCalculator(const IntRateCalculator& other);

	IntRateCalculator& operator=(const IntRateCalculator& other);

	//~IntRateCalculator();

	double singlePeriod(double value);

	//helper function
	bool CompareFloat(double x, double y, double epsilon = 0.0000001f)
	{
	   	if(abs(x - y) < epsilon)
	      return true; 	//they are same
	    return false; 	//they are not same
	}


private:
	double m_rate;
};

//-----------------------------------------------------------
IntRateCalculator::IntRateCalculator(double rate):m_rate(rate)
{}

//-----------------------------------------------------------
IntRateCalculator::IntRateCalculator(const IntRateCalculator& other)
{
	this->m_rate = other.m_rate;
}

//-----------------------------------------------------------
IntRateCalculator& IntRateCalculator::operator=(const IntRateCalculator& other)
{
	if(this != &other)
		this->m_rate=other.m_rate;

	return *this;
}

//-----------------------------------------------------------
double IntRateCalculator::singlePeriod(double pValue)
{
	auto futureValue = pValue * ( 1 + m_rate );
	return futureValue;
}

/*
//-----------------------------------------------------------
int main()
{

	double interestRate=10.0/100.0;
	double presentValue=100.0;
	double expectedValue=presentValue*(1+interestRate);
	IntRateCalculator irc(interestRate);
	auto futureValue = irc.singlePeriod(presentValue);
	assert(irc.CompareFloat(futureValue,expectedValue)==true);

	cout << "presentValue.........=" << presentValue << endl;
	cout << "interestRate.........=" << interestRate << endl;
	cout << "futureValue..........=" << futureValue << endl;

	retunr 0;

}
*/

// the main function receives parameters passed to the program
int main(int argc, const char * argv[])
{   
	if (argc != 3)    
	{        
		std::cout << "usage: progName <interest rate> <value> " << std::endl;
	    return 1;    
	}

	double rate = atof(argv[1]);    
	double value = atof(argv[2]);

	IntRateCalculator irCalculator(rate);    

	double res = irCalculator.singlePeriod(value);    

	std::cout << " result is " << res << std::endl;    

	return 0;
}
