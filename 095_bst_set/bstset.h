#include "set.h"

#include <stdlib.h>

template< typename T>


class BstSet : public Set<T>{

 public:

  class Node{

  public:

    T key;

    Node * left;

    Node * right;

  Node(T keyn):key(keyn), left(NULL), right(NULL){}

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

      add(current->key);

      copyConstructor_helper(current->left);

      copyConstructor_helper(current->right);

    }

  }


  BstSet<T>():root(NULL){}


  virtual void add(const T & key1){

    Node ** current = & root;

    while(*current != NULL){

      if((*current)->key > key1){

	current = &((*current)->left);

      }

      else if((*current)->key < key1){

	current = &((*current)->right);

      }

      else{

	return;

      }

    }

    *current = new Node(key1);

  }


  Node *removeHelp(const T& key,Node *root){

    if (root == NULL)
      return NULL;

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

	  root->left = temp->left;

	  delete temp;

	  return root;

	}

	while(tempNext->right != NULL){

	  temp = tempNext;

	  tempNext = tempNext->right;

	}

	root->key = tempNext->key;

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

  virtual void remove(const T& key){

    root = removeHelp(key,root);

  }


  virtual bool contains(const T & key1) const{

    Node * ptr = root;

    while(ptr != NULL){

      if(ptr->key == key1){

	return true;

      }

      if(ptr -> key > key1){

	ptr = ptr->left;

      }

      else if(ptr -> key < key1){

	ptr = ptr->right;

      }

    }

    return false;

  }

  virtual ~BstSet<T>(){

    destroy(root);

  }

  BstSet<T>(const BstSet<T> & set1){

    root = NULL;

    copyConstructor_helper(set1.root);

  }


  BstSet<T> & operator = (const BstSet<T> & rhs){

    if(this != &rhs){

      Node * temp = root;

      root = NULL;

      destroy(temp);

      copyConstructor_helper(rhs.root);

    }

    return * this;

  }

};

