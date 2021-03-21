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
class LinearInterpolation 
{
public:    
	LinearInterpolation() = default;    
	LinearInterpolation(const LinearInterpolation &p) = default;    
	~LinearInterpolation() = default;
	LinearInterpolation &operator=(const LinearInterpolation &p);    

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

	double getValue(double x)
	{
		//points before and after x
		double x0=0, y0=0, x1=0, y1=0;

		// x must be between a valida interval
    	if (x < m_x[0] || x > m_x[m_x.size()-1])
    	{
        	return 0; // outside of domain
    	}

	    for (size_t i=0; i<m_x.size(); ++i)
	    {
	        if (m_x[i] < x)
	        {
	            x0 = m_x[i];
	            y0 = m_y[i];
	        }
	        else if (m_x[i] >= x)
	        {
	            x1 = m_x[i];
	            y1 = m_y[i];
	            break;
	        }
	    }

	    return y0 * (x-x1)/(x0-x1) +  y1 * (x-x0)/(x1-x0);

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

	LinearInterpolation li;    
	li.setPoints(xvals, yvals);    

	double y = li.getValue(x);    

	cout	<< "interpolation result for value " << x << " is " 
			<< y << endl;    
	
	return 0;
}

