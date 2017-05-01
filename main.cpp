#include <iostream>
#include <cstring>
#include <fstream>
#include "Node.h"


using namespace std;

void strToLower(char* a);
void addNode(Node* head, int number, Node* &treeHead);
void printTree(Node* head, int level);
Node* nodeSearch (Node* head, int number, Node* &parent, bool &right);
bool deleteNode(Node* &head, int number); 

void configureInput(ifstream &stream, bool &isFile){
   
  char input[128];
  isFile = false;
  
  cout << "Read from File or Input text?" << endl;
  cin.getline(input,128);
  strToLower(input);
  
  if(input[0] == 'f'){
    cout << "What file?" << endl;
    cin.getline(input,128);
    stream.open(input);
    if(stream.is_open()){
      isFile = true;
    }
    else{
      cout << "Could not open file" << endl;
      cout << "Enter by command line" << endl;
    }
  }
  else{
    cout << "Enter by command line" << endl;
  }
}
void addNumbers(istream &from, Node* &head){
 
  int newInput;
  from >> newInput;
  addNode(head,newInput,head);
  while(from.peek() != '\n' && !from.eof()){
    if(isdigit(from.peek())){
      from >> newInput;
      addNode(head,newInput,head);
    }
    else{
      from.ignore();
    }
  }
}

int main(){
  
  Node* head = NULL;
  bool running = true;
  char input[30];
  cout<<"Valid commands are print,add,search and delete"
  while (running == true){
    cin.getline(input,30);
    strToLower(input);
    if (!strcmp(input,"add")){
      ifstream stream;
      bool isFile;
      configureInput(stream, isFile);
      addNumbers(isFile ? stream : cin, head);
      if(isFile) stream.close();
      cin.ignore();
    }
    else if (!strcmp(input,"print")){
      if(head){
	printTree(head,0);
      }
      else
	cout << "Nothing to print" << endl;
    }
    else if(!strcmp(input,"search")){
      if (head){
	cout << "What number are you looking for?" << endl;
	int number;
	Node* parent;
	bool right;
	cin >> number;
	if (nodeSearch(head,number,parent,right)){
	  cout << number << " is in the tree" << endl;
	}
	else{
	  cout << number << " is not in the tree" << endl;
	}
      }
      else{
	cout << "The tree is empty therefore you cant search it!" << endl;
      }
    }
    else if(!strcmp(input,"delete")){
      if (head){
        cout << "What number are you trying to delete?" << endl;
        int number;
	cin >> number;
	if (deleteNode(head,number)){
	  cout << number << " Has been deleted" << endl;
        }
        else{
          cout << number << " is not in the tree" << endl;
        }
      }
      else{
        cout << "The tree is empty therefore you cannot delete." << endl;
      } 
    }	   
    else{
      cout << "Valid Commands Only Please" << endl;
     
    }
  }
} 

void strToLower(char* a){ 
  while(*a){
    *a = tolower(*a);
    a++;
  }
}
void addNode(Node* head, int number, Node* &treeHead){
  if (treeHead == NULL){
    treeHead = new Node(number);
  }
  else if (number < head->getData()){
    if (head->getLeft()){
      addNode(head->getLeft(),number,treeHead);
    }
    else{
      head->setLeft(new Node(number));
    }
  }
  else if (number > head->getData()){
    if (head->getRight()){
      addNode(head->getRight(),number,treeHead);
    }
    else{
      head->setRight(new Node(number));
    }
  }
}
void printTree(Node* head, int level){
  level ++;
  if(head->getRight()){
    printTree(head->getRight(), level);
  }
  for (int i = 0; i < level; i++){
    cout << " ";
  }
  cout << head->getData() << endl;
  if(head->getLeft()){
    printTree(head->getLeft(), level);
  } 
}
Node* nodeSearch(Node* head, int number, Node* &parent, bool &right){
  if (number < head->getData()){
    if(head->getLeft()){
      right = false;
      parent = head;
      return nodeSearch(head->getLeft(), number, parent,right);
    }
    else return NULL;
  }
  else if (number > head->getData()){
    if(head->getRight()){
      right = true;
      parent = head;
      return nodeSearch(head->getRight(), number,parent,right);
    }
    else return NULL;
  }
  else return head;
}
bool deleteNode(Node* &head, int number){
  Node* parent;
  Node* dNode;
  bool right;
  Node* toSwap = NULL;
  dNode = nodeSearch(head,number,parent,right);
  if (!dNode){
    return false;
  }
  if (!dNode->getLeft() && !dNode->getRight()){
    toSwap = NULL;
  }
  else if(!dNode->getRight()){
    toSwap = dNode->getLeft();
  }
  else if(!dNode->getLeft()){
    toSwap = dNode->getRight();
  }
  else if(!dNode->getLeft()->getRight()){
    Node* current = dNode->getLeft();
    current->setRight(dNode->getRight());
    toSwap = current;
  }
  else{
    Node* leftRoot = dNode->getLeft();
    Node* current = dNode->getLeft()->getRight();
    Node* currentParent = leftRoot;
    while(current->getRight()){
      currentParent = current;
      current = current->getRight();
    }
    currentParent->setRight(current->getLeft());
    current->setLeft(leftRoot);
    current->setRight(dNode->getRight());
    toSwap = current; 
  
  }
  if(head == dNode) head = toSwap;
  else if(right) parent->setRight(toSwap);
  else parent->setLeft(toSwap);
  return true;
}
