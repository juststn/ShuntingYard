#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <string>

using namespace std;
//Class Definition for Node class

class Node{
 public:
  Node();
  ~Node();
  Node* getNext();
  void setNext(Node* newNext);
  void setValue(string C);
  string getValue();
 private:
  Node* next;
  string value;
};
#endif
