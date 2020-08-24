//------------------------------------------------
// file.........: tre000.cpp
// description..: tree - studies
// version......: v0
// author.......: Antonio Fernandes
//------------------------------------------------

#include <string>
#include <stdexcept>
#include <cassert>

#include "tree000.h"

using namespace std;

/*
------------------------------------------------
*/
TreeType::TreeType()
{
  root = nullptr;
}

/*
------------------------------------------------
*/
TreeType::~TreeType()
{
  cout << endl << "destructing tree..." << endl;
  Destroy(root);
}

/*
------------------------------------------------
*/
bool TreeType::IsEmpty() const
{
  return (root == nullptr);
}

/*
------------------------------------------------
*/
bool TreeType::IsFull() const
{
  TreeNode* treeNode = nullptr;

  try
  {
    treeNode = new TreeNode();
    delete treeNode;
    return false;
  }
  catch (std::bad_alloc& e)
  {
    return true;
  }
}

/*
------------------------------------------------
*/
int TreeType::GetLength() const
{
  return CountNodes(root);
}

/*
------------------------------------------------
*/
ItemType TreeType::GetItem(ItemType item, bool & found) const
{
  if (RetrieveItem(root, item))
  {
    found = true;
  }
  else
  { 
    found = false;
  }

  return item;
}

/*
------------------------------------------------
*/
void TreeType::PutItem(ItemType item)
{
  cout << endl;
  cout << "DEBUG: root BEFORE insert=" << root << " - item=" << item << endl;
  Insert(root, item);
  cout << "DEBUG: root AFTER insert=" << root << " - item=" << item << endl;
}

/*
------------------------------------------------
*/
//using pointer to pointer
void TreeType::PutItemPtoP(ItemType item)
{
  cout << endl;
  cout << "DEBUG: root BEFORE insert=" << root << " - item=" << item << endl;
  InsertPtoP(&root, item);
  cout << "DEBUG: root AFTER insert=" << root << " - item=" << item << endl;
}

/*
------------------------------------------------
*/
//void Print(std::& outFile) const
void TreeType::Print() const
{
  PrintTree(root);
}

/*
------------------------------------------------
*/
void TreeType::Print(std::ostream& out) const
{
  PrintTree(root, out); 
}

/*
using namespace std;

class TreeType
{
public:
  TreeType();
  ~TreeType();
  TreeType(const TreeType & original);
  void operator=(TreeType & original);

  void MakeEmpty();
  void IsEmpty() const;
  void IsFull() const;
  int GetLength() const;

  ItemType GetItem(ItemType item, bool & found);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order);
  ItemType GetNextItem(OrderType order, bool &finished);

  void Print(std::ofstream& outFile);
  
private:
  TreeNode * root;
};
*/

//---private members ---

/*
------------------------------------------------
*/
void TreeType::Destroy(TreeNode* & root)
{
  if (root != nullptr)
  {
    Destroy(root->left);
    Destroy(root->right);
    delete root;
  }
}


/*
------------------------------------------------
*/
int TreeType::CountNodes(TreeNode * root) const
{
  if (root == nullptr)
    return 0;

  return 1 + CountNodes(root->left) + CountNodes(root->right);
}

/*
------------------------------------------------
*/
bool TreeType::RetrieveItem(TreeNode * root, ItemType item) const
{
  if (root == nullptr)
    return false;

  if (item == root->info)
    return true;

  if (item < root->info )
    return RetrieveItem(root->left, item);
  else
    return RetrieveItem(root->right, item);
}

/*
------------------------------------------------
*/
void TreeType::Insert(TreeNode* & tree, ItemType item)
{
  cout << "DEBUG: tree=" << tree << " - item=" << item << endl;
  if (tree == nullptr)
  {
    tree = new TreeNode{item};
    cout << "DEBUG: found a null tree -> new tree=" << tree << " - item=" << item << endl;
  }
  else if (item == tree->info)
  {
    tree->info = item; //replace
  }
  else if (item < tree->info)
  {
    Insert(tree->left, item);
  }
  else
  {
    Insert(tree->right, item);
  }
}

/*
------------------------------------------------
*/
// INSERT - using pointer to pointer
void TreeType::InsertPtoP(TreeNode** tree, ItemType item)
{
  cout << "DEBUG: tree=" << tree << " - item=" << item << endl;
  if (*tree == nullptr)
  {
    *tree = new TreeNode{item};
    cout << "DEBUG: found a null tree -> new tree=" << tree << " - item=" << item << endl;
  }
  else if (item == (*tree)->info)
  {
    (*tree)->info = item; //replace
  }
  else if (item < (*tree)->info)
  {
    InsertPtoP(&((*tree)->left), item);
  }
  else
  {
    InsertPtoP(&((*tree)->right), item);
  }
}

/*
------------------------------------------------
*/
void TreeType::PrintInOrder(const TreeNode* tree) const
{
  if (tree == nullptr)
    return;

  PrintInOrder(tree->left);
  cout << tree->info << endl;
  PrintInOrder(tree->right);
}

