# suduku
Command-line application, and graphic user interface optionally, allowing to represent and solve sudokus. Group work as part of the course named "GLIN405 - Projet Informatique", taught under license 2 Computer Science at the Faculty of Science of the University of Montpellier.

This program runs on UNIX systems (Linux, Mac OS) and Windows. It allows to generate 4 * 4, 9 * 9 and 16 * 16 size sudokus, to recover grids and to play with these same grids or to solve them.

### CONCEPTS
  - Heuristics to remove impossible solutions (under grids).

    * Cross-hatching

    * Lone-number

    * N-possible or Naked subset
  
  - Back-tracking to solve the grids

  - C programming concepts 
  
    * dynamic memory allocation and pointer pointers,
    * IO and files manipulation
    * Algorithmic data structures
    * targeted typing ...

### CODE RUNNING
- Compilation :

The sudoku can be played on console, via the terminal.

        gcc sudoku.c functions.c -lm -ansi -pedantic -Wall -O3 -std = c99 -o sudoku.
- run

        ./sudoku.

The terminal is then emptied, in order to mask the compilation commands.

The user then has the choice between these options:
1. Start a game
2. Load a game
3. Top10
4. Recover a grid
5. Exit

He must enter the number corresponding to his choice.

If he decides to quit, the execution of the application ends.

Otherwise, if he decides to start a new game, load a game
previously saved, access to the top 10 or retrieve a grid,
has access to a new menu.
He is then asked what level of difficulty he wants to
all cases. The level of difficulty naively corresponds to the size of the
(4 * 4, 9 * 9 or 16 * 16).

The top 10 is displayed in case of choice 3.

The name of the file where the grid is to be retrieved is requested in the case
of the choice 4. If this file exists and corresponds to the grid size chosen, the recovered grid is displayed and the user is prompted to resolve it. if
accepts, the solution appears, otherwise it can play with this grid.

In the other two choices, the game grid is then generated (in the case
of a new part) or recovered (in the case of a load).
The user then has access to a new menu (called by
convenience menu 2) with the following options:

1. Playing
2. Help
3. Verification
4. Backup
5. Loading
6. Resetting
7. New Part
8. Top10
9. Recover a grid
10. Exit

He must enter the number corresponding to his choice.

If he decides to quit, the execution of the application ends.

If he decides to play, he can change the value of a box by entering
the number of the row, the number of the column of the box concerned, then its new value. If the box is modifiable, the grid will be displayed with the new value and then the menu item is re-entered from menu 2.

If he decides to call for help, he can choose the box on which he
wishes to display the list of possible values ​​by entering the number of the line then the column number of the box concerned. The help is displayed, and then repeats the selection from menu 2.

If he decides to verify its resolution, it only has to choose the corresponding option. If he has found the solution, he will be given the opportunity to leave the application (by typing 'o' to exit, 'n' to stay).

If he chooses to stay, the choice is reiterated from menu 2.
If it decides to save, the current grid is saved and then
the choice from menu 2.

If he decides to charge a party, he is asked to choose a level of
and the corresponding pre-saved grid is loaded. It is displayed, then the menu is repeated from menu 2.

If he decides to reset the game, the current grid is reset to its current original state, to the generation of the game grid.

If he decides to start a new game, he is referred to the choice of the
then the new game grid is displayed and the menu item is reiterated.

If he decides to access the top10 or retrieve a grid, the sequence
of the following operations is analogous to the corresponding operations in the first menu.

### AUTHOR

Abdoulaye Diallo (abdouldiallo30@yahoo.fr)

Redoine El Ouasti

Simon Galand

Adrien Lamant

Pierre-Louis Latour

Charly Maeder

Pierre Ruffin

Stella Zevio

### TEACHER (s) 
Mr Meynard

### DATE
26 march 2014
