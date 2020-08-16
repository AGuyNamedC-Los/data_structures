#pragma once
#ifndef BASICTREE_H
#define BASICTREE_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
struct Node {
	T data;
	Node<T>* leftChild;
	Node<T>* rightChild;
};

template <typename T>
class BasicTree {
private:
	Node<T>* root;
	int depth;	// number of edges from any node to the tree's root node
	int height;	// number of edges on the longest path from the node to a leaf node

private:
	/* unique */
	Node<T>* getNewNode(T Data);

public:
	/* constructor */
	BasicTree();

	/* insertions */
	void insert(T data);

	/* deletions */
	bool deleteNode(T data);		// in progress

	/* getters */
	T getNodeData(T data);
	Node<T>* getNode(T data);

	/* searches */
	bool isNodePresent(T data);

	/* printers */
	void printDFS();
	void printBFS();
	void printNode(T data);

	/* unique */
	Node<T>* inOrderSuccessor(Node<T> *node);
};

/* -----------------------------------------------------------------CONSTRUCTOR----------------------------------------------------------------- */
template <typename T>
BasicTree<T>::BasicTree() {
	this->root = NULL;
	this->depth = 0;
	this->height = 0;
}

/* -----------------------------------------------------------------UNIQUE----------------------------------------------------------------- */
/* private function to return a newly created node */
template <typename T>
Node<T>* BasicTree<T>::getNewNode(T data) {
	Node<T>* newNode = new Node<T>;	// allocate a new node
	/* set the variables of the node*/
	newNode->data = data;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}

/* -----------------------------------------------------------------INSERTIONS----------------------------------------------------------------- */
/* inserts a node into the tree where the node with the smaller data is to the left and the bigger data being on the right*/
template <typename T>
void BasicTree<T>::insert(T data) {
	if (this->root == NULL) {
		this->root = getNewNode(data);
		cout << "added root\n";
		return;
	}

	Node<T>* parent = NULL;
	Node<T>* currentNode = *&this->root;	// directly affects root instead of a copy

	while (currentNode != NULL) {
		if (data == currentNode->data) {		// travel down the right branch if data is the same
			parent = currentNode;
			currentNode = currentNode->rightChild;
		} else if (data < currentNode->data) {	// travel down the left branch
			parent = currentNode;
			currentNode = currentNode->leftChild;
		} else {	// travel down the right branch
			parent = currentNode;
			currentNode = currentNode->rightChild;
		}
	}

	if (data < parent->data)		// put new node as left child
		parent->leftChild = getNewNode(data);
	else    // put new node as right child
		parent->rightChild = getNewNode(data);
}

/* -----------------------------------------------------------------DELETIONS----------------------------------------------------------------- */
template <typename T>
bool BasicTree<T>::deleteNode(T data) {
	Node<T>* currentNode = *&this->root;

	// search for the node
	while (currentNode != NULL && currentNode->data != data) {
		if (data < currentNode->data) currentNode = currentNode->leftChild;
		else currentNode = currentNode->rightChild;
	}

	if(currentNode == NULL) {
		cout << "could not find: " << data << " in tree!\n";
		return false;
	}

	// node has no children
	if (currentNode->leftChild == NULL && currentNode->rightChild == NULL) {
		delete currentNode;
		return true;
	}

	// node has one child
	if (currentNode->leftChild == NULL || currentNode->rightChild == NULL) {
		if (currentNode->leftChild == NULL)
			currentNode = currentNode->rightChild;
		else
			currentNode = currentNode->leftChild;
	}

	// node has two children
	// find node's in order successor and it's parent (if available)
	Node<T>* temp = currentNode->rightChild;
	Node<T>* parent = NULL;
		
	while (temp->leftChild != NULL) {
		parent = temp;
		temp = temp->leftChild;
	}

	// if no parent found (there is no left subtree for temp (the current node's right child))
	if (parent == NULL) {
		if (temp->rightChild == NULL) temp->rightChild = NULL;
		currentNode->rightChild = temp->rightChild;
	} else {
		parent->leftChild = temp->rightChild;
	}

	currentNode->data = temp->data;
	delete temp;

	return true;
}

