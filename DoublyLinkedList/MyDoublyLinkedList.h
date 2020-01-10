#pragma once
#ifndef MYDOUBLYLINKEDLIST_H
#define MYDOUBLYLINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct Node {
	int index;
	T data;
	Node<T>* next;
	Node<T>* prev;
};

template <typename T>
class MyDoublyLinkedList{
private:
	Node<T>* head;		// keeps track of the first node in the doubly linked list
	Node<T>* tail;		// keeps track of the last node in the doubly linked list
	int size;

private:
	void setIndexes();

public:
	/* constructor */
	MyDoublyLinkedList();

	/* insertions */
	void insert(T data);
	void append(T data);
	void prepend(T data);
	void emplace(T data, int pos);

	/* deletions */
	void deleteNode(int pos);
	void deleteHead();
	void deleteTail();

	/* getters */
	T getData(int pos);
	Node<T>* getNode(int pos);
	T getHead();
	T getTail();
	int getSize();
	void printList();
	void printIndexes();
};

/*************CONSTRUCTOR*************/

/* basic constructor */
template <typename T>
MyDoublyLinkedList<T>::MyDoublyLinkedList() {
	cout << "Node head and tail created" << endl;
	this->head = NULL;
	this->tail = NULL;
	this->size = 0;
}

/**************INSERTIONS**************/

/* adds a node to the end of the doubly linked list */
template <typename T>
void MyDoublyLinkedList<T>::insert(T data) {
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	newNode->next = NULL;
	newNode->prev = NULL;

	if (this->head == NULL) {
		newNode->index = 0;
		this->head = newNode;
		this->tail = newNode;
		this->size++;
		return;
	}

	Node<T>* current = this->head;
	while (current != NULL) {
		current = current->next;
	}

	current = newNode;		// have current (which is NULL at this point) set to the newNode
	newNode->index = this->tail->index + 1;		// update the new node's index by incrementing the tail's index by 1
	newNode->prev = this->tail;		// connect the new node's [prev] link to the current tail (which has not been updated yet)
	this->tail->next = newNode;		// have the current tail's [next] link set to the newest node 
	newNode->next = NULL;
	this->tail = newNode;		// update the tail

	size++;
}

/* adds a node to the end of the linked list */
template <typename T>
void MyDoublyLinkedList<T>::append(T data) {
	Node<T>* newNode = new Node<T>;		// DID NOT HAVE <T> IF THIS BREAKS STUFF
	newNode->data = data;
	newNode->next = NULL;

	if (this->head == NULL) {		// if the list is empty then set both the head and tail equal to the same newly inserted node
		newNode->index = 0;
		this->head = newNode;
		this->tail = newNode;
		size++;
		return;
	}

	newNode->index = this->tail->index + 1;		// update the new node's index by incrementing the tail's index by 1
	newNode->prev = this->tail;		// connect the new node's [prev] link to the current tail (which has not been updated yet)
	this->tail->next = newNode;		// have the current tail's [next] link connect to the new node
	newNode->next = NULL;
	this->tail = newNode;		// update the tail 

	this->size++;
}

/* will add a new node to the front of the list */
template <typename T>
void MyDoublyLinkedList<T>::prepend(T data) {
	Node<T>* newNode = new Node<T>;
	newNode->data = data;
	newNode->prev = NULL;
	newNode->next = this->head;
	this->head = newNode;

	this->size++;
	setIndexes();
}

/* will create and fit a node inbetween other nodes 
   NOTE: this will take the place of an existing node and "shift" everything to the right */
template <typename T>
void MyDoublyLinkedList<T>::emplace(T data, int pos) {
	Node<T>* current = this->head;
	Node<T>* previous;
	Node<T>* newNode = new Node<T>;
	newNode->data = data;

	if (pos == 0) {		// case of wanting to place the node in the beginning of the list
		prepend(data);
	}
	else if (pos == this->size-1) {		// case of wanting to place the node at the end of the list
		previous = this->tail->prev;		// have previous hold the node before the tail
		previous->next = newNode;		// have the previous node's next link point to the newest node
		newNode->prev = previous;		// have the newest node's prev link point to previous
		newNode->next = this->tail;		// have the newest node's next link point to the tail
		this->tail->prev = newNode;
		this->tail->next = NULL;
	}
	else {
		while (current != NULL) {
			if (current->index == pos) {		// I HAVEN'T TESTED THIS YET
				previous->next = newNode;
				newNode->prev = previous;
				newNode->next = current;
				current->prev = newNode;
			}
			else {
				previous = current;
				current = current->next;
			}
		}
	}
}

