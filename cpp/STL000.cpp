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
#include <numeric>	//std::reduce
#include <chrono>   //time
#include <iomanip>  // set precision

//VIP: to use exec. policies (uses TBB parallel lib)
//include execution
//install TBB lib
//link with lib -> -ltbb
#include <execution> // exec. policies

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

//----------------------------------------------------------------------
void countIt()
{

	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	constexpr std::array v={ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

	cout << "\n>>>>>array=";
	std::copy(v.begin(), v.end(), ostream_iterator<int>(std::cout," "));

	
	int numItems = std::count(v.begin(), v.end(), 4);
	cout << "\n>>>>>num items 4=" << numItems << endl;
	assert(2 == numItems);


	numItems = std::count_if(v.begin(), v.end(), 
		[](int x){ return x%2==0;});

	cout << "\n>>>>>num items divisible by 2=" << numItems << endl;

	assert(5 == numItems);	


	//distance
	int dist = std::distance(v.begin(), v.end());
	cout << ">>>>>distance from 1 to 10=" << dist << endl;
	assert(10 == dist);

	dist = std::distance(v.begin()+6, v.end());
	cout << ">>>>>distance from 7 to 10=" << dist << endl;
	assert(4 == dist);

}

//----------------------------------------------------------------------
// reduce (c++17) - similar to accumulate but allows parallel polices

auto eval = [](auto fun) 
	{
        const auto t1 = std::chrono::high_resolution_clock::now();
        const auto [name, result] = fun();
        const auto t2 = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> ms = t2 - t1;
        std::cout << std::fixed << std::setprecision(1) << name << " result "
                  << result << " took " << ms.count() << " ms\n";
    };

void reduceIt()
{
	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	constexpr std::array v={ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

	auto res = std::reduce(v.begin(), v.end());
	cout << "\n>>>>>reduce res=" << res << endl;
	assert(51 == res);

	res = std::reduce(v.begin(), v.end(), 10);
	cout << "\n>>>>>reduce + inti val 10 - res=" << res << endl;
	assert(61 == res);

	res = std::reduce(v.begin(), v.end(), 10);
	cout << "\n>>>>>reduce + inti val 10 - res=" << res << endl;
	assert(61 == res);

	cout << endl;
	eval([&v] { return std::pair
				{
					"std::reduce(v.begin(), v.end(), 10)",
					std::reduce(v.begin(), v.end(), 10)
			    };
			   }
		);

		cout << endl;
		res = std::reduce( std::execution::par, v.begin(), v.end());
		cout << "\n>>>>>reduce res + parallel=" << res << endl;
		assert(51 == res);
}


//----------------------------------------------------------------------
void transformIt()
{
	/*
		std::transform applies the given function to a range and 
		stores the result in another range, keeping the original 
		elements order and beginning at d_first.
	*/

	cout << endl;
	cout << "________________________________" << endl;	
	cout << __PRETTY_FUNCTION__ << endl;

	std::vector v={ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };
	std::vector<int> res{};
	cout << "before transform v=";
	std::copy(v.begin(),v.end(),ostream_iterator<int>(std::cout, " "));
	std::transform(v.begin(),v.end(),std::back_inserter(res),[](int a){return a *=5;});
	cout << "\nafter transform X 5 -> v=";
	std::copy(res.begin(),res.end(),ostream_iterator<int>(std::cout, " "));

}


void testFor()
{
	cout << __PRETTY_FUNCTION__ << endl;

	//size_t sz = buf->size();
	size_t sz = 5;	

	while ( --sz >= 0 )
	{
		cout << "size=" << sz << endl;
	}
}
//>>>>>>>>>>>>>next 26:22 any_of

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

	countIt();

	reduceIt();

	transformIt();

	testFor();

	return 0;
}