/*
------------------------------------------------
*/
void TreeType::PrintPreOrder(const TreeNode* tree) const
{
  if (tree == nullptr)
    return;

  cout << tree->info << endl;
  PrintPreOrder(tree->left);
  PrintPreOrder(tree->right);
}

/*
------------------------------------------------
*/
void TreeType::PrintPostOrder(const TreeNode* tree) const
{
  if (tree == nullptr)
    return;

  PrintPostOrder(tree->left);
  PrintPostOrder(tree->right);
  cout << tree->info << endl;
}

/*
------------------------------------------------
*/
//void TreeType::PrintTree(const TreeNode* tree, std::ofstream& outFile) const
void TreeType::PrintTree(const TreeNode* tree) const
{
  // print all the nodes in order (left, parent, right)
  // Definition:   Prints the items in the binary search tree in order, 
  //               from smallest to largest.
  // Base Case:  If tree = NULL, do nothing.
  // General Case:  ..Traverse the left subtree in order.
  //                ..Then print Info(tree).
  //                ..Then traverse the right subtree in order.  

/*
  if (tree == nullptr)
    return;

  PrintTree(tree->left);
  cout << tree->info << endl;
  PrintTree(tree->right);
*/

  PrintInOrder(tree);
}

/*
------------------------------------------------
*/
void TreeType::PrintTree(const TreeNode* tree, std::ostream& out) const
{
  // print all the nodes in order (left, parent, right)
  // Definition:   Prints the items in the binary search tree in order, 
  //               from smallest to largest.
  // Base Case:  If tree = NULL, do nothing.
  // General Case:  ..Traverse the left subtree in order.
  //                ..Then print Info(tree).
  //                ..Then traverse the right subtree in order.  

  if (tree == nullptr)
    return;

  PrintTree(tree->left);
  out << tree->info << endl;
  PrintTree(tree->right);
}

/*
------------------------------------------------
*/
void TreeType::Print(const OrderType& orderType) const
{
  switch(orderType)
  {
    case OrderType::InOrder:
      PrintInOrder(root);
    break;
    case OrderType::PreOrder:
      PrintPreOrder(root);
    break;
    case OrderType::PostOrder:
      PrintPostOrder(root);
    break;
    default:
      cout << "ERROR -> invalid order type !" << endl;
    break;
  }
}

/*
------------------------------------------------
*/
int main()
{
  TreeType * tree = new TreeType{};

  assert(true == tree->IsEmpty());
  assert(false == tree->IsFull());
  assert(0 == tree->GetLength());

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>insert using reference to pointer" << endl;
  ItemType item {7};
  tree->PutItem(item);
  tree->PutItem(3);
  tree->PutItem(4);
  tree->PutItem(2);
  tree->PutItem(1);
  tree->PutItem(9);

  ItemType searchForItem=1;
  bool expectedFound = false;
  ItemType resItem = tree->GetItem(searchForItem, expectedFound);
  assert((expectedFound==true) && (searchForItem==resItem));

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree content..." << endl;
  tree->Print();

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree InOrder..." << endl;
  tree->Print(OrderType::InOrder);

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree PreOrder..." << endl;
  tree->Print(OrderType::PreOrder);

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree PostOrder..." << endl;
  tree->Print(OrderType::PostOrder);

  // insert using pointer to pointer
  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>insert using pointer to pointer" << endl;
  tree->PutItemPtoP(0);
  searchForItem=0;
  expectedFound = false;
  resItem = tree->GetItem(searchForItem, expectedFound);
  assert((expectedFound==true) && (searchForItem==resItem));

  // not found
  searchForItem=5;
  expectedFound = false;
  resItem = tree->GetItem(searchForItem, expectedFound);
  assert((expectedFound==false) && (searchForItem==resItem));
  delete tree;

  TreeType * tree2 = new TreeType{};  
  tree2->PutItemPtoP(1);
  tree2->PutItemPtoP(9);
  delete tree2;

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>constructing tree3" << endl;
  TreeType tree3{};  
  tree3.PutItemPtoP(7);
  tree3.PutItemPtoP(8);

  cout << ">>>>>printing tree3..." << endl;
  tree3.Print(cout);

  TreeType * tree4 = new TreeType{};
  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>insert using reference to pointer" << endl;
  tree4->PutItem(7);
  tree4->PutItem(4);
  tree4->PutItem(2);
  tree4->PutItem(6);
  tree4->PutItem(3);
  tree4->PutItem(5);
  tree4->PutItem(12);
  tree4->PutItem(9);
  tree4->PutItem(19);
  tree4->PutItem(8);
  tree4->PutItem(11);
  tree4->PutItem(15);
  tree4->PutItem(20);

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree4 content..." << endl;
  tree4->Print();

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree4 InOrder..." << endl;
  tree4->Print(OrderType::InOrder);

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree4 PreOrder..." << endl;
  tree4->Print(OrderType::PreOrder);

  cout << endl;
  cout << "_______________________________________" << endl;
  cout << ">>>>>printing tree4 PostOrder..." << endl;
  tree4->Print(OrderType::PostOrder);

  delete tree4;
  
  return 0;
}


