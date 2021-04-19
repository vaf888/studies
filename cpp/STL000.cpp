//------------------------------------------------
// description..: stl - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <iterator>
#include <random>	//rnadom_device


using namespace std;

/*
	study sequence based on video:
	https://www.youtube.com/watch?v=2olsGf6JIkU&t=375s
	"105 STL Algorithms in Less Than an Hour”
*/

//----------------------------------------------------------------------
//Heaps - tree with parents also having big value
//        (contrary to heap of stones - smaller at the top!)

template <typename TIter>
void displayIt(TIter it, TIter end, std::string msg)
{
	cout << msg << endl;

/*
	for_each(begin, end, 
		[](TIter * item){cout << *item << "";});
*/
	for (; it != end; ++it) 
	{ 
		cout << *it << " ";
	}

	cout << endl;

}

//squash it down into a range
//serialize each level of the tree, one after the other one, horizontally
//e.g. tree= 9, children: (8,6) -> goes to: 9,8,6
//going from a node to its left child is essentially
//taking its index and make it X 2 (+1)

//VIP: heaps use - to get the max element of a collection (front)

void heap000()
{
	cout << endl;
	cout << "________________________________" << endl;
	cout << __PRETTY_FUNCTION__ << endl;

	cout << ">>>>>Heap" << endl;
	std::vector<int> v{100,200,300,400,500};
	displayIt(begin(v), end(v), ">>>>>before make_heap");
	std::make_heap(v.begin(), v.end());
	displayIt(v.begin(), v.end(), ">>>>>after make_heap");

	cout << endl;
	cout << ">>>>>" << endl;
	std::vector<int> v2{100,200,300,400,500};
	std::make_heap(v2.begin(), v2.end());
	v2.push_back(1000);
	displayIt(begin(v2), end(v2), ">>>>>before push_heap");
	std::push_heap(begin(v2), end(v2));
	displayIt(begin(v2), end(v2), ">>>>>after push_heap");

	std::cout << ">>>>>max heap after push_heap=" << v2.front() << '\n';
}

//----------------------------------------------------------------------
void sorting()
{
	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	cout << ">>>>>Sorting ASCENDING ..." << endl;
	std::vector<int> v{500,300,100,400,200};
	displayIt(begin(v), end(v), ">>>>>before sort");
	
	//default order = ascending
	//std::sort(begin(v), end(v), [](int a, int b){return a < b;});
	std::sort(begin(v), end(v));

	displayIt(begin(v), end(v), ">>>>>after sort");


	cout << endl;
	cout << "________________________________" << endl;
	cout << ">>>>>Sorting DESCENDING ..." << endl;
	std::vector<int> v2{500,300,100,400,200};
	displayIt(begin(v2), end(v2), ">>>>>before sort");
	std::sort(begin(v2), end(v2), [](int a, int b){return a > b;});
	displayIt(begin(v2), end(v2), ">>>>>after sort");

	//partial sort - sorts part of vector only - rest stays in unspecified order
	//sorts collection from beginning UNTIL A POINT IN THE MIDDLE
	cout << endl;
	cout << "________________________________" << endl;
	cout << ">>>>>Sorting DESCENDING ..." << endl;
	std::vector<int> v21{500,300,100,400,200};
	displayIt(begin(v21), end(v21), ">>>>>before sort");
	std::sort(begin(v21), end(v21), [](int a, int b){return a > b;});
	displayIt(begin(v21), end(v21), ">>>>>after sort");

	//partial_sort
	//-The generic algorithm partial_sort() sorts only a portion of a sequence.
    //-three iterators are used to describe the beginning, middle, and end of a sequence
    //-partial sort - sorts part of vector only - rest stays in unspecified order
	//-sorts collection from beginning UNTIL A POINT IN THE MIDDLE
	//-parameters:
	// [begin, middle), end), comparator

    cout << endl;
	cout << "________________________________" << endl;
	cout << ">>>>>partial sort ..." << endl;
	std::vector<int> v3{9,8,3,1,7,6,2,5,4};
	displayIt(begin(v3), end(v3), ">>>>>before sort");

	//sort the smallest 5 items int the sequence
	//std::partial_sort(begin(v3), begin(v3)+5, end(v3), [](int a, int b){return a < b;});
	std::partial_sort(begin(v3), begin(v3)+5, end(v3));
	displayIt(begin(v3), end(v3), ">>>>>after sort");

    cout << endl;
	cout << "________________________________" << endl;
	cout << ">>>>>partial sort - biggest ..." << endl;
	std::vector<int> v4{9,8,3,1,7,6,2,5,4};
	displayIt(begin(v4), end(v4), ">>>>>before sort");

	//sort the biggest 4 items int the sequence
	std::partial_sort(begin(v4), begin(v4)+4, end(v4), [](int a, int b){return a > b;});
	displayIt(begin(v4), end(v4), ">>>>>after sort");

    cout << endl;
	cout << "________________________________" << endl;
	cout << ">>>>>sort nth_element..." << endl;
	std::vector<int> v5{9,8,3,1,7,6,2,5,4};
	std::random_shuffle (begin(v5), end(v5));
	displayIt(begin(v5), end(v5), ">>>>>before sort");

	//sort result: 
	//all items < n_element, nth_element, items > nth_element
	//(*) before and after no order specified !
	// e.g.: 3rd element NOT INCLUDED (from 0) is the middle point
	// default = lessthan - smaller before
	std::partial_sort(begin(v5), begin(v5)+3, end(v5));
	//doing -> greater before
	//std::partial_sort(begin(v5), begin(v5)+3, end(v5), [](int a, int b){return a > b;});
	displayIt(begin(v5), end(v5), ">>>>>after sort");
}

