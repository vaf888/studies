//------------------------------------------------
// file.........: movesemantics001.cpp
// description..: rational numbers 
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <string>
#include <utility>
#include <iostream>  // std::cout, std::endl
#include <cassert>
#include <typeinfo>
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
	Rational & operator = (const Rational &);
	
	Rational(Rational && other) noexcept;
	Rational & operator = (Rational &&) noexcept;

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

private:
	int n_ = 0;
	int d_ = 1;
};

Rational::Rational(const Rational & other) : n_(other.n_), d_(other.d_)
{
	message(">>>>> COPY constructor");
}

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

Rational::Rational(Rational && rhs) noexcept
{
	message(">>>>>move constructor!");
	n_ = std::move(rhs.n_);
	d_ = std::move(rhs.d_);
	rhs.reset();
}

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

ostream& operator<<(ostream& os, const Rational& r)
{
	os << ">>>>>numerator=" << r.n_ << "; denominator=" << r.d_ << endl; 
	return os;
}

void Rational::reset()
{
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

/*
Rational::operator std::string () const
{
	return string();
}

std::string Rational::string() const
{
	return "Tests Only !!!"; 
}
*/

template <typename T>
void swap(T & a, T & b)
{
	message(">>>>>swapp");
	T temp = std::move(a);
	a = std::move(b);
    b = std::move(temp);
}

int main()
{
	Rational a = 7;		// 7/1
    assert((a.getN()==7) && (a.getD()==1));
	message(">>>>> rational number = a");
	cout << a;
	
	Rational b(5,3);	// 5/3
    assert((b.getN()==5) && (b.getD()==3));
	message(">>>>> rational number = b");
	cout << b;

	Rational c = b;     // copy ctor
    assert((c.getN()==5) && (c.getD()==3));
	message(">>>>> rational number = c");
	cout << c;

	Rational d;			// default ctor
    assert((d.getN()==0) && (d.getD()==1));
	message(">>>>> rational number = d");
	cout << d; 
	
	auto e = Rational(a+b);
	cout << e;
	message(">>>>> rational number = e");
	cout << e; 

	// ::swap - to use local swap (not std's one)
	::swap(d,e);
	message(">>>>> rational number = d");
	cout << d; 
	message(">>>>> rational number = e");
	cout << e;

	// using std::swapp()
	std::swap(d,e);
	message(">>>>> rational number = d");
	cout << d; 
	message(">>>>> rational number = e");
	cout << e;
/*
	// using move const - when I do not one available yet
	// the copy ctor will be called
	Rational f = std::move(e);     // copy ctor -> no move available
	message(">>>>> rational number = f");
	cout << f;
*/
	//using move constructor - after it, e (source) will be null !!!
	// std::move(...) -> only cast the reference (&) to a rvalue (&&)
	Rational f = std::move(e); // std:move -> casts e to e&& - so the move ctor will be called
	message(">>>>> rational number = e");
	cout << e;
	message(">>>>> rational number = f");
	cout << f;

	//using move assignment operator
	message(">>>>> rational number = f");
	cout << f;
	Rational g;
	Rational gBefore = g;
	message(">>>>> rational number = g");
	cout << g;
	g = std::move(f);
	message(">>>>> rational number = f");
	cout << f;
	message(">>>>> rational number = g");
	cout << g;
	assert(f == gBefore);

	return 0;
}

