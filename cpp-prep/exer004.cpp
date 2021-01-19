#include <iostream>
#include <cassert>

using namespace std;


//What is the output of the program below?


int main()
{
	enum color_type {red, orange, yellow, green, blue, violet};

	color_type shirt, pants;

	shirt = red;
	pants = blue;
	cout << shirt << " " << pants << endl;  // 0<SP>4

	return 0;
}