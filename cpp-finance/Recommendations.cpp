//------------------------------------------------
// description..: perfect forwarding
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>
#include <vector>
#include <map>
#include <utility>

using namespace std;

/*
Many financial institutions such as pension funds and insurance companies, as well as 
etail investors, use analysts’ recommendations as a gauge of the predominant view about a particular stock. This in turn can be used to determine future capital allocation to a portfolio of stocks.

Analyst recommendations come from one of the several institutions that provide public 
analysis of equity investments, generally from some of the major investment banks. 
The recommendation for a particular stock includes a defined action such as “buy,” 
“sell,” or “hold.” 
The recommendation also frequently includes a price target, which determines how much the analyst expects to be the “fair price” for the instrument.

Since there are so many analysts covering the equities market, keeping track of 
recommendations is one of the important parts of the work of an institutional investor. 
In this recipe, you will create a C++ class to store this type of information and to 
answer some basic questions such as “what is the average target price for a particular 
stock?”
*/

//----------------------------------------------------------------------
enum class RecommendationType 
{    
	BUY,    SELL,    HOLD,    NO_RECOMMENDATION
};

//----------------------------------------------------------------------
class Recommendation 
{
public:
    Recommendation() = default;

    Recommendation(const std::string &ticker, RecommendationType rec, double target)
    	:m_ticker(ticker), m_recommendationType(rec), m_targetPrice(target)
    {
    };

    Recommendation(const Recommendation &r) = default;
    Recommendation& operator =(const Recommendation &r) = default;

    Recommendation(Recommendation&& r) = default;
    Recommendation& operator =(Recommendation&& r) = default;

    ~Recommendation() = default;

    double getTarget() const
    {
    	return m_targetPrice;
    }

    RecommendationType getRecommendation() const
    {
    	//TODO: fix this
    	return m_recommendationType;
    }

    std::string getTicker() const
    {
    	return m_ticker;
    }

private:
	std::string m_ticker{};
	RecommendationType m_recommendationType{RecommendationType::NO_RECOMMENDATION};
	double m_targetPrice{0.00};

};

//----------------------------------------------------------------------
class RecommendationsProcessor
{
public:
	RecommendationsProcessor() = default;

	RecommendationsProcessor(const RecommendationsProcessor&) = default;
	RecommendationsProcessor& operator=(const RecommendationsProcessor&) = default;

	RecommendationsProcessor(RecommendationsProcessor&&) = default;
	RecommendationsProcessor& operator=(RecommendationsProcessor&&) = default;

	~RecommendationsProcessor() = default;

	double averageTargetPrice(const std::string &ticker);
	void addRecommendation(const std::string &ticker,RecommendationType rec, double targetPrice);

	void displayIt()
	{
		cout << endl;
		cout << ">>>>>available recommendations:" << endl;
		for(auto r:m_recommendations)
		{
			cout << ">>>ticker=" << r.first << endl;
			
			// display all recommendations for one ticker
			for(auto oneRec:r.second)
			{

				//TODO: fix this !!!!!!!
				//cout << "recommendation type=" << oneRec.getRecommendation() << endl;
				cout << "recommendation type=" << "TESTS ONLY !!!" << endl;
				cout << "targetPrice=" << oneRec.getTarget() << endl;

			}

		}

	}	

private:
	std::map<std::string, std::vector<Recommendation>> m_recommendations;

};

//----------------------------------------------------------------------
void RecommendationsProcessor::addRecommendation(const std::string &ticker,                                                 
												 RecommendationType rec, 
												 double targetPrice)
{    
	Recommendation r(ticker, rec, targetPrice);    
	m_recommendations[ticker].push_back(r);
}

//----------------------------------------------------------------------
double RecommendationsProcessor::averageTargetPrice(const std::string &ticker)
{    
	if (m_recommendations.find(ticker) == m_recommendations.end())        
		return 0.0;    

	auto vrec = m_recommendations[ticker];    

	//auto numRecommendations = m_recommendations[ticker].size();

	//std::vector<double> prices;  
	double totalTickers = 0.0;
	for(auto rc:vrec)  
	{
		totalTickers += rc.getTarget();

	}
	auto avg1 = totalTickers/m_recommendations[ticker].size();
	cout << "avg1 - via loop = " << avg1 << endl;


	//return std::accumulate(prices.begin(), prices.end(), 0) / prices.size();
	auto newTotal = 0.0;
	std::for_each(m_recommendations[ticker].begin(), m_recommendations[ticker].end(), 
			[&](Recommendation & r)
			{
				newTotal += r.getTarget(); 
			});

	auto avg2 = newTotal/m_recommendations[ticker].size();
	cout << "avg2 - via for each = " << avg2 << endl;

	return avg1;
}

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "__________________________________________________" << endl;
	RecommendationsProcessor rp{};
	rp.addRecommendation(std::string("APPLE"), RecommendationType::BUY, 100.00);
	rp.addRecommendation(std::string("APPLE"), RecommendationType::BUY, 200.00);
	rp.addRecommendation(std::string("APPLE"), RecommendationType::BUY, 300.00);
	rp.addRecommendation(std::string("APPLE"), RecommendationType::BUY, 400.00);

	rp.addRecommendation(std::string("YAHOO"), RecommendationType::BUY, 111.22);

	rp.displayIt();

	cout << "__________________________________________________" << endl;
	rp.averageTargetPrice(std::string{"APPLE"});







	//desired usage for the Dictionary class:
	cout << "___________________________________" << endl;

	
	return 0;
}

