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

	/* getters */
	T getData_DFS(T data);
	int getData_BFS(T data);
	Node<T>* getNode_DFS(T data);
	Node<T> getNode_BFS(T data);

	/* searches */

	/* printers */
	void printDFS();
	void printBFS();
	void printNode_DFS(T data);
	void printNode_BFS(T data);
};

template <typename T>
BasicTree<T>::BasicTree() {
	this->root = NULL;
	this->depth = 0;
	this->height = 0;
}

template <typename T>
Node<T>* BasicTree<T>::getNewNode(T data) {
	Node<T>* newNode = new Node<T>;	// allocate a new node
	/* set the variable of the node*/
	newNode->data = data;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}

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

template <typename T>
T BasicTree<T>::getData_DFS(T data) {
	Node<T>* currentNode = this->root;
	stack<Node<T>*> nodeStack;

	/* case of an empty tree */
	if (this->root == NULL) { return NULL; }

	/* case of just the root*/
	if (this->root->leftChild == NULL && this->root->rightChild == NULL) { return this->root->data; }

	/* keep traveling left until we reach a null node, then pop from the stack and travel right (if possible) then travel left, repeat */
	while (!nodeStack.empty() || currentNode != NULL) {
		if (currentNode != NULL) {
			if (currentNode->data == data) {
				return currentNode->data;
			}
			nodeStack.push(currentNode);
			currentNode = currentNode->leftChild;	// travel left
		}
		else {	// means we reached a null node
			currentNode = nodeStack.top();	// get the node at the top of the stack, which is the leftmost node at the moment
			nodeStack.pop();

			currentNode = currentNode->rightChild;	// travel right
		}
	}

	return NULL;
}

template <typename T>
int BasicTree<T>::getData_BFS(T data) {

}

template <typename T>
Node<T>* BasicTree<T>::getNode_DFS(T data) {
	Node<T>* currentNode = this->root;
	stack<Node<T>*> nodeStack;

	/* case of an empty tree */
	if (this->root == NULL) { return NULL; }

	/* case of just the root*/
	if (this->root->leftChild == NULL && this->root->rightChild == NULL) { return this->root; }

	/* keep traveling left until we reach a null node, then pop from the stack and travel right (if possible) then travel left, repeat */
	while (!nodeStack.empty() || currentNode != NULL) {
		if (currentNode != NULL) {
			if (currentNode->data == data) {
				return currentNode;
			}
			nodeStack.push(currentNode);
			currentNode = currentNode->leftChild;	// travel left
		}
		else {	// means we reached a null node
			currentNode = nodeStack.top();	// get the node at the top of the stack, which is the leftmost node at the moment
			nodeStack.pop();

			currentNode = currentNode->rightChild;	// travel right
		}
	}

	return NULL;
}

template <typename T>
Node<T> BasicTree<T>::getNode_BFS(T data) {

}

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

	/* keep traveling left until we reach a null node, then pop from the stack and travel right (if possible) then travel left, repeat */
	while (!nodeStack.empty() || currentNode != NULL) {
		if (currentNode != NULL) {
			nodeStack.push(currentNode);
			currentNode = currentNode->leftChild;	// travel left
		} else {	// means we reached a null node
			currentNode = nodeStack.top();	// get the node at the top of the stack, which is the leftmost node at the moment
			cout << currentNode->data << " ";
			nodeStack.pop();

			currentNode = currentNode->rightChild;	// travel right
		}
	}

	delete currentNode;
}

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
void BasicTree<T>::printNode_DFS(T data) {

}

template <typename T>
void BasicTree<T>::printNode_BFS(T data) {

}


#endif