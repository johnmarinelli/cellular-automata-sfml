#Cellular Automata
![alt-text](http://natureofcode.com/book/imgs/chapter07/ch07_12.png)
From [Wikipedia](http://en.wikipedia.org/wiki/Cellular_automaton): *A cellular automaton is a discrete model studied in computability theory, mathematics, physics, complexity science, theoretical biology and microstructure modeling*

**Less boring version**
Cellular automata are really sweet models that make really sweet patterns.  They were first studied in the 1940s for watching the growth of crystals, and now we use them as a theoretical device for modelling all kinds of nifty things from the economy, to population growth, to life itself.  Personally, I just like how they look.

Imagine a 2-dimensional grid.  In a cellular automata model, each cell has a finite state that is affected by its neighbors.  We have rules that determine how a cells' neighbors will affect it, and the whole model starts off with a predetermined seed.  

#Structure of the program
##Dependencies
- SFML 2.1
- cmake

##Installation
First, clone the repo.  Then find and move your FindSFML.cmake (should be in <SFML directory>/cmake/Modules) into the build directory.  

##Usage
You should now have a 'CA' file in your build directory.  To use the program, type into the command line:

```
./CA Rules/<Your-Rule-File.txt> Seed/<Your-Seed-File.txt>
```

For example (out of the box:)
```
./CA Rules/Conway.txt Seed/Conway/R-Pentomino.txt
```

##Writing your own Rules and Seeds
###Rules:
First line will be the neighborhood type (Moore is a 3x3, Von Neumann is 3x3 with no diagonals).
Second line is the number of rows.
From here, you'll have either specific rules or totalistic rules.  Specific rules are formatted like this: 
```
01010
/rule
```
This says that any cell with its left and right neighbors alive will be alive.

Totalistic rules are rules that just count the number of alive or dead neighbors, and they're formatted as such:
```
CELLALIVE
<3:DEAD
/CELLALIVE
```
This says that if the cell is alive, and if three of its neighbors are alive, the cell will be dead.

There are formatting instructions in the build/Rules directory.
