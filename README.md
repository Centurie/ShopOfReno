Roscoe's Potion Emporium
A CLI shop management system written in modern C++. Players enter the emporium with randomized starting gold, browse compile-time configured shop inventories, purchase items with strict input validation, and review acquired inventory upon exiting.

What the Project Does
Roscoe's Potion Emporium models a text-based economic exchange loop. 
Upon startup, the engine registers player state, dynamically assigns starting capital, displays current shop stock, validates terminal input streams against trailing buffer noise, processes transactions, and prints final player inventory contents.

Prerequisites
A C++17 compliant compiler (GCC 8+, Clang 7+, or MSVC 2019+)

CMake 3.14+ (optional) or direct command-line invocation
