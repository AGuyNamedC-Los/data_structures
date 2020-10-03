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
			Console.WriteLine("1 - print tree (DFS)");
			Console.WriteLine("2 - tree height");
			Console.WriteLine("3 - print pretty tree");
			Console.WriteLine("4 - continually insert into tree");
			Console.WriteLine("5 - quit");
			Console.WriteLine();
		}
		
		static void Menu() {
			MenuOptions();
			Console.Write("choice: ");
			int choice = Convert.ToInt32(Console.ReadLine());
			int num;
			AVL_Tree avl = new AVL_Tree();

			while(choice != 5) {
				switch(choice) {
					case 0:   // insert into tree
						Console.Write("number to insert: ");
						num = Convert.ToInt32(Console.ReadLine());
						avl.Insert(num);
						Console.WriteLine(num + " has been inserted...");
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					case 1:   // print tree DFS
						Console.WriteLine("printing tree...");
						avl.PrintTree();
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;

					case 2:
						Console.WriteLine("tree height: " + avl.TreeHeight);
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					case 3:
						Console.WriteLine("printing pretty tree...");
						avl.PrintPrettyTree();
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					case 4:
						bool running= true;
						while (running) {
							Console.WriteLine("[q] to quit");
							Console.Write("number to insert: ");
							string input = Console.ReadLine();
							if (input.Equals("q")) {
								running = false;
							} else {
								int number = Convert.ToInt32(input);
								avl.Insert(number);
								avl.Print2D();
								Console.WriteLine();
							}
						}
						Console.WriteLine();
						MenuOptions();
						Console.Write("choice: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
					default:	// invalid choice
						MenuOptions();
						Console.Write("Please select a valid option between 0-5: ");
						choice = Convert.ToInt32(Console.ReadLine());
						break;
				}

			}
		}
	}
}
