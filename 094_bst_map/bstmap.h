#ifndef __BSTMAP_H__
#define __BSTMAP_H__

#include "map.h"
#include <iostream>

template<typename K, typename V>
  class BstMap : public Map <K, V> {
 private:

  class Node{
  public:
    K key;
    V value;
    Node *parent;
    Node *left;
    Node *right;
  Node(K key_in, V val_in, Node * parent_in, Node * left_in, Node * right_in):
    key(key_in), value(val_in), parent(parent_in), left(left_in), right(right_in){}

  };

  Node* root;
  int numOfKeys;
 public:

 BstMap(): root(NULL), numOfKeys(0) {}
  ~BstMap(){}

  virtual Node* findNode(Node* sub_root, K key){

    if(numOfKeys > 0){
      Node *curr_node = sub_root;
      if (key == curr_node->key){
	return curr_node;
      }
      else if (key > curr_node->key){
	return findNode(curr_node->right, key);
      }
      else {
	return findNode(curr_node->left, key);
      }
    }
    else {
      return NULL;
    }
  }
};

#endif
