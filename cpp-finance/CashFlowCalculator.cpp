//------------------------------------------------
// description..: finance - cash flow calculation
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
 	If your code includes mathematical functions (like exp, cos, etc.), you need 
 	to link to the mathematics library libm.so. T
 	his is done, just like for serial compiling, by adding -lm to the end of your 
 	compile command, that is: 

    g++ -o sample sample.c -lm


*/


//----------------------------------------------------------------------
class CashFlowCalculator 
{
public:    
	// constructors
	CashFlowCalculator(double rate): m_rate(rate)
	{}

	CashFlowCalculator(const CashFlowCalculator &v): m_rate(v.m_rate)
	{}

	~CashFlowCalculator()
	{}

    CashFlowCalculator & operator =(const CashFlowCalculator &v)
    {    
    	if (this != &v)    
    	{        
    		this->m_cashPayments = v.m_cashPayments;        
    		this->m_timePeriods = v.m_timePeriods;        
    		this->m_rate = v.m_rate;    
    	}    

    	return *this;
    }	



	//used to add new payments to the desired cash flow
	void addCashPayment(double value, int timePeriod);
	
	double presentValue();
	
private:    
	std::vector<double> m_cashPayments;
	std::vector<int> m_timePeriods;
	double m_rate;
	
	//to compute the PV or the whole cash flow
	//futureValue = the value of the payment
	//timePeriod  = when this payment occurs
	double presentValue(double futureValue, int timePeriod);
};

//----------------------------------------------------------------------
void CashFlowCalculator::addCashPayment(double value, int timePeriod)
{
	m_cashPayments.push_back(value);
    m_timePeriods.push_back(timePeriod);	
}


//----------------------------------------------------------------------
//used to calculate the PV for a single payment
double CashFlowCalculator::presentValue(double futureValue, int timePeriod)
{

	double pValue = futureValue / pow(1+m_rate, timePeriod);   

	std::cout << " value " << pValue << std::endl;    

	return pValue;	
}

//----------------------------------------------------------------------
double CashFlowCalculator::presentValue()
{

	double total = 0;    

	for (size_t i=0; i<m_cashPayments.size(); ++i)
	{        
		total += presentValue(m_cashPayments[i], m_timePeriods[i]);    
	}    

	return total;	
}


//----------------------------------------------------------------------
int main(int argc, char * argv[])
{


	/*
		Calculating Present Value in C++
		The standard procedure is to denote values paid by the two parties 
		using positive and negative signs. 
		..For example, we can denote an initial loan as a negative number, 
		  and each payment of the loan as a positive number. 
		..Using this approach, for a cash flow from two parties to be equivalent, 
		  the present value of all cash transfers needs to add to zero.
	*/

    
	cout << ">>>>>main() ..." << endl;
	
	if (argc != 2)
    {
        std::cout << "usage: progName <interest rate>" << std::endl;
        return 1;
    }

    double rate = atof(argv[1]);

    CashFlowCalculator cfc(rate);
    do 
    {
        int period;
        cout << endl << "-> period:";
        std::cin >> period;
        if (period == -1) 
        {
            break;
        }

        double value;
        cout << "-> value:";
        std::cin >> value;

        cout << endl;

        cfc.addCashPayment(value, period);

    } while (1);

    double result = cfc.presentValue();

    std::cout << " The present value is " << result << std::endl;

    return 0;	



	cout << ">>>>>main() - End !" << endl;

	return 0;

}
