#include <iostream>
#include <string>
#include <stack>
#include "Node.h"
#include "TreeNode.h"
#include <cstring>

using namespace std;


/*
Shunting Yard algorithm - Justin He: Takes in a mathematical expression containing ( +, -, *, /, ^),
integer numbers, and parentheses, then traslates into post fix expression.
User is then prompted for which notation (infix, prefix, postfix) to output, from the expression tree.

 */

//function prototypes
void push(Node* &head, string C);
void pop(Node* &head, string C, string &postArray);
void processToken(Node* &stack, string token, string &postArray);
int  isOperator(string C);
bool isNumber(string C);
bool isSpace(string C);
void popParentheses(Node* &head, string op, string &postArray);
void buildExpressionTree(string postArray, TreeNode* &head);
void addToTree(string token, TreeNode* &head);
void printPrefix(TreeNode* head);
string printInfix(TreeNode* head);
void printPostfix(TreeNode* head);
bool NeedParensOnLeft(TreeNode *node);
bool NeedParensOnRight(TreeNode *node);

int main(){

  //initialize variables
  string array= "";
  string postArray = "";
  string output = "";
  string token= "";
  string input= "";
  Node* stack = NULL;
  TreeNode* head = NULL;
  
  cout << "Enter an Infix math expression. Use a space to separate each token. For example: 1 * ( 2 + 3 ) ^ 4" << endl;

  getline(cin, array);

  cout << "The postfix is: " << endl;
  
  //Scan the entered string and process each individual token separated by space  
  for(int i = 0; i < array.length(); i++){
    if (array[i] == ' ' ){
      // if it is a space, then it is the end of the previous token
      processToken(stack, token, postArray);
      token = "";      
    }
    else {
      token = token + array[i]; 
    }
    
  }
  
  // process the last token
  processToken(stack, token, postArray);
  pop(stack, " ", postArray);

  cout << endl;
  
  // cout << "The postfix is: " << endl;
  //cout << postArray << endl << endl; 
  
  //Use postfix string to create the tree
  buildExpressionTree(postArray, head);
  
  input = "";
  while (input != "exit") {
    cout << endl; 
    cout << "Would you like the tree in prefix, infix, or postfix? (Type: prefix, infix, postfix or exit)" << endl;
  
     getline(cin, input);

    //Print the expression tree in 3 ways 
    if (input == "prefix"){
      printPrefix(head);
      cout << endl;
    }
    if (input == "infix"){
      cout << printInfix(head);
      cout << endl;
    }
    if (input == "postfix") {
      printPostfix(head);
      cout << endl;
     }
  }
}


//Function to process the different token types 
void processToken(Node* &stack, string token, string &postArray){
  if (token == " " || token == "") {
    return;
  }

  // if it is a operator (^, + - * /)
  if (isOperator(token) >0){

    // When the token is not a ^
    if (token != "^") {
      pop(stack, token, postArray);
    }
    
    // Push the operator 
    push(stack, token);
  }

  /// if it is an operand (number):
  if (isNumber(token) == true){
    postArray = postArray + token + " "; 
    cout << token << " ";
  }
  
  if (token == "("){
    push(stack, token);
  }
  
  if (token == ")"){
    popParentheses(stack, token, postArray);
  }
}

//Evaluate if the character is an operator
// if is operator, return the precedence: 1 for +-, 2 for */ and 3 for ^
int isOperator(string C){

  if (C == "+" || C == "-"){
    return 1;
  }
  if (C == "*" || C == "/"){
    return 2;
  }
  if (C == "^"){
    return 3;
  }
  else return 0;
}

//Evaluate if the character is a letter or number 
bool isNumber(string C){
  if (C[0] >= '0' && C[0] <= '9'){
    return true;
  }
  if (C[0] >= 'a' && C[0] <= 'z'){
    return true;
  }
  if (C[0] >= 'A' && C[0] <= 'Z'){
    return true;
  }
  else {
    return false;
  }
}

//evaluate if the character is a space
bool isSpace(string C){
  if (C[0] == ' '){
    return true;
  }
  else {
    return false;
  }
}

// pushes an operator into the stack
void push(Node* &head, string C){
  Node* temp = new Node;
  temp->setValue(C);
  if (head == NULL){
    temp->setNext(NULL);
    head = temp;
  }
  else {
    temp->setNext(head);
    head = temp;
  }
}

