//------------------------------------------------
// description..: finance - CompoundIntRateCalculator 
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
class CompoundIntRateCalculator 
{
public:    
	CompoundIntRateCalculator(double rate);
    CompoundIntRateCalculator(const CompoundIntRateCalculator &v);
    CompoundIntRateCalculator &operator =(const CompoundIntRateCalculator &v);
    ~CompoundIntRateCalculator();
	
    double multiplePeriod(double value, int numPeriods);
    double continuousCompounding(double value, int numPeriods);

 private:    
	double m_rate;
};

//----------------------------------------------------------------------
CompoundIntRateCalculator::CompoundIntRateCalculator(double rate)
: m_rate(rate)
{
}

//----------------------------------------------------------------------
CompoundIntRateCalculator::~CompoundIntRateCalculator()
{
}

//----------------------------------------------------------------------
CompoundIntRateCalculator::CompoundIntRateCalculator(const CompoundIntRateCalculator &v)
: m_rate(v.m_rate)
{
}

//----------------------------------------------------------------------
CompoundIntRateCalculator &CompoundIntRateCalculator::operator =(const CompoundIntRateCalculator &v)
{
    if (this != &v)
    {
        this->m_rate = v.m_rate;
    }
    return *this;
}

//----------------------------------------------------------------------
double CompoundIntRateCalculator::multiplePeriod(double value, int numPeriods)
{
    double f = value * pow(1 + m_rate, numPeriods);
    return f;
}


//----------------------------------------------------------------------
double CompoundIntRateCalculator::continuousCompounding(double value, int numPeriods)
{
    double f = value * exp(m_rate * numPeriods);
    return f;
}

//----------------------------------------------------------------------
int main(int argc, const char * argv[])
{
    if (argc != 4)
    {
        std::cout << "usage: progName <interest rate> <present value> <num periods>" << std::endl;
        return 1;
    }

    double rate = atof(argv[1]);
    double value = atof(argv[2]);
    int num_periods = atoi(argv[3]);

    CompoundIntRateCalculator cIRCalc(rate);
    double res = cIRCalc.multiplePeriod(value, num_periods);

    double contRes = cIRCalc.continuousCompounding(value, num_periods);
    std::cout << " future value for multiple period compounding is " << res << std::endl;
    std::cout << " future value for continuous compounding is " << contRes << std::endl;

    return 0;
}


