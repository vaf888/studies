//------------------------------------------------
// description..: TimeSeriesTransformations
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

/*

*/

//----------------------------------------------------------------------
class TimeSeriesTransformations 
{
public:    
	TimeSeriesTransformations() = default;
	TimeSeriesTransformations(std::vector<double> v):m_prices(std::move(v))
	{
	}    

	TimeSeriesTransformations(const TimeSeriesTransformations& other) = default;
	TimeSeriesTransformations& operator=(const TimeSeriesTransformations& other) = default;

	TimeSeriesTransformations(TimeSeriesTransformations&& other) = default;
	TimeSeriesTransformations& operator=(TimeSeriesTransformations&& other) = default;    

	~TimeSeriesTransformations() = default;

	void reducePrices(double val)
	{
		cout << __PRETTY_FUNCTION__ << endl;

		for_each(m_prices.begin(), m_prices.end(),
			[&val](double& originalValue) { originalValue -= val;});
	}

	//using range
	void reducePrices2(double val)
	{
		cout << __PRETTY_FUNCTION__ << endl;

		for(auto & price:m_prices)
			price -= val;

	}

	void increasePrices(double val)
	{
		cout << __PRETTY_FUNCTION__ << endl;

		for_each(m_prices.begin(), m_prices.end(),
			[&val](double& originalValue) { originalValue += val;});
	}   

	void removePricesLessThan(double val)
	{
		//using ERASE-REMOVE idiom		
		m_prices.erase(std::remove_if(m_prices.begin(), m_prices.end(), 
			[&](double& originalValue) 
			{ 
				return (originalValue < val) ? true : false;
			}), // the remove
		m_prices.end()); // the erase
	}   


	void removePricesGreaterThan(double val); // TODO - similar to lessThan

	double getFirstPriceLessThan(double val)   
	{
			for(auto el:m_prices)
			{
				if(el < val)
					return el;
			}

			return -1.0;
	}

	void addValue(double val)
	{
		m_prices.emplace_back(val);
	}   

	void addValues(const std::vector<double> &values)
	{
		for(auto el:values)
			m_prices.emplace_back(el);
	}

	void displayIt(std::string label="")
	{
		cout << ">>>>>" << label << ":" << endl;
		for_each(m_prices.begin(), m_prices.end(),
			[](double& val)
			{
				cout << val << " ";
			});
		cout << endl;
	}

	bool checkAllValues(std::vector<double>&& expected)
	{
		auto checkAll = [&]() 
						{
							for(auto i{0}; i< static_cast<int>(m_prices.size()); ++i)
							{
								if(!isEqual(m_prices[i], expected[i]))
									return false;
							}
							return true;	
						};

		return checkAll();
	}
private:    
	std::vector<double> m_prices;

	bool isEqual(double v1, double v2, double epsilon = 0.00001L)
	{
    	return (fabs(v1 - v2) < epsilon);
	}
};


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<double> vd{100.0, 110.0, 120.0,130.0, 140.0};
	TimeSeriesTransformations ts(vd);

	cout << "__________________________________________________" << endl;
	ts.displayIt("BEFORE reducing of 2.00");
	ts.reducePrices(2.00);
	ts.displayIt("AFTER reducing of 2.00");
	std::vector<double> expected{98.0, 108.0, 118.0, 128.0, 138.0};
	assert(ts.checkAllValues(std::move(expected))==true);

	cout << endl;
	cout << "__________________________________________________" << endl;
	ts.displayIt("BEFORE increasing prices of 2.00");
	ts.increasePrices(2.00);
	ts.displayIt("AFTER increasing prices of 2.00");
	std::vector<double> expected1{100.0, 110.0, 120.0,130.0, 140.0};
	assert(ts.checkAllValues(std::move(expected1))==true);

	cout << endl;
	cout << "__________________________________________________" << endl;
	ts.displayIt("BEFORE reducing of 3.00");
	ts.reducePrices2(3.00);
	ts.displayIt("AFTER reducing of 2.00");
	std::vector<double> expected2{97.0, 107.0, 117.0, 127.0, 137.0};
	assert(ts.checkAllValues(std::move(expected2))==true);

	cout << endl;
	cout << "__________________________________________________" << endl;
	//setup
	TimeSeriesTransformations ts3(vd);
	//act
	ts3.displayIt("BEFORE removePricesLessThan 120.0");
	ts3.removePricesLessThan(125.0);
	ts3.displayIt("AFTER removePricesLessThan 120.0");
	//assert
	std::vector<double> expected3{130.0, 140.0};
	assert(ts3.checkAllValues(std::move(expected3))==true);

	cout << endl;
	cout << "__________________________________________________" << endl;
	//setup
	TimeSeriesTransformations ts4(vd);
	//act
	ts4.displayIt("BEFORE removePricesLessThan 50.0");
	ts4.removePricesLessThan(50.0);
	ts4.displayIt("AFTER removePricesLessThan 50.0");
	//assert
	std::vector<double> expected4{100.0, 110.0, 120.0,130.0, 140.0};
	assert(ts4.checkAllValues(std::move(expected4))==true);

	cout << endl;
	cout << "__________________________________________________" << endl;
	//setup
	std::vector<double> vd5{100.0, 110.0, 85.0, 130.0, 140.0};
	TimeSeriesTransformations ts5(vd5);
	//act
	ts5.displayIt("BEFORE getFirstPriceLessThan 90.0");
	double result5 = ts5.getFirstPriceLessThan(90.0);
	ts5.displayIt("AFTER getFirstPriceLessThan 90.0");
	cout << "result5=" << result5 << endl;
	//assert
	double expected5=85.0; // need better compare functions - TODO
	assert((result5 >= expected5) && ((result5 <= expected5 + 1.0)));
	cout << "___________________________________" << endl;

	cout << endl;
	cout << "__________________________________________________" << endl;
	//setup
	TimeSeriesTransformations ts6(vd);
	//act
	ts6.displayIt("BEFORE addValue 123.0");
	ts6.addValue(123.0);
	ts6.displayIt("AFTER raddValue 123.0");
	//assert
	std::vector<double> expected6{100.0, 110.0, 120.0,130.0, 140.0, 123.0};
	assert(ts6.checkAllValues(std::move(expected6))==true);

	cout << endl;
	cout << "__________________________________________________" << endl;
	//setup
	TimeSeriesTransformations ts7(vd);
	std::vector<double> vd7{123.0, 456.0, 789.0};

	//act
	ts7.displayIt("BEFORE addValues {123.0, 456.0, 789.0}");
	ts7.addValues(vd7);
	ts7.displayIt("AFTER raddValues {123.0, 456.0, 789.0}");
	//assert
	std::vector<double> expected7{100.0, 110.0, 120.0,130.0, 140.0, 123.0, 456.0, 789.0};
	assert(ts7.checkAllValues(std::move(expected7))==true);

	
	return 0;
}