// function to pop the head value of the stack
void pop(Node* &head, string op, string &postArray){
  Node* temp;
  temp = head;
  string tempOp;
  
  while (temp != NULL && isOperator(temp->getValue()) >= isOperator(op)){

    postArray = postArray + temp->getValue() + " ";
    
    cout << temp->getValue() << " ";
    head = temp->getNext();
    delete temp;
    temp = head;
    }
}

//Special pop case for when there are parentheses
void popParentheses(Node* &head, string op, string &postArray){
  Node* temp;
  temp = head;

  while (temp != NULL && temp->getValue() != "("){
    cout << temp->getValue() << " ";

    // add to postArray
    postArray = postArray + temp->getValue() + " ";

    head = temp->getNext();
    delete temp;
    temp = head;
    }

  // for right ( 
  if (temp != NULL && temp->getValue() == "("){
    head = temp->getNext();
    delete temp;
    temp = head;
  }
}

//Take the postfix expression and builds a tree; head returns the root of the tree
void buildExpressionTree(string postArray, TreeNode* &head){
  string token = "";
  
  int length = postArray.length();
   for(int i = 0; i < length; i++){
    if (postArray[i] == ' '){
      //cout << token << endl;
      addToTree(token, head);
      token= "";
    }
    else {
      token = token + postArray[i]; 
    }
  }

   //addToTree(token, head); // add a new one?

}

//Add a single number or operator into the expression tree
void addToTree(string token, TreeNode* &head){
  if(token == " " || token == ""){
    //Return if there is nothing
    return;
  }
 
  // if it is number, then add to tree
  if(isNumber(token) == true){
    TreeNode* newNode = new TreeNode;
    newNode->setValue(token);
    newNode->setNext(head);
    head = newNode;
  }

  //If isoperator has return of 1, 2 or 3
  if(isOperator(token)){
    TreeNode* temp = new TreeNode;
    temp->setValue(token);
    temp->setRight(head);
    head = head->getNext();
    temp->setLeft(head);
    head = head->getNext();
    temp->setNext(head);
    head = temp;
  }
}

//Print tree in infix (recursive)
/*void printInfix(TreeNode* head){
  if (head == NULL){
    return;
  }
  printInfix(head->getLeft());
  cout << head->getValue() << " ";
  printInfix(head->getRight());
}
*/

// Infix print of the tree (recursive).  Add in the parences based on precedence
string printInfix(TreeNode* head) {
  if (head == NULL) return "";

  if (isNumber(head->getValue()))
      return head->getValue();

  string lhs = "";
  string rhs = "";

  //recursive call to left tree 
  lhs = printInfix(head->getLeft());

  if (NeedParensOnLeft(head))
     lhs = "( " + lhs + " )";

  //recursive call to right tree
  rhs = printInfix(head->getRight());

  if (NeedParensOnRight(head))
    rhs = "( " + rhs + " )";
  
  return lhs + " " + head->getValue() + " " + rhs;
	  
}

// Print tree in prefix (recursive)
void printPrefix(TreeNode* head){
  if (head == NULL){
    return;
  }
  cout << head->getValue() << " ";
  printPrefix(head->getLeft());
  printPrefix(head->getRight());
}

// print tree in postfix (recursive)
void printPostfix(TreeNode* head){
  if (head == NULL){
    return;
  }
  printPostfix(head->getLeft());
  printPostfix(head->getRight());
  cout << head->getValue() << " ";
}

// check if it needs to add parenthesis on the left side
bool NeedParensOnLeft(TreeNode *node) {

  if (node == NULL) return false; 
  if (node->getLeft() == NULL)
    return false;

 
  return (isOperator(node->getLeft()->getValue()) &&
	  isOperator(node->getLeft()->getValue()) <  isOperator(node->getValue()));
}

// check if it needs to add parenthesis on the right hand side
bool NeedParensOnRight(TreeNode *node) {

  if (node == NULL)
    return false;

  if (node->getRight() == NULL)
    return false; 

  if (isNumber(node->getRight()->getValue())) 
    return false;
  
  if (node->getValue() == "+" || node->getValue() == "*")
    return (isOperator(node->getRight()->getValue()) < isOperator(node->getValue()));
	    
  return (isOperator(node->getRight()->getValue()) <= isOperator(node->getValue()));
}
      
 
