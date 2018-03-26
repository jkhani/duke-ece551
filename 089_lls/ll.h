#ifndef _LL_H_

#define _LL_H_

#include <cstdlib>

#include <exception>

#include <assert.h>

#include <stdio.h>

#include <iostream>

//YOUR CODE GOES HERE


class OutOfBoundException:public std::exception{

 public:

  const char* what()const throw()
  {

    return "Error! Index doesn't exist.\n";

  }

};


template<typename T>

class LinkedList{

 private:
  class Node{

  public:
    T data;

    Node * next;

    Node * previous;

  Node(const T & d):data(d),next(NULL),previous(NULL){}

  Node(const T & d, Node * n, Node * p):data(d), next(n),previous(p){}

  };

  int size;

  Node * head;

  Node * tail;

 public:
  void addFront(const T & item){

    head = new Node(item, head, NULL);

    if(tail == NULL){

      tail = head;
    }

    else{

      head->next->previous = head;

    }

    size++;
  }

  void addBack(const T & item){

    tail = new Node(item, NULL, tail);

    if(head == NULL){

      head = tail;

    }

    else{

      tail->previous->next = tail;

    }

    size++;

  }

  bool remove(const T &item){

    Node * ptr = head;

    if(ptr == NULL) return false;

    else if(ptr->data == item){

      head  = ptr->next;
      if(ptr->next!=NULL){

	ptr -> next ->previous = NULL;

      }

      else{

	tail = NULL;

      }

      delete ptr;

      size--;

      return true;

    }

    else{

      ptr = ptr->next;

      while(ptr!=NULL){

	if(ptr->data == item){

	  ptr->previous->next = ptr->next;

	  if(ptr->next !=NULL){

	    ptr->next->previous = ptr->previous;

	  }

	  else{

	    tail = ptr->previous;

	  }

	  delete ptr;

	  size--;

	  return true;

	}

	ptr = ptr->next;

      }

      return false;

    }

  }

  T & operator[](int index){

    int c = 0;

    Node * p = head;

    while(p!=NULL){

      if(c==index){

	return p->data;

      }

      p = p->next;

      c ++;

    }

    throw OutOfBoundException();

    ///    return sha;//ruguomeizhaodao

    //hhhhhhhhhhhh

  }

  T & operator[](int index)const{

    int c = 0;

    Node * p = head;

    while(p!=NULL){

      if(c==index){

	return p->data;

      }

      p = p->next;

      c ++;

    }

    throw OutOfBoundException();
    //hhhhhhhhhhhh
  }

  int find(const T &item)const{

    if(head==NULL) return -1;

    else{

      Node *const* ptr = &head;

      int index = 0;

      while(*ptr!=NULL){

	if((*ptr)->data == item){

	  return index;

	}

	ptr = &((*ptr) ->next);
	index++;

      }

      return -1;

    }

  }


 LinkedList():size(0),head(NULL),tail(NULL){}

 LinkedList(const LinkedList & linked):size(linked.size) {

    if(linked.head ==NULL){

      head =NULL;

      tail =NULL;

    }

    else{

      head = new Node(linked.head->data,NULL,NULL);

      Node * ptr = head;

      Node * ptrl = linked.head;

      while(ptrl->next!=NULL){

	ptr->next = new Node(ptrl->next->data,NULL,ptr);

	ptr = ptr->next;

	ptrl = ptrl->next;

      }

      tail =ptr;

    }

  }

  LinkedList & operator = (const LinkedList &rhs){

    if(this != &rhs){

      Node * temp = head;

      if(rhs.head ==NULL){

	head = NULL;

	tail = NULL;

	size = 0;

      }

      else{

	head = new Node(rhs.head->data,NULL,NULL);

	Node * ptr = head;

	Node * ptrl = rhs.head;

	while(ptrl->next!=NULL){

	  ptr->next = new Node(ptrl->next->data,NULL,ptr);

	  ptr = ptr->next;

	  ptrl = ptrl->next;

	}

	tail = ptr;

	size = rhs.size;

      }

      if(temp !=NULL){

	while(temp->next!=NULL){

	  temp = temp->next;

	  delete temp->previous;

	}

	delete temp;

      }

    }

    return *this;

  }

  ~LinkedList(){

    Node * ptr = head;

    if(head!=NULL){

      while(ptr->next!=NULL){

	ptr = ptr->next;

	delete ptr->previous;

      }

      delete ptr;

    }

  }

  int getSize()const{
    return size;
  }
};

#endif
