using System;
using System.Collections.Generic;
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

		// constructor for AVL_Tree
		public AVL_Tree() {
			Root = null;
			TreeHeight = 0;
		}

		// creates a node for the tree
		private TreeNode CreateTreeNode(int data) {
			TreeNode newNode = new TreeNode(data);
			return newNode;
		}

		// currently inserts in BST fashion
		public void Insert(int data) {
			if(Root == null) { 
				Root = CreateTreeNode(data);
				return;
			}

			TreeNode currNode = Root;
			TreeNode prevNode = null;
			int treeHeight = 0;

			while(currNode != null) {
				if(data < currNode.Data) {
					prevNode = currNode;
					currNode = currNode.Left;
					treeHeight++;
				} else {
					prevNode = currNode;
					currNode = currNode.Right;
					treeHeight++;
				}
			}

			if(data < prevNode.Data) {
				prevNode.Left = new TreeNode(data, prevNode.NodeDepth + 1);
				prevNode.Left.Parent = prevNode;
			} else {
				prevNode.Right = new TreeNode(data, prevNode.NodeDepth + 1);
				prevNode.Right.Parent = prevNode;
			}

			if (treeHeight > TreeHeight) TreeHeight = treeHeight;
		}

		private void PrintNode(TreeNode node) {
			Console.Write("[" + node.Data + "]");
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

		private String Indent(int paddingSize) {
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
				Console.Write(Indent(5 * (TreeHeight - currNode.NodeDepth)) + "[" + currNode.Data + "]");
			}
		}
	}
}
