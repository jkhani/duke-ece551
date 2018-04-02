#include "map.h"
#include <stdlib.h>

template<typename K, typename V>
  class BstMap : public Map<K, V>{
 public:
  class Node{

  public:
    K key;
    V value;
    Node * left;
    Node * right;
  Node(K keyn, V valuen):key(keyn), value(valuen), left(NULL), right(NULL){}
  };

  Node * root;
  void destroy(Node * current){
    if(current != NULL){
      destroy(current->left);
      destroy(current->right);
      delete current;
    }
  }

  void copyConstructor_helper(Node* current){
    if(current != NULL){
      add(current->key,current->value);
      copyConstructor_helper(current->left);
      copyConstructor_helper(current->right);
    }
  }

  BstMap<K,V>():root(NULL){}

  virtual void add(const K & key1, const V & value1){
    Node ** current = & root;
    while(*current != NULL){
      if((*current)->key > key1){
	current = &((*current)->left);
      }
      else if((*current)->key < key1){
	current = &((*current)->right);
      }
      else{
	(*current)->value = value1;
	return;
      }
    }
    *current = new Node(key1, value1);
  }

  Node *removeHelp(const K& key,Node *root){
    if (root == NULL) return NULL;
    if (root->key == key){
      if (root->left == NULL && root->right == NULL){
	delete root;
	return NULL;
      }
      if (root->left == NULL && root->right != NULL){
	Node *temp = root->right;
	delete root;
	return temp;
      }
      if (root->left != NULL && root->right == NULL){
	Node *temp = root->left;
	delete root;
	return temp;
      }
      else{
	Node *temp = root->left;
	Node *tempNext = temp->right;
	if (tempNext == NULL){
	  root->key = temp->key;
	  root->value = temp->value;
	  root->left = temp->left;
	  delete temp;
	  return root;
	}
	
	while(tempNext->right != NULL){
	  temp = tempNext;
	  tempNext = tempNext->right;
	}
	root->key = tempNext->key;
	root->value = tempNext->value;
	temp->right = tempNext->left;
	delete tempNext;
	return root;
      }
    }
    else if (root->key > key){
      root->left = removeHelp(key,root->left);
      return root;
    }
    else{
      root->right = removeHelp(key,root->right);
      return root;
    }
  }

  virtual void remove(const K& key){
    root = removeHelp(key,root);
  }

  virtual const V & lookup( const K & key1) const throw (std::invalid_argument){
    Node * ptr = root;
    while(ptr != NULL){
      if(ptr->key == key1){
	return ptr -> value;
      }
      if(ptr -> key > key1){
	ptr = ptr->left;
      }
      else if(ptr -> key < key1){
	ptr = ptr->right;
      }
    }
    throw std::invalid_argument("NOT FOUND");
  }
  virtual ~BstMap<K,V>(){
    destroy(root);
  }

  BstMap<K, V>(const BstMap<K,V> & map1){
    root = NULL;
    copyConstructor_helper(map1.root);
  }

  BstMap<K, V> & operator = (const BstMap<K, V> & rhs){
    if(this != &rhs){
      Node * temp = root;
      root = NULL;
      destroy(temp);
      copyConstructor_helper(rhs.root);
    }
    return * this;
  }

};
