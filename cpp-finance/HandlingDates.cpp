//------------------------------------------------
// description..: handling dates + using boost library
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <boost/date_time/gregorian/gregorian.hpp>

using namespace std;


namespace FinancialData
{

class Date 
{
public:
	enum class DayOfWeek 
	{    
		Sun=0,    Mon=1,    Tue=2,    Wed=3,    Thu=4,    Fri=5,    Sat=6
	};

	Date() = default;
    
    Date(int year, int month, int day):
    	m_year(year), m_month(month), m_day(day)
    {
    }

    Date(const Date& other) = default;
    Date& operator=(const Date& other) = default;
    Date(Date&& other) = default;
    Date& operator=(Date&& other) = default;
    ~Date() = default;

    Date &operator++()
    {
		std::vector<int> monthsWith31 = { 1, 3, 5, 7, 8, 10, 12 };

        if (m_day == 31)
        {
                m_day = 1;
                m_month++;
        }
        else if (m_day == 30 &&
                 std::find(monthsWith31.begin(),
                           monthsWith31.end(), m_month) == monthsWith31.end())
        {
                m_day = 1;
                m_month++;
        }
        else if (m_day == 29 && m_month == 2)
        {
                m_day = 1;
                m_month++;
        }
        else if (m_day == 28 && m_month == 2  && !isLeapYear())
        {
                m_day = 1;
                m_month++;
        }
        else
        {
                m_day++;
        }

        if (m_month > 12)
        {
                m_month = 1;
                m_year++;
        }

        return *this;    	
    }    
    
    bool operator<(const Date &d)
    {  	
		if (m_year < d.m_year) 
			return true;    

		if ( m_year == d.m_year &&
			 m_month < d.m_month) 
			return true;    

		if ( m_year == d.m_year && 
			 m_month == d.m_month && 
			 m_day < d.m_day) 
			return true;    
	
		return false;    
	}    

    bool isLeapYear();
    DayOfWeek getDayOfWeek();    
    int daysInterval(const Date &);    
    bool isTradingDay();

    std::string toStringDate(Date::DayOfWeek day)
    {
    	//TESTS ONLY
    	(void)day;

		switch(day)
	    {
	        case DayOfWeek::Sun: return "Sunday";
	        case DayOfWeek::Mon: return "Monday";
	        case DayOfWeek::Tue: return "Tuesday";
	        case DayOfWeek::Wed: return "Wednesday";
	        case DayOfWeek::Thu: return "Thursday";
	        case DayOfWeek::Fri: return "Friday";
	        case DayOfWeek::Sat: return "Saturday";
	    }
	    throw std::runtime_error("unknown day of week");
	}

private:    
    	int m_year;    
    	int m_month;    
    	int m_day;
};

//----------------------------------------------------------------------
bool Date::isLeapYear()
{
	/*
	if (m_year%4 != 0)
		return false;

	if (m_year%100 != 0)
		return false;

	if (m_year%400 != 0)
		return false;

	return true;
	*/

	return ((m_year%4 == 0)   && 
		    (m_year%100 == 0) && 
		    (m_year%400 == 0)); 
}

//----------------------------------------------------------------------
Date::DayOfWeek Date::getDayOfWeek()
{
 	/*
 	boost::gregorian::date d(m_year, m_month, m_day);
    auto dayOfWeek = d.day_of_week();
    (void)dayOfWeek;
    cout << "dayOfWeek=" << dayOfWeek << endl;
    cout << "d=" << d << endl;
    //TESTS ONLY
	int day = 1;
	return static_cast<Date::DayOfWeek>(day);
	*/

	//got code from these sites:
	//https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Implementation-dependent_methods_of_Sakamoto.2C_Lachman.2C_Keith_and_Craver

	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };  

	auto day = m_day;
	auto month = m_month;
	auto year = m_year;

	year = year - (month < 3);	
    
    auto numDayWeek = (year + year/4 - year/100 + year/400 
    	+ t[month-1] + day) % 7;

    return static_cast<Date::DayOfWeek>(numDayWeek);
}   

//----------------------------------------------------------------------
int Date::daysInterval(const Date& d)
{
	boost::gregorian::date bdate1(m_year, m_month, m_day);    
	boost::gregorian::date bdate2(d.m_year, d.m_month, d.m_day);

	boost::gregorian::date_duration duration = bdate1 - bdate2;    

	return static_cast<int>(duration.days());
}

//----------------------------------------------------------------------
bool Date::isTradingDay()
{
	Date::DayOfWeek dayOfWeek = getDayOfWeek();

	switch(dayOfWeek)
	{
		case DayOfWeek::Sat:
		case DayOfWeek::Sun:
			return true;
		break;

		default:
			return true;
		break;
	}
}

}//namespace - end

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "__________________________________________________" << endl;

	FinancialData::Date myDate(2015, 1, 3); 
	//FinancialData::Date myDate(2002, 1, 10);

	auto dayOfWeek = myDate.getDayOfWeek();
	std::cout << " day of week is="
		<< myDate.toStringDate(dayOfWeek)
		<< std::endl;    

	FinancialData::Date secondDate(2014, 12, 5);    
	++secondDate;  

	// test increment operator    
	++secondDate;    

	int interval = myDate.daysInterval(secondDate);    
	 std::cout << " interval is=" 
	 	<< interval << " days" << std::endl;    

	return 0;	
}

