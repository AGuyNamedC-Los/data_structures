using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Text;
using System.Xml;

namespace AVL_Tree {
	class AVL_Tree {
		// class that creates a tree node
		class TreeNode
		{
			public int Data { get; set; }
			public TreeNode Left { get; set; }
			public TreeNode Right { get; set; }
			public int BF { get; set; }   // balance factor BF(node) = Height(right subtree) - Height(left subtree)
			public int NodeDepth { get; set; }
			public int NodeHeight { get; set; }


			// constructor for TreeNode
			public TreeNode(int _data) {
				Data = _data;
				BF = 0;
				NodeDepth = 0;
				NodeHeight = 0;
			}
		}

		private TreeNode Root { get; set; }
		public int TreeHeight { get; set; }
		private readonly int COUNT = 10;

		// constructor for AVL_Tree
		public AVL_Tree() {
			Root = null;
			TreeHeight = 0;
		}

		// ensures no duplicate values are inserted before inserting recursively into the tree
		public bool Insert(int data) {
			if (Root == null) { 
				Root = new TreeNode(data); 
				return true; 
			}

			bool duplicateVal = findNode(Root, data);

			// ensure no duplicate values are accepted
			if (!duplicateVal) {
				TreeNode newNode = new TreeNode(data);
				Root = Insert(Root, newNode);
				return true;
			}

			return false;
		}

		// insert into the tree recursively
		private TreeNode Insert(TreeNode currentNode, TreeNode newNode) {
			if (currentNode == null) {
				currentNode = newNode;
				return currentNode;
			}

			if (newNode.Data < currentNode.Data) { 
				currentNode.Left = Insert(currentNode.Left, newNode); 
			} else { 
				currentNode.Right = Insert(currentNode.Right, newNode); 
			}

			UpdateNode(currentNode);
			return Balance(currentNode);
		}

		// updates a node's height value
		private void UpdateNode(TreeNode node) {
			int leftNodeHeight = (node.Left == null) ? -1 : node.Left.NodeHeight;
			int rightNodeHeight = (node.Right == null) ? -1 : node.Right.NodeHeight;

			node.NodeHeight = 1 + Math.Max(leftNodeHeight, rightNodeHeight);
			node.BF = rightNodeHeight - leftNodeHeight;
		}

		// will rotate the nodes accordingly to adhear to AVL tree balancing
		private TreeNode Balance(TreeNode currNode) {
			// left heavy sub-tree
			if (currNode.BF <= -2) {
				if (currNode.Left.BF <= 0) { 
					return LeftLeftCase(currNode); 
				} else { 
					return LeftRightCase(currNode);
				}
			// right heavy sub-tree
			} else if (currNode.BF >= 2) {
				if (currNode.Right.BF >= 0) { 
					return RightRightCase(currNode); 
				} else {
					return RightLeftCase(currNode); 
				}
			}

			return currNode;
		}

		// rotates nodes to the left from a given node
		private TreeNode LeftRotation(TreeNode node) {
			TreeNode newParent = node.Right;
			node.Right = newParent.Left;
			newParent.Left = node;

			UpdateNode(node);
			UpdateNode(newParent);
			return newParent;
		}

		// rotates nodes to the right from a given node
		private TreeNode RightRotation(TreeNode node) {
			TreeNode newParent = node.Left;
			node.Left = newParent.Right;
			newParent.Right = node;

			UpdateNode(node);
			UpdateNode(newParent);
			return newParent;
		}

		/*
		       A
		      /
		     B	=>   B
		    /         / \
		   C         C   A
		*/

		private TreeNode LeftLeftCase(TreeNode node) {
			return RightRotation(node);
		}

		/* 
		  	A		  A
		    /	      /
		   B		=>   C	=>   C
		    \         /         / \
		     C	   B         B   A
		*/
		private TreeNode LeftRightCase(TreeNode node) {
			node.Left = LeftRotation(node.Left);	// this will turn it into a left left case
			return LeftLeftCase(node);
		}

		/* 
		   A
		    \
		     B	 =>   B
		      \		/ \
		       C      A   C
		*/
		private TreeNode RightRightCase(TreeNode node) {
			return LeftRotation(node);
		}

		/*   
		   A         A
		    \         \
		     B	=>   C	=>   C
		    /           \       / \
		   C             B     A   B
		*/
		private TreeNode RightLeftCase(TreeNode node) {
			node.Right = RightRotation(node.Right);	// this will turn it into a right right case
			return RightRightCase(node);
		}

