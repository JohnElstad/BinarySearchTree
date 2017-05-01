using namespace std;


class Node{
 public:
  Node(int newData);
  Node();
  ~Node();
  Node* getLeft(); //returns the node on the left
  Node* getRight();//same as above just on the right
  int getData(); //returns the data that the node points to
  void setLeft(Node* node); //sets the pointer on the left
  void setRight(Node* node); //sets the pointer on the right
 protected:
  int data;
  Node* left;
  Node* right;
};
