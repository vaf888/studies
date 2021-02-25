//------------------------------------------------
// description..: finance - risk calculator
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <algorithm>	// for_each
#include <vector>
#include <cmath>		//pow
#include <memory>		// unique_ptr/shared ptr

using namespace std;

//----------------------------------------------------------------------------
// these are risk grades, as determined by rating agencies
class CreditRisk 
{   

public: 
    enum class RiskType 
    {        
        AAA,        
        AAPlus,        
        AA,        
        APlus,        
        A,        
        BPlus,        
        B,        
        CPlus,        
        C    
    };


    static std::string toString(const RiskType & rt)
    {
        switch(rt)
        {
            case RiskType::AAA:
                return "AAA";
            break;
            case RiskType::A:
                return "A";
            break;
            case RiskType::APlus:
                return "APlus";
            break;
            case RiskType::BPlus:
                return "BPlus";
            break;
            default:
                return "Other";
            break;
        }
    }
                    

    CreditRisk() = default;

    explicit CreditRisk(RiskType rt) : m_rating(rt)
    {
    }

    RiskType getRating()
    {
        return m_rating;
    }

private:
    RiskType m_rating;

};


//----------------------------------------------------------------------------
// calculates the risk associated to a portfolio
class RiskCalculator 
{
public:    
    RiskCalculator() = default;    
    ~RiskCalculator() = default; 

    
    RiskCalculator(const RiskCalculator &v) : m_creditRisks(v.m_creditRisks)
    {
    }

    RiskCalculator & operator =(const RiskCalculator &v)
    {
        if (this != &v)
        {
            m_creditRisks = v.m_creditRisks;
        }
        return *this;
    }    


    void addCreditRisk(std::shared_ptr<CreditRisk> risk)    
    {
        m_creditRisks.push_back(risk);
    }   

    CreditRisk::RiskType portfolioMaxRisk()   
    {

        CreditRisk::RiskType risk = CreditRisk::RiskType::AAA;    

        for (auto cr:m_creditRisks)    
        {        
            if (cr->getRating() < risk)        
            {            
                risk = cr->getRating();        
            }    
        } 

        return risk;
    }    

    CreditRisk::RiskType portfolioMinRisk()
    {

        CreditRisk::RiskType risk = CreditRisk::RiskType::C;    

        for (auto cr:m_creditRisks)    
        {        
            if (cr->getRating() > risk)        
            {            
                risk = cr->getRating();        
            }    
        } 

        return risk;
    }

    void displayIt()
    {
        cout << "RiskType list:" << endl;
        for(auto rt:m_creditRisks)
        {
            cout << "RiskType=" << CreditRisk::toString(rt->getRating()) << endl;
        }

        cout << endl;
    }

private:    
    std::vector<std::shared_ptr<CreditRisk> > m_creditRisks;
};


//----------------------------------------------------------------------
int main()
{
    RiskCalculator rc;

    auto creditRisk = make_shared<CreditRisk>(CreditRisk::RiskType::AAA);
    rc.addCreditRisk(creditRisk);

    creditRisk = make_shared<CreditRisk>(CreditRisk::RiskType::APlus);
    rc.addCreditRisk(creditRisk);    

    creditRisk = make_shared<CreditRisk>(CreditRisk::RiskType::BPlus);
    rc.addCreditRisk(creditRisk);  

    rc.displayIt();  

    cout << "max risk=" << CreditRisk::toString(rc.portfolioMaxRisk()) << endl;
    cout << "min risk=" << CreditRisk::toString(rc.portfolioMinRisk()) << endl;

    return 0;    // the autopointer is released at the end of the scope...
    
}


