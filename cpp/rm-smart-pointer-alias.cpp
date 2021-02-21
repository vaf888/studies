//------------------------------------------------
// description..: resource management - using smart pointer alias
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>

using namespace std;


//----------------------------------------------------------------------
class Object
{
public:
	// public !!!
	std::shared_ptr<int> i = std::make_shared<int>(1);

	int getI()
	{
		return *i;
	}

	void updateValue()
	{
		if (*i < 2)
		{
			i = std::make_shared<int>(99);
		}
	}

};


//---global var ---
Object o;


//----------------------------------------------------------------------
static void print(const int t_i)
{
	cout << "t_i=" << t_i << endl;
}


//----------------------------------------------------------------------
void useValueError()
{
	const int& local_i = o.getI();

	o.updateValue();

	print(local_i);
}


//----------------------------------------------------------------------
int main()
{

	//Object o;

	cout << ">>>>>main() ..." << endl;
	useValueError();
	cout << ">>>>>main() - End !" << endl;

	return 0;

}

