//------------------------------------------------
// description..: resource management - cont.
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <memory>

using namespace std;


class DataHolder
{

public:
	DataHolder(string t) : m_strPtr{make_unique<string>(std::move(t))}
	{
	}

	DataHolder(int t) : m_intPtr{make_unique<int>(std::move(t))}
	{
	}

	DataHolder() = default;
	
	DataHolder(const DataHolder & other) = delete;
	DataHolder& operator=(const DataHolder & other) = delete;

	DataHolder(DataHolder && other) = default;
	DataHolder& operator=(DataHolder && other) = default;

	~DataHolder() = default;

	void print()
	{
		if (m_strPtr)
			cout << *m_strPtr << endl;
		else if(m_intPtr)
			cout << *m_intPtr << endl;
		else
			cout << "Not defined !!!" << endl;
	}



private:
	std::unique_ptr<std::string> m_strPtr{nullptr};
	std::unique_ptr<int> m_intPtr{nullptr};

};


//----------------------------------------------------------------------
int main()
{
	cout << ">>>>>main() ..." << endl;

	DataHolder dh1(1);
	DataHolder dh2("string");
	DataHolder dh3; // calls the default constructor or WITHOUT {}
	//DataHolder dh3{}; idem
	//DataHolder dh3; // calls a constructor with NO PARMS - not necessarily the default !

	dh1.print();
	dh2.print();
	dh3.print();
	
	cout << ">>>>>main() - End !" << endl;

	return 0;

}

