//------------------------------------------------
// description..: resource management - passing smart pointers
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>

using namespace std;

/*
	smart pointers - uses:

	a) uses object, may modify, may be null
	void use(T* p);

	b)uses object, MAY NOT modify it, may be null !!!
	void use(const T* p);

	c)uses object, MAY modify it, -> reference -> can't be NULL
	void use(T& p);

	d)uses object, MAY NOT modify it, -> reference -> can't be NULL
	void use(const T& p);

	(*)  prefer reference type, if the parameter cannot be null
	(**) prefer user const and only user POINTER IF THE value may be NULL


	--- MAY SHARE case ---
	void may-share(const shared_ptr<T>& p); // might retain refcont
    (*) indicates to the user that you:
        ..may chose to make a copy

        i) can't change pointer value if : const shared_ptr<int>& p
           auto tmp = make_shared<int>(99999);
           p = tmp; >>>>>>>>>>>>>>>> ERROR if const (OK, if not const!!!)
*/


//----------------------------------------------------------------------
// this prototype: allows function to decide if it needs to share ownership
// (*) const shared_ptr<T>&  -> appeart const (the pointer is const) but
//	   it allows to change the pointed object !!!
// (**) const shared_ptr<const T>& t -> THIS IS ACTULLY CONST OBJ
//
// (***) But I can create new pointers (share from the p pointer below); e.g.:
//         auto p1 = p; // this will also increment the p use_count !!!
void mayShare(const shared_ptr<int>& p, const shared_ptr<const int>& pConstObj)
{

	cout << __PRETTY_FUNCTION__ << endl;

	std::cout << "p.use_count() - before == " << p.use_count() << '\n'; 

	std::cout << "p.use_count() - after == " << p.use_count() << '\n'; \

    // !!! ERROR : can't change pointer p it is CONST !!!
    //     (*) if I remove the const it works OK !!!
	//auto tmp = make_shared<int>(888);	
	//p = tmp;

	// OK - this is not a const object
	*p = 99;

	// ERROR - const obj - can't change it
	// error: assignment of read-only location
	//*pConstObj = 10;

	cout << "*p=" << *p << endl;
	cout << "*pConstObj=" << *pConstObj << endl;
}

//----------------------------------------------------------------------
void share( shared_ptr<int>& p)
{

	cout << __PRETTY_FUNCTION__ << endl;
	// share ownership
	// will share object - so, changing counter (refcount)
	// used only if function needs to increase the use counter

	// sharing the ownership - increments the use counter
	auto p1 = p;
	cout << "*p1=" << *p1 << endl;

}

//----------------------------------------------------------------------
// indicates that it CONSUMES THE OBJECT
// -takes ownership of the object
// -Because copy is disabled in unique_ptr 
//  the call below will only compile if the pointer is being moved
void take(std::unique_ptr<int> p)
{
	cout << __PRETTY_FUNCTION__ << endl;
	cout << "*p=" << *p << endl;
}


//----------------------------------------------------------------------
int main()
{
	cout << ">>>>>main() ..." << endl;

	auto ptConstObj = make_shared<int>(123);

	auto pt = make_shared<int>(1);
	std::cout << "pt.use_count() - main - before == " << pt.use_count() << '\n'; 
	mayShare(pt, ptConstObj);
	std::cout << "pt.use_count() - main - after == " << pt.use_count() << '\n'; 


	auto ptShare = make_shared<int>(888);
	share(ptShare);


	auto ptTake = make_unique<int>(666)	;
	take(std::move(ptTake));
	ptTake = nullptr;

	
	cout << ">>>>>main() - End !" << endl;

	return 0;

}

