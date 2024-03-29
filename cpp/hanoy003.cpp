//------------------------------------------------
// file.........: hanoy003.cpp
// description..: hanoy tower (using stack) - recursion
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <utility>
#include <iostream>  	// std::cout, std::endl
#include <cassert>
#include <cstring>
#include <stack>
#include <vector>
#include <sstream>      // std::istringstream
//#include <typeinfo>
 
using namespace std;

stack<string> source;
stack<string> target;
stack<string> temp;

void message(const string & s)
{
	cout << endl;
    cout << "__________________________________" << endl;
    cout << s << endl;
}

void message()
{
	cout << endl;
    cout << "__________________________________" << endl;
}

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

void displayOneDisk(string && diskName)
{
	auto res = split(diskName,'-');
	auto n = res[1];
	int number = std::stoi(n);
	for (int i=0; i < number; ++i)
	{
		cout << n;
	}
	cout << endl;
}

void displayTower(stack<string> & tower, string && label)
{
	std::stack<string> tmpTower = tower;

	cout << endl;
	cout << label << endl;
	while(!tmpTower.empty())
	{
	    string w = tmpTower.top();
	    displayOneDisk(std::move(w));
	    tmpTower.pop();
	}
}

void displayMove(string && disk)
{
	cout << endl << ">>>>>>>>>>>>>>" << endl;
	cout << "moving disk=" << disk << "..." << endl;

	// display the 3 towers/stacks content:
	displayTower(source, "source:");
	displayTower(target, "target:");
	displayTower(temp, "temp:");
}

void initTowers(int n)
{
	const string s = "disk-";

	string diskName = "";
	for(int i=n; i >=1; --i)
	{
		diskName = s + std::to_string(i);

		source.push(diskName);
	}
}

void towers(int n, stack<string> & source, stack<string> & target, stack<string> & temp)
{
	string disk = "";

	// if this is a stack of size one, just move it: source -> target
	if(n == 1)
	{
		disk = source.top();
		source.pop();
		target.push(disk);
		displayMove(std::move(disk));
	}
	else
	{
		// move top n-1 items from source to temp, using target as temporary/spare
		towers(n-1, source, temp, target);

		// move top (left item = bigest one) - from source to target
		towers(1,source, target, temp);

		// move all the items in the temp to the target (using source as temporary/spare)
		towers(n-1, temp, target, source);
	}
}

void towersWrapper(int n)
{
	message();
	cout << "towers layout: Source - Target - Temp" << endl;

	initTowers(n);

	//discNumber=n; // first/biggest disk to be moved
	//totalDiscsInTarget=0;

	towers(n, source, target, temp);
}

int main (int argc, char *argv[])
{
	string line="";
	cout << "number of disks:";
	std::getline(cin, line);
	int n = stoi(line);

	towersWrapper(n);

	message(">>>>> End of Calls !!!");
}

