//------------------------------------------------
// file.........: movesemantics002.cpp
// description..: rational numbers + using copy-and-swap idiom
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

// copy & swap idiom:
// goal: to have just one assigment operator (parm. by value)
//       which will be used as 
//       move assignemet operator and regular assignment operator !!!
//

#include <string>
#include <utility>
#include <iostream>  // std::cout, std::endl
#include <cassert>
#include <typeinfo>
#include <algorithm> 
using namespace std;

void message(const string & s)
{
	cout << "__________________________________" << endl;
    cout << s << endl;
}

class Rational
{

public:
	Rational() {reset(); message(">>>>> default constructor");}
	Rational(const int & numerator) : n_(numerator) { message(">>>>> int constructor");}
	Rational(const int & numerator, const int & denominator) : n_(numerator), d_(denominator) { message(">>>>> int,int constructor");}
	~Rational() {message(">>>>> destructor;");}

	Rational(const Rational & other); 
	//change required by the copy & swap idiom
	//Rational & operator = (const Rational &);
	Rational & operator = (Rational);
	
	Rational(Rational && other) noexcept;
	// removed - change required by the copy & swap idiom
	//Rational & operator = (Rational &&) noexcept;

	Rational operator + (const Rational &) const;
	Rational operator - (const Rational &) const;
	Rational operator * (const Rational &) const;
	Rational operator / (const Rational &) const;

	bool operator == (const Rational &) const;
	//operator std::string (std::ostream&, const Rational&) const {return "Tests Only";}
	//std::string string() const;
	friend ostream& operator<<(ostream& os, const Rational& r);

	void reset();
	inline int getN() const {return n_;}
	inline int getD() const {return d_;}
	void swap(Rational & r);

private:
	int n_ = 0;
	int d_ = 1;
};

Rational::Rational(const Rational & other) : n_(other.n_), d_(other.d_)
{
	message(">>>>> COPY constructor");
}

// required by the copy and swap idiom
void Rational::swap(Rational & r)
{
	std::swap(n_, r.n_);
	std::swap(d_, r.d_);
}

//copy & swap idiom: change regular operator = 
/*
Rational & Rational::operator = (const Rational & rhs)
{
	message(">>>>>assignment operator!"); 
	if(this != &rhs)
	{
		n_ = rhs.n_;
		d_ = rhs.d_;
	}
	return *this;
}
*/
//CONCLUSION:
//-this is the move assignement and assignment operator ALL in one !!!
Rational & Rational::operator = ( Rational rhs)
{
	message(">>>>>copy & swap operator"); 
	swap(rhs);
	
	return *this;
}

Rational::Rational(Rational && rhs) noexcept
{
	message(">>>>>move constructor!");
	n_ = std::move(rhs.n_);
	d_ = std::move(rhs.d_);
	rhs.reset();
}

// removed - change required by the copy & swap idiom
/*
Rational & Rational::operator = (Rational && rhs) noexcept
{
	message(">>>>>move assignment operator!"); 
	if(this != &rhs)
	{
		n_ = std::move(rhs.n_);
		d_ = std::move(rhs.d_);
		rhs.reset();
	}
	
	return *this;
}
*/

ostream& operator<<(ostream& os, const Rational& r)
{
	os << ">>>>>numerator=" << r.n_ << "; denominator=" << r.d_ << endl; 
	return os;
}

void Rational::reset()
{
	message(">>>>> in reset()");
	n_=0;
	d_=1;
}

Rational Rational::operator + (const Rational & rhs) const
{
	return Rational((n_*rhs.d_) + (d_*rhs.n_), d_*rhs.d_);
}

Rational Rational::operator - (const Rational & rhs) const
{
	return Rational((n_*rhs.d_) - (d_*rhs.n_), d_*rhs.d_);
}

Rational Rational::operator * (const Rational & rhs) const
{
	return Rational((n_*rhs.n_), d_*rhs.d_);
}

Rational Rational::operator / (const Rational & rhs) const
{
	return Rational((n_*rhs.d_), d_*rhs.n_);
}

bool Rational::operator == (const Rational & rhs) const
{
	message("DEBUG: in operator ==...");
	return ( (d_==rhs.d_) && (n_==rhs.n_)); 
}

template <typename T>
void swap(T & a, T & b)
{
	message(">>>>>swap");
	T temp = std::move(a);
	a = std::move(b);
    b = std::move(temp);
}

int main()
{

	// i) using the copy & swap as move assignment operator
	message(">>>>> Before  b = std::move(a) !!!!!!!!!!!!!!!!!!!!!!!!!!");
	Rational a(5,3);	// 5/3
    assert((a.getN()==5) && (a.getD()==3));
	message(">>>>> rational number = a");
	cout << a;
	
	Rational b(9,5);	// 9/5
    assert((b.getN()==9) && (b.getD()==5));
	message(">>>>> rational number = b");
	cout << b;

	message("DEBUG: will call now b = std::move(a) ");
	b = std::move(a);
	message("DEBUG: back from  b = std::move(a) ");

	message(">>>>> After  b = std::move(a) !!!!!!!!!!!!!!!!!!!!!!!!!!");
	message(">>>>> rational number = a");
	cout << a;
	message(">>>>> rational number = b");
	cout << b;

	// ii) using the copy & swap as copy assignment
	message(">>>>> Before d=c !!!!!!!!!!!!!!!!!!!!!!!!!!");
	Rational c(7,8);	
    assert((c.getN()==7) && (c.getD()==8));
	message(">>>>> rational number = c");
	cout << c;
	
	Rational d(9,10);
    assert((d.getN()==9) && (d.getD()==10));
	message(">>>>> rational number = d");
	cout << d;

	d = c;

	message(">>>>> After d=c !!!!!!!!!!!!!!!!!!!!!!!!!!");
	message(">>>>> rational number = c");
	cout << c;
	
	message(">>>>> rational number = d");
	cout << d;

	return 0;
}

