#ifndef TREE_H
#define TREE_H

using namespace std;

class tree
{
 public:
  tree(char*);
  // setters
  void setRight(tree*);
  void setLeft(tree*);
  void setNext(tree*); 
  
  //getters
  tree* getRight();
  tree* getLeft();
  tree* getNext();
  char* getData();

  tree* next = NULL;
  tree* left = NULL;
  tree* right = NULL;
  char* data; 
};
#endif
