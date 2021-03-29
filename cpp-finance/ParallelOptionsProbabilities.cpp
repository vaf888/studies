//------------------------------------------------
// description..: ParallelOptionsProbabilities - multi-threading
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <utility>
#include <cmath>		// fabs
#include <future>
#include <chrono>
#include <boost/random/normal_distribution.hpp>
#include <boost/random.hpp>

using namespace std;

static boost::rand48 random_generator; 

//----------------------------------------------------------------------
class RandomWalkThread
{
public:

	RandomWalkThread() = default;

    RandomWalkThread(int num_steps, double sigma, double startPrice)
    	: m_numberOfSteps(num_steps),  m_sigma(sigma),  m_startingPrice(startPrice)
    {
    }

    ~RandomWalkThread()
    {
    }

    double runIt()
    {
		cout << ">>>>>running thread=" << std::this_thread::get_id() << endl;    
		int nAbove = 0;    
		for (int i=0; i<m_numberOfSteps; ++i)    
		{        
			double val = getLastPriceOfWalk();        

			if (val >= m_startingPrice)        
			{            
				nAbove++;        
			}    
		}    

		m_result = nAbove/(double)m_numberOfSteps;
		return m_result;
    }

    double gaussianValue(double mean, double sigma)
	{    
		boost::random::normal_distribution<> distrib(mean, sigma);
		return distrib(random_generator);
	}    

    double getLastPriceOfWalk()
    {

		double prev = m_startingPrice;    

		for (int i=0; i<m_numberOfSteps; ++i)    
		{        
			double stepSize = gaussianValue(0, m_sigma);        

			int r = rand() % 2;        

			double val = prev;        

			if (r == 0) 
				val += (stepSize * val);        
			else 
				val -= (stepSize * val);        

			prev = val;    
		}    

		return prev;
    }

    double result()
    {
    	return m_result;
    }


private:
    int m_numberOfSteps;     // number of steps
    double m_sigma;          // size of each step (in percentage)
    double m_startingPrice;  // starting price

    double m_result;
};


//----------------------------------------------------------------------
class ParallelOptionsProbabilities  
{
public:   

 	ParallelOptionsProbabilities() = default;

	ParallelOptionsProbabilities(int size, double start, double step)
		: m_numSteps(size),
		  m_step(step),
  		  m_strikePrice(start) 
    {
    }

	ParallelOptionsProbabilities(const ParallelOptionsProbabilities &p) :
			m_numSteps(p.m_numSteps),
			m_step(p.m_step),
  			m_strikePrice(p.m_strikePrice)
  	{
  	}

	~ParallelOptionsProbabilities()
	{
	}

	ParallelOptionsProbabilities &operator=(const ParallelOptionsProbabilities &p)
	{
		if (this != &p)    
		{        
			m_numSteps = p.m_numSteps;        
			m_strikePrice = p.m_strikePrice;        
			m_step = p.m_step;    
		}    

		return *this;		
	}

	
	double probFinishAboveStrike()
	{
		constexpr int NumThreads = 20;

	    //vector<std::future<double>> threads(numThreads);
	    vector<std::future<double>> threads{};

	    for(int i=0; i < NumThreads; ++i)
	    {
			threads.push_back
			(std::move(std::async(std::launch::async, &RandomWalkThread::runIt, 
						new RandomWalkThread(m_numSteps, m_step, m_strikePrice))
					  )
			);
		}

		//std::this_thread::sleep_for(1s);

	    double nAbove = 0;
	    cout << ">>>>>threads.size()=" << threads.size() << endl;
	    for (auto & t : threads) 
	    {
	    	try
	    	{
	    		cout << ">>>>>future - getting results !!!" << endl;
	    		auto res = t.get();
	    		cout << ">>>>>future - res=" << res << endl;

	        	nAbove += res;

	        	//delete threads[i];
	        }
			catch (const std::future_error& e) 
			{
        		std::cout << "Caught a future_error with code \"" << e.code()
                  << "\"\nMessage: \"" << e.what() << "\"\n";
    		}	        
	    }

	    return nAbove/(double)(NumThreads);
	}

/*
	double probFinishAboveStrike()
	{
		const int numThreads = 5;

	    vector<std::future<double>> threads(numThreads);

	    for (int i=0; i<numThreads; ++i)
	    {

			auto randomWalkThread =
	    		new RandomWalkThread(m_numSteps, m_step, m_strikePrice);

	    	threads.push_back
	    		(
	    			std::async(std::launch::async, &RandomWalkThread::runIt, randomWalkThread)
	    		);
	    }

	    double nAbove = 0;

	    for (auto & t : threads) 
	    {
	    	try
	    	{
	        	nAbove += t.get();
	        	//delete threads[i];
	        }
			catch (const std::future_error& e) 
			{
        		std::cout << "Caught a future_error with code \"" << e.code()
                  << "\"\nMessage: \"" << e.what() << "\"\n";
    		}	        
	    }

	    return nAbove/(double)(numThreads);
	}

*/

private:    
	int m_numSteps;       // number of steps    
	double m_step;        // size of each step (in percentage)    
	double m_strikePrice; // starting price
};


// nm /usr/lib/x86_64-linux-gnu/libm.a --defined-only | grep fmax
//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "__________________________________________________" << endl;

	ParallelOptionsProbabilities rw(100, 50.0, 52.0);    

	double r = rw.probFinishAboveStrike();    

	cout << " result is " << r << endl;

	return 0;
}

