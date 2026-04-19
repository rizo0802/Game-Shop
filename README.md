League of Legends Item Shop ⚔️
[cite_start]A C terminal application that simulates a MOBA item shop using data structures. [cite: 3, 18, 19]

Features
* [cite_start]Smart Crafting Logic: Automatically checks if you have the required components in your inventory, consumes them, and adds the completed item to your inventory. [cite: 37, 46, 52]
* [cite_start]Economy System: Farm randomized gold and automatically verify funds before purchasing components from the shop. [cite: 33, 36]
* [cite_start]Inventory Management: Seamlessly add bought components to your inventory or view your current stash at any time. [cite: 23, 24]
* [cite_start]Data Structure Architecture: Built using 3 preloaded binary trees for item recipes, a simple linked list for the inventory, and direct double pointer manipulation for safe data saving across the program. [cite: 4, 5, 16, 17]

How It Works
[cite_start]The program runs in an interactive loop where users navigate a main menu. [cite: 60, 74] Through the menu, you can:

* [cite_start]View the 3 available items to build (InfinityEdge, Thornmail, TitanicHydra) and their required components. [cite: 54, 55, 60]
* [cite_start]Manage your simple linked list inventory by purchasing from a selection of 8 base components. [cite: 4, 57]
* [cite_start]Farm gold to increase your current balance of 200 starting gold. [cite: 19, 36]
* [cite_start]Craft items, handled by an advanced function that safely matches list nodes to tree nodes and updates the list head using C double pointers. [cite: 10, 83, 86]

Getting Started
Prerequisites
* You will need a C compiler installed on your system (such as gcc).
