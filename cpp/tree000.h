//------------------------------------------------
// file.........: tree000.h
// description..: tree - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <iostream>  	// std::cout, std::endl

#ifndef _tre000_h_
#define _tre000_h_

// Assumption: ItemType is a type for 
// which the operators "<" and "==" are 
// defined 
// --either an appropriate built-in type or
// a class that overloads these operators.
typedef int ItemType;

enum class OrderType 
{ PreOrder, InOrder, PostOrder };

//forward declaration
struct TreeNode;

struct TreeNode
{
  ItemType  info;
  TreeNode* left;
  TreeNode* right;

  explicit TreeNode() : info(), left(nullptr), right(nullptr)
  {
  }

  explicit TreeNode(ItemType item): info(item), left(nullptr), right(nullptr)
  {
  }

  ~TreeNode()
  {

  }
};

class TreeType
{
public:
  TreeType();
  ~TreeType();
  TreeType(const TreeType & original);
  void operator=(TreeType & original);

  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const;

  ItemType GetItem(ItemType item, bool & found) const;
  void PutItem(ItemType item);
  void PutItemPtoP(ItemType item); //using pointer to pointer
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order);
  ItemType GetNextItem(OrderType order, bool &finished);

  void Print(std::ostream& out) const;
  void Print() const;
  void Print(const OrderType& orderType) const;

private:
  TreeNode * root;

  int CountNodes(TreeNode * root) const;
  bool RetrieveItem(TreeNode * root, ItemType item) const;
  void Insert(TreeNode*& tree, ItemType item);
  void InsertPtoP(TreeNode** tree, ItemType item); // insert using pointer to pointer
  void PrintTree(const TreeNode* tree, std::ostream& out) const;
  void PrintTree(const TreeNode* tree) const;

  void PrintInOrder(const TreeNode* tree) const;
  void PrintPreOrder(const TreeNode* tree) const;
  void PrintPostOrder(const TreeNode* tree) const;

  void Destroy(TreeNode* & root);

};

#endif
