using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace AVL_Tree {
	class AVL_Tree {
		// class that creates a tree node
		class TreeNode
		{
			public int Data { get; set; }	// data each node will hold
			public TreeNode Parent { get; set; }
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

			public TreeNode(int _data, int _nodeDepth) {
				Data = _data;
				BF = 0;
				NodeDepth = _nodeDepth;
				NodeHeight = 0;
			}
		}

		private TreeNode Root { get; set; }
		public int TreeHeight { get; set; }
		private int COUNT = 10;

		// constructor for AVL_Tree
		public AVL_Tree() {
			Root = null;
			TreeHeight = 0;
		}

		public void Insert(int data) {
			if (Root == null) { 
				Root = new TreeNode(data); 
				return; 
			}

			TreeNode newNode = new TreeNode(data);
			Root = Insert(Root, newNode);
		}

		private TreeNode Insert(TreeNode currentNode, TreeNode newNode) {
			if (currentNode == null) {
				currentNode = newNode;
				return currentNode;
			}

			if (newNode.Data < currentNode.Data) { currentNode.Left = Insert(currentNode.Left, newNode); }
			else { currentNode.Right = Insert(currentNode.Right, newNode); }

			UpdateNode(currentNode);
			Balance(currentNode);
			return currentNode;
		}

		// will travel upwards from a given node and properly update heights and balance factor of each node visited
		private void UpdateNode(TreeNode node) {
			int leftNodeHeight = (node.Left == null) ? -1 : node.Left.NodeHeight;
			int rightNodeHeight = (node.Right == null) ? -1 : node.Right.NodeHeight;

			node.NodeHeight = 1 + Math.Max(leftNodeHeight, rightNodeHeight);
			node.BF = rightNodeHeight - leftNodeHeight;
		}

		private void Balance(TreeNode currNode) {
			// left heavy sub-tree
			if (currNode.BF <= -2) {
				if (currNode.Left.BF <= 0) {
					Console.Write("left left case: ");
					Console.Write("BF:[" + currNode.BF + "][" + currNode.Data + "]" + "\n");
					RightRotation(currNode);
				}
				else {
					Console.Write("left right case: ");
					Console.Write("BF:[" + currNode.BF + "][" + currNode.Data + "]" + "\n");
				}
				// right heavy sub-tree
			}
			else if (currNode.BF >= 2) {
				if (currNode.Right.BF >= 0) {
					Console.Write("right right case: ");
					Console.Write("BF:[" + currNode.BF + "][" + currNode.Data + "]" + "\n");

				}
				else {
					Console.Write("right left case: ");
					Console.Write("BF:[" + currNode.BF + "][" + currNode.Data + "]" + "\n");
				}
			}
		}

		// for public interface
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
			Console.Write("BF:[" + root.BF + "][" + root.Data + "]" + "\n");

			// Process left child  
			Print2D(root.Left, space);
		}

		private void LeftRotation(TreeNode node_A) {

		}

		private void RightRotation(TreeNode node_A) {

		}

		private void LeftLeftCase(TreeNode node) {
			RightRotation(node);
		}

		private void RightRightCase(TreeNode node) {
			LeftRotation(node);
		}
	}
}