/* -----------------------------------------------------------------GETTERS----------------------------------------------------------------- */
template <typename T>
T BasicTree<T>::getNodeData(T data) {
	Node<T>* currentNode = this->root;

	while (currentNode != NULL) {
		if (data == currentNode->data) {
			return currentNode->data;
		} else if (data < currentNode->data) {	// travel down left branch
			currentNode = currentNode->leftChild;
		} else {	// travel down right branch
			currentNode = currentNode->rightChild;
		}
	}

	return NULL;
}

template <typename T>
Node<T>* BasicTree<T>::getNode(T data) {
	Node<T>* currentNode = this->root;
	stack<Node<T>*> nodeStack;

	while (currentNode != NULL) {
		if (data == currentNode->data) {
			return currentNode;
		}
		else if (data < currentNode->data) {	// travel down left branch
			currentNode = currentNode->leftChild;
		}
		else {	// travel down right branch
			currentNode = currentNode->rightChild;
		}
	}
	return NULL;
}

/* -----------------------------------------------------------------SERACHES----------------------------------------------------------------- */
/* Searches through the tree and returns true if a node is found that the user wants, false if not */
template <typename T>
bool BasicTree<T>::isNodePresent(T data) {
	Node<T> currentNode = this->root;

	while (currentNode != NULL) {
		if (data == currentNode->data) {	
			return true;
		} else if (data < currentNode->data) {	// travel down left branch
			currentNode = currentNode->leftChild;
		} else {
			currentNode = currentNode->rightChild;	// travel down right branch
		}
	}

	return false;
}

/* -----------------------------------------------------------------PRINTERS----------------------------------------------------------------- */
/* prints the tree in a Depth First Search fashion*/
template <typename T>
void BasicTree<T>::printDFS() {
	Node<T>* currentNode = *&this->root;
	stack<Node<T>*> nodeStack;

	/* case of an empty tree */
	if (this->root == NULL) { return; }

	/* case of just the root*/
	if (this->root->leftChild == NULL && this->root->rightChild == NULL) {
		cout << this->root->data;
		return;
	}

	/* case of root having just one child */

	/* keep traveling left until we reach a null node, then pop from the stack and travel right (if possible) then travel left, repeat */
	while (!nodeStack.empty() || currentNode != NULL) {
		if (currentNode != NULL) {
			nodeStack.push(currentNode);
			currentNode = currentNode->leftChild;	// travel left
		}
		else {	// means we reached a null node
			currentNode = nodeStack.top();	// get the node at the top of the stack, which is the leftmost node at the moment
			cout << currentNode->data << " ";
			nodeStack.pop();

			currentNode = currentNode->rightChild;	// travel right
		}
	}
	delete currentNode;
}

/* prints the tree in a Breadth First Search fashion*/
template <typename T>
void BasicTree<T>::printBFS() {
	Node<T>* currentNode;
	queue<Node<T>*> nodeQueue;

	/* case of an empty tree */
	if (this->root == NULL) { return; }

	/* case of just the root */
	if (this->root->leftChild == NULL && this->root->rightChild == NULL) {
		cout << this->root->data;
		return;
	}

	nodeQueue.push(*&this->root);	// push the root to the queue first
	while (!nodeQueue.empty()) {
		currentNode = nodeQueue.front();
		cout << currentNode->data << " ";
		nodeQueue.pop();		

		if (currentNode->leftChild != NULL) { nodeQueue.push(currentNode->leftChild); }	// queue the left child of current node
		if (currentNode->rightChild != NULL) { nodeQueue.push(currentNode->rightChild); }	// queue the right child of current node
	}
}

template <typename T>
void BasicTree<T>::printNode(T data) {
	Node<T> currentNode = this->root;
	
	while (currentNode != NULL) {
		if (data == currentNode->data) {
			cout << currentNode->data;
			return;
		} else if (data < currentNode->data) {	// travel down left branch
			currentNode = currentNode->leftChild;
		} else {
			currentNode = currentNode->rightChild;	// travel down right branch
		}
	}
	cout << "could not find node with data: " << data;
}

template <typename T>
Node<T>* BasicTree<T>::inOrderSuccessor(Node<T>* node) {
	Node<T>* currentNode = node;
	while (currentNode != NULL && currentNode->leftChild != NULL) { currentNode = currentNode->leftChild; }

	return currentNode;
}

#endif