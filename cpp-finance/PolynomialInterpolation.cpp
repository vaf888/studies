//------------------------------------------------
// description..: linear interpolation - using linear equations
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>		// fabs

using namespace std;


//----------------------------------------------------------------------
class PolynomialInterpolation 
{
public:    
	PolynomialInterpolation() = default;    
	PolynomialInterpolation(const PolynomialInterpolation &p) = default;    
	~PolynomialInterpolation() = default;
	PolynomialInterpolation &operator=(const PolynomialInterpolation &p);    

	void setPoints(const std::vector<double> &xpoints, 
				   const std::vector<double> &ypoints)
	{

 		m_x = xpoints;    
 		m_y = ypoints;    

 		// update points to become sorted on x axis.    
 		std::sort(m_x.begin(), m_x.end());    

 		//fix m_y - after m_x was sorted
 		for (size_t i=0; i<m_x.size(); ++i)    
 		{        
 			for (size_t j=0; j<m_x.size(); ++j)        
 			{            
 				if (m_x[i] == xpoints[j])            
 				{                
 					m_y[i] = ypoints[j];                
 					break;            
 				}       
 			}    
 		}

	}

	double getPolynomial(double x)
	{
		double polynomialValue = 0.0;

		for(size_t i=0; i < m_x.size(); ++i)
		{

			//compute the numerator
			double numerator = 1;
			for (size_t j=0; j < m_x.size(); ++j)
			{
				if(j != i)
					numerator *= (x - m_x[j]);
			}

			//denominator
			double denominator = 1;
			for (size_t j=0; j < m_x.size(); ++j)
			{
				if(j != i)
					denominator *= (m_x[i] - m_x[j]);
			}

			// add coeficient for the i-th term
			//P(x) = Y0L0(x) + ... YnLn(x)
			polynomialValue += (m_y[i] * (numerator/denominator));
		}

		return polynomialValue;
	}

private:    
	std::vector<double> m_x;    
	std::vector<double> m_y;
};

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "__________________________________________________" << endl;

/*
	--- via user input ---
	vector<double> xvals;    
	vector<double> yvals;    

	//getting: x0,y0 and x1,y1
	double xi = 0;    
	double yi = 0;    
	while (cin >> xi)    
	{        
		if (xi == -1)        
		{            
			break;        
		}        
		xvals.push_back(xi);        

		cin >> yi;        
		yvals.push_back(yi);    
	}   

	double x = 0;    
	cin >> x;    

	PolynomialInterpolation pi;    
	pi.setPoints(xvals, yvals);    

	double y = pi.getPolynomial(x);    

	cout	<< "Polynomial Interpolation result for value " << x << " is " 
			<< y << endl;    
	
*/

	std::vector<double> xvals{10, 20, 30, 40, 49};
	std::vector<double> yvals{0.6, 0.11, 1.1, 1.62, 1.4};
	double x = 27;
	PolynomialInterpolation pi;    
	pi.setPoints(xvals, yvals);    
	
	double y = pi.getPolynomial(x);    

	cout	<< "Polynomial Interpolation result for value " << x << " is " 
			<< y << endl;    


	return 0;
}

