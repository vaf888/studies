//------------------------------------------------
// file.........: graph002.h
// description..: graph using adjacent list - studies
//                using DepthFirstSeard & BreadthFirstSearch
// version......: v1
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl

#ifndef _graph002_h_
#define _graph002_h_

#include <list>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
#include <iostream>
#include <string>

// Assumption: ItemType is a type for 
// which the operators "<" and "==" are 
// defined 
// --either an appropriate built-in type or
// a class that overloads these operators.
typedef std::string NodeItemType;
typedef int WeightType;

class EdgeNode
{

  NodeItemType mFromNode;
  NodeItemType mToNode;
  WeightType mWeight;    

public:

  EdgeNode()
  {
    mFromNode="";
    mToNode="";
    mWeight=-1;
  }

  EdgeNode(NodeItemType fromNode, NodeItemType toNode, WeightType weight)
  {
    mFromNode=fromNode;
    mToNode=toNode;
    mWeight=weight;
  }

  ~EdgeNode()
  {
    //std::cout <<" [in ~EdgeNode()]";
  }

  EdgeNode(const EdgeNode & other)
  {
    mFromNode=other.mFromNode;
    mToNode=other.mToNode;
    mWeight=other.mWeight;
  }

  EdgeNode & operator=(const EdgeNode & other)
  {
    if(this != &other)
    {

      // TODO: check this
      mFromNode=other.mFromNode;
      mToNode=other.mToNode;
      mWeight=other.mWeight;
    }
    return *this;
  }

  NodeItemType GetFromNode()
  {
    return mFromNode;
  }

  NodeItemType GetToNode()
  {
    return mToNode;
  }

  WeightType GetWeight()
  {
    return mWeight;
  }

  friend std::ostream & operator<<(std::ostream & out, const EdgeNode & edge );
};

class Graph
{
public:
  Graph()
  {
  }
  
  ~Graph()
  {
    //std::cout <<"in ~Graph()" <<std::endl;

    for(auto it=mNodes.begin(); it!=mNodes.end(); ++it)
    {
      //std::cout << "destructing - graph[" << it->first << "]:" << std::endl;

      auto edgeList = it->second;
      for(const auto &edge : *edgeList)
      {
        //std::cout << "..deleting edge -> ";
        //std::cout << *edge;
        delete edge;
        //std::cout << std::endl;
      }
      //std::cout << std::endl;
    }
  }
  
  void AddNode(NodeItemType node)
  {
    std::list<EdgeNode *> * l = new std::list<EdgeNode *>{};
    mNodes[node] = l;
  }

  void AddEdge(NodeItemType fromNode, NodeItemType toNode, WeightType weight)  
  {
    if (mNodes.count(fromNode) != 0)
    {
      auto actualList = mNodes[fromNode];
      actualList->push_back((new EdgeNode{fromNode, toNode, weight}));
    }
  }

  Graph(const Graph & other)
  {
      // TODO: check this
      mNodes = other.mNodes;
  }

  Graph & operator=(const Graph & other)
  {
    if(this != &other)
    {

      // TODO: check this
      mNodes = other.mNodes;
    }
    return *this;
  }

  auto GetEdgeList(const NodeItemType & node)  
  {
    return mNodes[node];
  }

  void AppendAdjacentNodes(
    const NodeItemType & node, 
    std::list<NodeItemType> & list);

  friend std::ostream & operator<<(std::ostream & out, const Graph & graph );

private:

  void AppendAdjacentNodes(
    const NodeItemType & node, 
    std::stack<NodeItemType> & stack);

  bool HasAdjacentNodes(
  const NodeItemType & node) const;

  std::map<std::string, std::list<EdgeNode *>*> mNodes;
};

//this should be in another cpp + .h file
class GraphAlgorithm
{
public:
  GraphAlgorithm(Graph & graph) : mGraph(graph)
  {}

  void DepthFirstSearch(NodeItemType & startNode);
  void BreadthFirstSearch(NodeItemType & startNode);
  void BreadthFirstSearchIterative(NodeItemType & startNode);

private:
  void DepthFirstSearch( NodeItemType node, std::set<NodeItemType> * visited);
  void BreadthFirstSearch(NodeItemType curNode, std::list<NodeItemType> & nodesToBeVisited);

  Graph & mGraph;
};

#endif
