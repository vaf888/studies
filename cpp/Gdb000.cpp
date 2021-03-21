//------------------------------------------------
// description..: handling dates + using boost library
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <vector>

using namespace std;

/*
//----------------------------------------------------------------------
int fatorial(int n)
{

	if(n==0)
		return 1;

	return n * fatorial(n-1);
}


//----------------------------------------------------------------------
#define NUM_THREADS 5
 
#define BLACK   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"


std::mutex colour_mutex;
 
void PrintAsciiText(int id)
{
    string colour;
 
    colour_mutex.lock();

    switch((long)id)
    {
	    case 0:
	        colour = RED;
	        break;
	    case 1:
	        colour = GREEN;
	        break;
	    case 2:
	        colour = YELLOW;
	        break;
	    case 3:
	        colour = BLUE;
	        break;
	    case 4:
	        colour = CYAN;
	        break;
	    default:
	        colour = BLACK;
	        break;
    }
 
    sleep(1);

    cout << colour 
    	<< "I'm a new thread, I'm number " 
    	<< (long)id 
    	<< BLACK << endl;
    
    colour_mutex.unlock();

}

*/

//----------------------------------------------------------------------
struct TimeStuff
{
	int8_t m_hours;
	uint32_t m_micros;
	uint16_t m_seconds;

	TimeStuff() = default;	

	TimeStuff(int8_t hours, uint32_t micro, uint16_t seconds):
		m_hours(hours), m_micros(micro), m_seconds(seconds)
	{
	}

	~TimeStuff() = default;	

};

//----------------------------------------------------------------------
void valgrind000()
{
	// TEST CODE for valgrind
	constexpr int MAXSIZE = 10;
	std::array<int, MAXSIZE> a;

	// generates an error - array out of bound !
	for(auto i=0; i<= MAXSIZE+2; i++)
	{
		a[i]=0;
	}

	a[MAXSIZE+5] = 10;

	int * b  = new int{};
	*b = 1;

}

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	cout << "__________________________________________________" << endl;

	/*
	int n = 4;
	assert(24 == fatorial(n));

	// threads
    std::vector<std::thread> threads{};
 
    for(int i = 0; i < NUM_THREADS; ++i)
    {
       threads.push_back(std::thread(PrintAsciiText, i));
    }

    for(auto t = threads.begin(); t != threads.end(); ++t)
    {
    	t->join();
    }

	TimeStuff timeStuff{6, 0x12345678, 0XDEAD};
 	cout << "sizeof(timeStuff)=" << sizeof(timeStuff) << endl;

 	*/

 	//valgrind test
	valgrind000();
	
	return 0;	
}

