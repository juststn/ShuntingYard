#include <iostream>
#include "TreeNode.h"
#include <string>

using namespace std;

// class of TreeNode
// constructor
TreeNode::TreeNode(){
  next = NULL;
  left = NULL;
  right = NULL;
  value = "";
}

// destructor
TreeNode::~TreeNode(){
  
}

// set left node
void TreeNode::setLeft(TreeNode* newLeft){
  left = newLeft;
}

// set right node
void TreeNode::setRight(TreeNode* newRight){
  right = newRight;
}

//get left node
TreeNode* TreeNode::getLeft(){
  return left;
}

// get right node
TreeNode* TreeNode::getRight(){
  return right;
}

// get next node
TreeNode* TreeNode::getNext(){
  return next;
}

// set next node
void TreeNode::setNext(TreeNode* newNext){
  next = newNext;
}

// get value
string TreeNode::getValue(){
  return value;
}

// ste value
void TreeNode::setValue(string newValue){
  value = newValue;
}