		public bool Remove(int data) {
			if (Root == null) { return false; }

			bool nodeExists = findNode(Root, data);

			// ensure no duplicate values are accepted
			if (nodeExists) {
				Root = Remove(Root, data);
				return true;
			}

			return false;
		}

		private TreeNode Remove(TreeNode node, int data) { 
			if(node == null) { return null; }

			if (data < node.Data) {
				node.Left = Remove(node.Left, data);
			} else if (data > node.Data) {
				node.Right = Remove(node.Right, data);
			// node found, check which one of the four removal situations is usable
			} else { 
				// node has no left sub tree so just replace this node with it's right child
				if (node.Left == null) {
					return node.Right;

				// node has no left sub tree so just replace this node with it's right child
				} else if (node.Right == null) {
					return node.Left;

				// node has both a left and right subtree
				// remove the child that has the greatest height between both node's children
				} else {
					// remove the highest value from the left subtree 
					if (node.Left.NodeHeight > node.Right.NodeHeight) {
						int successorVal = GetHighestValue(node.Left);
						node.Data = successorVal;


						// now we must delete the succesor node we found from using GetHighestValue by calling the Remove function once again...
						// we are guarenteed to either use the case of this node having one left child or no children
						// which is handled by one of the if satements above
						node.Left = Remove(node.Left, successorVal);

					// remove the lowest value from the right subtree 
					} else {
						int succesorVal = GetLowestValue(node.Right);	 // get lowest value from the right subtree
						node.Data = succesorVal; // replace the current node's value with the lowest value from the right sub tree


						// now we must delete the succesor node we found from using GetLowestValue by calling the Remove function once again...
						// we are guarenteed to either use the case of this node having one right child or no children
						// which is handled by one of the if satements above
						node.Right = Remove(node.Right, succesorVal);
					}
					
				}
			}

			return node;
		}

		public int GetLowestvalue() {
			return GetLowestValue(Root);
		}

		// travel as far down left as possible to find lowest value in the tree
		private int GetLowestValue(TreeNode node) {
			while (node != null) { node = node.Left; }
			return node.Data;
		}

		public int GetHighestValue() {
			return GetHighestValue(Root);
		}

		// travel as far down right as possible to find greatest value in the tree
		private int GetHighestValue(TreeNode node) {
			while (node != null) { node = node.Right; }
			return node.Data;
		}

		public bool findNode(int data) {
			return findNode(Root, data);
		}

		private bool findNode(TreeNode node, int data) {
			while (node != null) {
				if (data < node.Data) {
					node = node.Left;
				} else if (data > node.Data) {
					node = node.Right;
				} else {
					return true;
				}
			}

			return false;
		}

		public void DeleteTree() {
			Root = null;
		}

		public void PrintTree() {
			PrintTree(Root);
		}

		// prints tree DFS
		private void PrintTree(TreeNode node) {
			if (node != null) {
				Console.Write(node.Data + ", ");
				if (node.Left != null) PrintTree(node.Left);
				if (node.Right != null) PrintTree(node.Right);
			}
		}

		private string Indent(int paddingSize) {
			return "".PadRight(paddingSize);
		}

		public void PrintPrettyTree() {
			PrintPrettyTree(Root);
		}

		private void PrintPrettyTree(TreeNode root) {
			if(root == null) { return; }

			Queue<TreeNode> treeNodes = new Queue<TreeNode>();
			treeNodes.Enqueue(root);
			TreeNode currNode;
			int currTreeDepth = 0;

			while(treeNodes.Count != 0) {
				currNode = treeNodes.Dequeue();
				if(currNode.Left != null) { treeNodes.Enqueue(currNode.Left); } 
				if(currNode.Right != null) { treeNodes.Enqueue(currNode.Right); }

				if(currNode.NodeDepth > currTreeDepth) {
					currTreeDepth = currNode.NodeDepth;
					Console.WriteLine();
				}
				Console.Write(Indent(15 * (TreeHeight - currNode.NodeDepth)) + "D:[" + currNode.NodeDepth + "] H:[" +currNode.NodeHeight + "] BF:[" + currNode.BF + "] N:[" + currNode.Data + "]");
			}
		}

		public void Print2D() {
			Print2D(Root, 0);
		}

		private void Print2D(TreeNode root, int space) {
			// Base case  
			if (root == null) { return; }

			// Increase distance between levels  
			space += COUNT;

			// Process right child first  
			Print2D(root.Right, space);

			// Print current node after space count  
			Console.Write("\n");
			for (int i = COUNT; i < space; i++) { Console.Write(" "); }
			Console.Write("[" + root.Data + "]" + "\n");

			// Process left child  
			Print2D(root.Left, space);
		}
	}
}
