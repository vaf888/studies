//------------------------------------------------
// file.........: graphRunner002.cpp
// description..: run graph related functionalities
// version......: v1
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

#include "graph002.h"

using namespace std;

/*
------------------------------------------
*/
int main() 
{
  {
    Graph g{};
    NodeItemType va{"AA"};
    NodeItemType vb{"BB"};
    NodeItemType vc{"CC"};
    NodeItemType vd{"DD"};
    NodeItemType ve{"EE"};
    NodeItemType vf{"FF"};
    NodeItemType vg{"GG"};
    NodeItemType vh{"HH"};

    g.AddNode(va);
    g.AddNode(vb);
    g.AddNode(vc);
    g.AddNode(vd);
    g.AddNode(ve);
    g.AddNode(vf);
    g.AddNode(vg);
    g.AddNode(vh);

    g.AddEdge(va, vb, 100);
    g.AddEdge(va, vc, 101);
    g.AddEdge(va, vd, 102);
    g.AddEdge(va, vh, 103);

    g.AddEdge(vb, vc, 200);

    g.AddEdge(vd, ve, 201);

    g.AddEdge(ve, vf, 300);
    g.AddEdge(ve, vg, 301);

    g.AddEdge(vh, vg, 400);
    cout << g;

    GraphAlgorithm algo{g};
    NodeItemType startingAt{"AA"};
    //NodeItemType startingAt{"DD"};
    //NodeItemType startingAt{"HH"};

    cout << endl;
    cout << "___________________________" << endl;
    cout << ">>>>> DepthFirstSearch" << endl;
    cout << "..startingAt=" << startingAt << endl;
    cout << "..result -> ";
    algo.DepthFirstSearch(startingAt);
    cout << endl;

    cout << endl;
    cout << g;
    cout << endl;

    cout << endl;
    cout << "___________________________" << endl;
    cout << ">>>>> BreadthFirstSearch" << endl;
    cout << "..startingAt=" << startingAt << endl;
    cout << "..result -> ";
    algo.BreadthFirstSearch(startingAt);
    cout << endl;

    cout << endl;
    cout << "___________________________" << endl;
    cout << ">>>>> BreadthFirstSearchIterative" << endl;
    cout << "..startingAt=" << startingAt << endl;
    cout << "..result -> ";
    algo.BreadthFirstSearchIterative(startingAt);
    cout << endl;

  }


  return 0;
} 
