#ifndef TREENODE_H
#define TREENODE_H
#include <string>
using namespace std;

// definition of TreeNode class
class TreeNode{
 public:
  TreeNode();
  ~TreeNode();
  TreeNode* getRight();
  TreeNode* getLeft();

  void setLeft(TreeNode* newLeft);
  void setRight(TreeNode* newRight);
  TreeNode* getNext();
  void setNext(TreeNode* newNext);
  string getValue();
  void setValue(string newValue);
 private:
  
  TreeNode* left;
  TreeNode* right;
  TreeNode* next;
  string value;
  
};

#endif
