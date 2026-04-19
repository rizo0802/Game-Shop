League of Legends Item Shop ⚔️
A C terminal application that simulates a MOBA item shop using data structures.

Features
* Smart Crafting Logic: Automatically checks if you have the required components in your inventory, consumes them, and adds the completed item to your inventory.
* Economy System: Farm randomized gold and automatically verify funds before purchasing components from the shop.
* Inventory Management: Seamlessly add bought components to your inventory or view your current stash at any time. 
* Data Structure Architecture: Built using 3 preloaded binary trees for item recipes, a simple linked list for the inventory, and direct double pointer manipulation for safe data saving across the program. 

How It Works
The program runs in an interactive loop where users navigate a main menu. Through the menu, you can:

* ]View the 3 available items to build (InfinityEdge, Thornmail, TitanicHydra) and their required components. 
* Manage your simple linked list inventory by purchasing from a selection of 8 base components.
* Farm gold to increase your current balance of 200 starting gold.
* Craft items, handled by an advanced function that safely matches list nodes to tree nodes and updates the list head using C double pointers.

Getting Started
Prerequisites
* You will need a C compiler installed on your system (such as gcc).