//----------------------------------------------------------------------
void partitioning()
{
	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	cout << ">>>>>partitioning (even items first)..." << endl;
	std::vector<int> v{0,1,2,3,4,5,6,7,8,9};
	std::random_shuffle (begin(v), end(v));

	displayIt(begin(v), end(v), ">>>>>before partitioning");

	auto it = std::partition(v.begin(), v.end(), 
		[](int i){return i % 2 == 0;});

	std::cout << "\n>>>>>Partitioned vector -> first half:\n    ";
	std::copy(begin(v), it, std::ostream_iterator<int>(std::cout, " ") );
	std::cout << "\n>>>>>Partitioned vector -> second half:\n    ";
	std::copy(it+1, end(v), std::ostream_iterator<int>(std::cout," ") );
}	


//----------------------------------------------------------------------
void permutations(string input)
{
	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	std::cout << "\n>>>>>input before loop= " << input << '\n';
	do 
	{
	std::cout << "+++" << input << '\n';

	} 
	while ( std::next_permutation(begin(input),end(input)) );

	std::cout << ">>>>>input after loop= " << input << '\n';
}	

//----------------------------------------------------------------------
void reverseIt(string input)
{
	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;


	// we need to make result big enough to keep the results
	string result{};
	result.resize(input.size()); 

	std::cout << "\n>>>>>input before reverse_copy= " << input << '\n';
	//std::reverse_copy(begin(input), end(input), begin(result));
	// OR - using back inserter - result must be bidirectional
	std::reverse_copy(begin(input), end(input), back_inserter(result));

	std::cout << ">>>>>result= " << result << '\n';
	std::cout << ">>>>>input after reverse_copy= " << input << '\n';


	std::cout << "\n>>>>>input before reverse= " << input << '\n';
	std::reverse(begin(input), end(input));
	std::cout << ">>>>>input after reverse= " << input << '\n';
	
}	

//----------------------------------------------------------------------
void rotateIt()
{
	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	//rotate: block of items after middle is exchanged
	//with block before it - midle will be the first item
	// e.g.:  ABCDEFG
	// rotate it with middle = E will result
	// EFGABCD

	string input{"ABCDEGF"};
	string result{};

	std::cout << "\n>>>>>input before rotate_copy= " << input << '\n';
	std::rotate_copy(begin(input), begin(input) + 4, end(input), back_inserter(result));
	std::cout << ">>>>>result= " << result << '\n';
	std::cout << ">>>>>input after rotate_copy= " << input << '\n';

	std::cout << "\n>>>>>input before rotate= " << input << '\n';
	std::rotate(begin(input), begin(input) + 4, end(input));
	std::cout << ">>>>>input after rotate= " << input << '\n';
}

void ramdomIt()
{

	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector<int> v{1,2,3,4,5,6,7,8,9};

	cout << ">>>>>random_shuffle + def. func - BEFORE" << endl;
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout," "));

	std::random_shuffle(v.begin(), v.end());
	cout << "\n>>>>>random_shuffle + def. func - AFTER" << endl;
	std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout," "));
	cout << endl;

	//using random func. 
	std::random_device rd;
	std::mt19937 g(rd());

	std::vector<int> v2{1,2,3,4,5,6,7,8,9};

	cout << "\n>>>>>random_shuffle + rand. func - BEFORE" << endl;
	std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout," "));

	std::shuffle(v2.begin(), v2.end(), g);
	cout << "\n>>>>>random_shuffle + rand. func. - AFTER" << endl;
	std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout," "));
	cout << endl;

}

//TODOs:
// count
// accumulate transforme reduce
// etc ...23:24 min

//----------------------------------------------------------------------
int main()
{
	cout << __PRETTY_FUNCTION__ << endl;

	heap000();

	sorting();

	partitioning();

	permutations("ABCD");

	reverseIt("ABCD");

	rotateIt();

	ramdomIt();

	return 0;
}

