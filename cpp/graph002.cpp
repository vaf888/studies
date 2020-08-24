//------------------------------------------------
// file.........: graph002.cpp
// description..: graphs using adjacent list - studies
//                using DepthFirstSeard & BreadthFirstSearch
// version......: v1
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cassert>

#include "graph002.h"
#include <iterator>

using namespace std;

/*
------------------------------------------
*/
std::ostream & operator<<(std::ostream & out, const EdgeNode & edge )
{
  out << "fromNode=" << edge.mFromNode << " -> mToNode=" 
      << edge.mToNode << " - mWeight=" << edge.mWeight << endl;
  return out;
}

/*
------------------------------------------
*/
std::ostream & operator<<(std::ostream & out, const Graph & graph )
{
  out << endl;
  out << ">>>>>Graph content:" << endl;

  for(auto it=graph.mNodes.begin(); it!=graph.mNodes.end(); ++it)
  {
    //out << "graph[" << it->first << "] = " << &(it->second) << '\n';
    out << endl;
    out << "graph[" << it->first << "]:" << endl;

    // list all edges linked to this edge
    std::list<EdgeNode *> * edgeList = it->second;

    for(const auto &edge : *edgeList)
    {
      out << *edge;
    }
  }

  out << endl;

  return out;
}

/*
------------------------------------------
*/
bool Graph::HasAdjacentNodes(
  const NodeItemType & node) const
{
  return (mNodes.count(node) != 0);
}

/*
------------------------------------------
*/
void Graph::AppendAdjacentNodes(
  const NodeItemType & node, 
  std::stack<NodeItemType> & stack)
{
    if (mNodes.count(node) != 0)
    {
      auto edgeList = mNodes[node];
      
      for(auto edge : *edgeList)
      {
        stack.push(edge->GetToNode());
      }
    }
}

/*
------------------------------------------
*/
void Graph::AppendAdjacentNodes(
    const NodeItemType & node, 
    std::list<NodeItemType> & list)
{
    if (mNodes.count(node) != 0)
    {
      auto edgeList = mNodes[node];
      
      for(auto edge : *edgeList)
      {
        // only those not in the list yet !
        if (std::find(list.begin(), list.end(), edge->GetToNode()) == list.end())
        {
          list.push_back(edge->GetToNode());
        }
      }
    }
}

//////////////// the code below should be in another .cpp/.h

/*
------------------------------------------
*/
void GraphAlgorithm::DepthFirstSearch(
  NodeItemType curNode, 
  std::set<NodeItemType> * visited)
{
  // if already visited - base case
  if (visited->count(curNode) > 0)
  {
    return;
  }
  else // node not visited yet
  {
    // do sth with curNode
    cout << curNode << " ";

    visited->insert(curNode);

    auto nodesList = mGraph.GetEdgeList(curNode);

    for(auto edgeNode:(*nodesList))
    {
      auto nodeTmp = edgeNode->GetToNode();
      DepthFirstSearch(nodeTmp, visited);
    }
  }
}

/*
------------------------------------------
*/
void GraphAlgorithm::DepthFirstSearch(NodeItemType & startNode)
{
  std::set<NodeItemType> visited;
  DepthFirstSearch(startNode, &visited);
}

/*
------------------------------------------
*/
void GraphAlgorithm::BreadthFirstSearch(
  NodeItemType curNode, 
  std::list<NodeItemType> & q)
{
  if (curNode == "")
  {
    return;
  }
  else
  {
    cout << curNode << " ";

    mGraph.AppendAdjacentNodes(curNode, q);

    while(!q.empty())
    {
      curNode = q.front();
      q.pop_front();

      BreadthFirstSearch(curNode, q);     
    }
  }
}


/*
------------------------------------------
*/
void GraphAlgorithm::BreadthFirstSearch(NodeItemType & startNode)
{
  std::list<NodeItemType> q;
  BreadthFirstSearch(startNode, q);
}

/*
------------------------------------------
*/
void GraphAlgorithm::BreadthFirstSearchIterative(NodeItemType & startNode)
{
  std::list<NodeItemType> q;
  std::set<NodeItemType> visited;

  q.push_back(startNode);

  NodeItemType node=""; 
  while(!q.empty())
  {
    node = q.front();
    q.pop_front();

    //process only not visited yet nodes
    if(visited.count(node) == 0)
    {
      cout << node << " ";

      visited.insert(node);

      // add all adjacents nodes to this node (to be visited)
      //cout << endl << "DEBUG:" << "node=" << node <<endl;
      auto nodesList = mGraph.GetEdgeList(node);
      for(auto edgeNode:(*nodesList))
      {
          // add node as a candidate to be visited
          q.push_back(edgeNode->GetToNode());
      }
    }
  }
}
