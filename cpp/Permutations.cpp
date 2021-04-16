//------------------------------------------------
// description..: permutation - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iterator>


using namespace std;

static int numPermutations=0;
void permutations(string input, int pos, int n)
{
	if(pos == n-1)
	{
		cout << input << endl;
		numPermutations++;
		return;
	}

	for(int j=pos; j < n; ++j)
	{
		swap(input[pos], input[j]);

		permutations(input, pos+1, n);

		swap(input[pos], input[j]);
	}

}


void permutationHelper(std::string s)
{
	cout << __PRETTY_FUNCTION__ << endl;
	numPermutations=0;
	permutations(s, 0, s.length());
	cout <<">>>>>number of permutations=" << numPermutations << endl;
}

//----------------------------------------------------------------------
void getPermutations(std::string input, std::string output, int * numPermutations) 
{
  cout << "\n+++TESTS ONLY: input=" << input << "; output=" << output << endl;
  if (input.length() == 0)
  {
  	cout << ">>>>>" << output << endl;
  	(*numPermutations)++;
  	output="";
  	return;
  } 
  else
  {

  	for(int i=0; i < (int)input.length(); ++i)
  	{
  		cout << "---TESTS ONLY: i=" << i << endl;

  		auto leftChoices = input.substr(0,i) + input.substr(i+1);

  		//output += input[i]; ????? why not ????

  		getPermutations(leftChoices, output + input[i], numPermutations);
  	}

  }
}

int  getPermutationsHelper(std::string s)
{
	cout << __PRETTY_FUNCTION__ << endl;
	std::string result{};
	int numPermutations=0;
	getPermutations(s, result, &numPermutations);
	return numPermutations;
}


//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;


	cout <<"__________________________________" << endl;
	permutationHelper(std::string{"ABC"});

	cout <<"__________________________________" << endl;
	permutationHelper(std::string{"ABCD"});


/*
	cout <<"__________________________________" << endl;
	cout <<">>>>>permutations for 'ABC'" << endl;
	auto numPermutations = getPermutationHelper(std::string{"ABC"});
	cout <<">>>>>number of permutations=" << numPermutations << endl;
	assert(6 == numPermutations);


	cout <<"__________________________________" << endl;
	cout <<">>>>>permutations for 'ABCD'" << endl;
	numPermutations = getPermutationsHelper(std::string{"ABCD"});
	cout <<">>>>>number of permutations=" << numPermutations << endl;
	assert(24 == numPermutations);
*/

	return 0;

}

