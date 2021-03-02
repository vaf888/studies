//------------------------------------------------
// description..: finance - NumVector
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
#include <exception>  
#include <fstream>      //ifstream - file operations
#include <typeinfo>       // operator typeid

using namespace std;

class NumVector 
{
public:    
    NumVector()
    {
        cout << "!!!!!!!!! DEFAULT constructor called !!!" << endl;
    } 

    ~NumVector() = default;   

    NumVector(const NumVector &v): m_values(v.m_values)
    {
        cout << "!!!!!!!!! copy constructor called !!!" << endl;
    }

    NumVector &operator =(const NumVector & v)
    {
        cout << "!!!!!!!!! assignment called !!!" << endl;
        if(this != &v)
        {
            m_values = v.m_values;
        }

        return *this;
    }

    NumVector(NumVector &&v): m_values(v.m_values)
    {
        cout << "!!!!!!!!! MOVE constructor called !!!" << endl;
        v.m_values.clear();
    }

    NumVector &operator =(NumVector&& v)
    {
        cout << "!!!!!!!!! MOVE assignment called..." << endl;
        {
            m_values.clear();
            m_values = v.m_values;
        }

        return *this;
    }

    void add(double val)
    {
        m_values.push_back(val);
    } 

    void removeLast()
    {
        m_values.pop_back();
    }

    double get(int pos) const
    {
        return m_values[pos];
    } 

    size_t size() const
    {
        return m_values.size();
    }

    void displayIt() const
    {
        cout << endl;
        cout << ">>>vector content:" << endl;
        for(auto i:m_values)
            cout << i << endl;
    }

private:    
    std::vector<double> m_values;
};


NumVector operator +(const NumVector &a, const NumVector &b)
{
    if(a.size() != b.size())
    {
        throw new std::runtime_error("error - vectors must have the same size !");
    }

    NumVector res;
    for(size_t i=0; i < a.size(); ++i)
    {
        res.add(a.get(i) + b.get(i));
    }

    return res;
}

NumVector operator -(const NumVector &a, const NumVector &b)
{
    if(a.size() != b.size())
    {
        throw new std::runtime_error("error - vectors must have the same size !");
    }

    NumVector res;
    for(size_t i=0; i < a.size(); ++i)
    {
        res.add(a.get(i) - b.get(i));
    }

    return res;
}

NumVector operator *(const NumVector &a, const NumVector &b)
{
    if(a.size() != b.size())
    {
        throw new std::runtime_error("error - vectors must have the same size !");
    }

    NumVector res;
    for(size_t i=0; i < a.size(); ++i)
    {
        res.add(a.get(i) * b.get(i));
    }

    return res;
}


//----------------------------------------------------------------------
//int main(int argc, const char **argv)
int main()
{
    cout << "main - Starting..." << endl;

    cout << "_______________________" << endl;
    NumVector v1;
    v1.add(10);
    v1.add(20);
    v1.displayIt();

    cout << "_______________________" << endl;
    NumVector v2;
    v2.add(100);
    v2.add(200);
    v2.displayIt();

    cout << "_______________________" << endl;
    NumVector vAdd = std::move(v1 + v2);
    std::cout << "type vAdd=" << typeid(vAdd).name() << '\n';
    vAdd.displayIt();

    cout << "_______________________" << endl;
    NumVector v3;
    v3.add(1000);
    v3.displayIt();

    cout << "_______________________" << endl;
    NumVector v4 = v3;
    v4.add(2000);
    v4.displayIt();

    cout << "main - End !" << endl;

    return 0;
}



