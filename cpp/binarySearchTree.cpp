//------------------------------------------------
// file.........: binarySearchTree.cpp
// description..: binary search (precondition: input 
//                is a binary tree) (recursion)
//                return: the index of found item, or -1
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
//#include <typeinfo>
 
using namespace std;

void message(const string & s)
{
    cout << "__________________________________" << endl;
    cout << s << endl;
}

struct treeNode
{
	string data,
	struct treeNode * left;
	struct treeNode * right;

	treeNode(int value):data(value), left(nullptr), right(nullprt)
	{}
};

node * buidTree(node * root)
{

	root == nullptr;

	node * nodeTmp = new treeNode(50);
	root = nodeTmp;

	nodeTmp->left = new treeNode(49);
	nodeTmp = nodeTmp->left;
	
	root->left = nodeTmp;

	nodeTmp->data = 50;
	nodeTmp->left = nullptr;
	nodeTmp->right = nullptr;

	nodeTmp = new (struct node);
	root = nodeTmp;
	nodeTmp->data = 50;




}

void message(const int v[], int n)
{
    cout << "__________________________________" << endl;
    cout << "content=";

    for(auto i=0; i < n; ++i)
    	cout << v[i] << " ";
    cout << endl;
}


int binarySearchTree(int v[], int begin, int end, int searchFor)
{
	cout << "DEBUG: begin=" << begin << "; end=" << end << endl;

	if(begin > end)
		return -1;

	int middle = (begin + end)/2;

	if (v[middle] == searchFor)
		return middle;

	if(searchFor < v[middle])
		return binarySearchTree(v, begin, middle-1, searchFor);
	else
		return binarySearchTree(v, middle+1, end, searchFor);
}

int binarySearchTreeWrapper(int v1[], int v1Size, int searchFor)
{ 
	cout << endl;
	cout << "DEBUG: in binarySearchTreeWrapper - searchFor = " << searchFor << endl;

	int res = -1;
	res = binarySearchTree(v1, 0, v1Size-1, searchFor);	
	cout << "DEBUG: in binarySearchTreeWrapper - res = " << res << endl;
	return res;
}

int main (int argc, char *argv[])
{
	int a[] = {3,4,5,7,8};
	int sizeofA = sizeof(a)/sizeof(a[0]);
	message(a, sizeofA);

	int res = binarySearchTreeWrapper(a, sizeofA, 3);
	assert(-1 != res);

	res = binarySearchTreeWrapper(a, sizeofA, 4);
	assert(-1 != res);

	res = binarySearchTreeWrapper(a, sizeofA, 5);
	assert(-1 != res);

	res = binarySearchTreeWrapper(a, sizeofA, 7);
	assert(-1 != res);

	res = binarySearchTreeWrapper(a, sizeofA, 8);
	assert(-1 != res);

	res = binarySearchTreeWrapper(a, sizeofA, 9);
	assert(-1 == res);


	//message(">>>>> End of Calls !!!");
}

