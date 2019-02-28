#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

Node::Node(){
  next = NULL;

}

Node::~Node(){

}
  

// get next

Node* Node::getNext(){
  return next;
}

// get value

string Node::getValue(){
  return value;
}

//set next

void Node::setNext(Node* newNext){
  next = newNext;
}

// set value to the operator being passed in
void Node::setValue(string C){
  value = C;
}




