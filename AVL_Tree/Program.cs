using System;
using System.Reflection.Metadata.Ecma335;

namespace AVL_Tree {
	class Program {
		static void Main(string[] args) {
			Menu();
		}

		static void MenuOptions() {
			Console.WriteLine("------------------MENU------------------");
			Console.WriteLine("0 - insert");
			Console.WriteLine("1 - continually insert into tree");
			Console.WriteLine("2 - remove");
			Console.WriteLine("3 - tree height");
			Console.WriteLine("4 - print tree (DFS)");
			Console.WriteLine("5 - quit");
			Console.WriteLine();
		}
		
		static void Menu() {
			MenuOptions();
			Console.Write("choice: ");
			int choice = Convert.ToInt32(Console.ReadLine());
			int num;
			bool inserted;
			AVL_Tree avl = new AVL_Tree();

			while(choice != 5) {
				switch(choice) {
					// insert into tree
					case 0:   
						Console.Write("number to insert: ");
						num = Convert.ToInt32(Console.ReadLine());
						inserted = avl.Insert(num);
						if (inserted) {
							Console.WriteLine(num + " has been inserted...\n");
						} else {
							Console.WriteLine(num + " was not inserted (already in the tree)\n");
						}

						avl.Print2D();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					// continually insert into the tree
					case 1:	
						bool running = true;
						while (running)
						{
							Console.WriteLine("[q] to quit");
							Console.Write("number to insert: ");
							string input = Console.ReadLine();
							if (input.Equals("q")) {
								running = false;
							} else {
								int number = Convert.ToInt32(input);

								inserted = avl.Insert(number);
								if (inserted) {
									Console.WriteLine(number + " has been inserted...\n");
								} else {
									Console.WriteLine(number + " was not inserted (already in the tree)\n");
								}

								avl.Print2D();
								Console.WriteLine();
							}
						}

						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					// delete an item from the tree
					case 2:   
						Console.Write("number to remove: ");
						num = Convert.ToInt32(Console.ReadLine());

						bool removed = avl.Remove(num);
						if (removed) {
							Console.WriteLine(num + " has been removed...\n");
						}
						else {
							Console.WriteLine(num + " was not removed\n");
						}

						avl.Print2D();
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					case 3:
						Console.WriteLine("tree height: " + avl.TreeHeight);
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					// print tree DFS
					case 4:
						Console.WriteLine("printing tree...");
						avl.PrintTree();
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					// invalid choice
					default:
						MenuOptions();
						Console.Write("Please select a valid option between 0-5: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
				}
			}
		}
	}
}