/**************DELETIONS**************/

/* deletes a node from the doubly linked list */
template <typename T>
void MyDoublyLinkedList<T>::deleteNode(int pos) {
	Node<T>* current = this->head;
	Node<T>* previous = this->head;
	Node<T>* nodeToDelete = this->head;

	if (pos >= 0 && pos < this->size) {		// confirm that the index is within range
		if (pos == this->head->index) {		// case of the head needing to be deleted		
			current = current->next;		// current will be the head
			current->prev = NULL;		
			delete nodeToDelete;		// delete the node
			this->size--;		// decrease the size by 1
			this->head = current;		// update the head
			setIndexes();
			return;
		}
		else if (this->tail->index == pos) {		// case of the tail needing to be deleted
			current = this->tail->prev;		// have current equal the node before the tail
			nodeToDelete = this->tail;
			delete nodeToDelete;
			current->next = NULL;

			this->size--;
			this->tail = current;
			setIndexes();
			return;
		}
		else {
			while (true) {
				if (current->index == pos) {		// match found, delete node
					nodeToDelete = current;
					current = current->next;		// have current hold the node after the node to be deleted
					previous->next = current;		// connect the node before the node to be delete to the node that comes after the node to be deleted
					current->prev = previous;		// connect the node after the node to be delete to the node that comes before the node to be deleted
					delete nodeToDelete;
					this->size--;
					setIndexes();
					return;
				}
				else {
					previous = current;
					current = current->next;
				}
			}
		}
	}
	else {
		cout << "out of bounds\n";
	}
}

/* will delete the head of the list
   NOTE: does not handle the case of an empty list yet*/
template <typename T>
void MyDoublyLinkedList<T>::deleteHead() {
	Node* nodeToDelete = this->head;
	Node* current = this->head;

	current = current->next;
	delete nodeToDelete;
	this->head = current;

	size--;
	setIndexes();
}

/* will delete the tail of the list
   NOTE: does not handle the case of an empty list yet*/
template <typename T>
void MyDoublyLinkedList<T>::deleteTail() {
	Node* nodeToDelete = this->tail;
	Node* current = this->tail;

	current = current->prev;
	delete nodeToDelete;
	this->tail = current;

	size--;
	setIndexes();
}

/**************GETTERS**************/

/* returns the data of a node */
template <typename T>
T MyDoublyLinkedList<T>::getData(int pos) {
	Node<T>* current = this->head;
	if (pos >= 0 && pos < this->size) {
		while (true) {
			if (current->index == pos) {
				return current->data;
			}
			else {
				current = current->next;
			}
		}
	}
	else {
		return NULL;
	}
}

/* returns a node from the doubly linked list */
template <typename T>
Node<T>* MyDoublyLinkedList<T>::getNode(int pos) {
	Node<T>* current = this->head;
	if (pos >= 0 && pos < this->size) {
		while (true) {
			if (current->index == pos) {
				return current;
			}
			else {
				current = current->next;
			}
		}
	}
	else {
		return NULL;
	}
}

/* returns the head's data*/
template <typename T>
T MyDoublyLinkedList<T>::getHead() {
	return this->head->data;
}

/* returns the tail's data */
template <typename T>
T MyDoublyLinkedList<T>::getTail() {
	return this->tail->data;
}

/* returns the size of the doubly linked list */
template <typename T>
int MyDoublyLinkedList<T>::getSize() {
	return this->size;
}

/* prints out the contents of the doubly linked list */
template <typename T>
void MyDoublyLinkedList<T>::printList() {
	Node<T>* current = this->head;

	//cout << "printing list\n";
	while (current != NULL) {
		cout << current->data << "\n";
		current = current->next;
	}
}

/* prints out the indexes of the doubly linked list */
template <typename T>
void MyDoublyLinkedList<T>::printIndexes() {
	Node<T>* current = this->head;
	
	cout << "printing indexes\n";
	while (current != NULL) {
		cout << current->index << "\n";
		current = current->next;
	}
}

/***************UNIQUE***************/

/* properly assigns the correct index to each node after a deletion has occured 
   NOTE: only call this function after the size has been decremented by 1 AND
   the head or tail have been properly updated!! */
template <typename T>
void MyDoublyLinkedList<T>::setIndexes() {
	Node<T>* current = this->head;

	for (int i = 0; i < this->size; i++) {
		current->index = i;
		current = current->next;
	}
}

#endif