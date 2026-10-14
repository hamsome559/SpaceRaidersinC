# IN CLASS TEST 2 PART 3 [of 3]

# This section involves writing some challenging functions. 
# These questions are considered beyond first class and 
# should only be attempted if parts 1 and 2 are done
# --------------------------------------------------------------------------------
# The Game of Life, a cellular automaton, is implemented by initializing a two-dimensional grid of 
# boolean values representing cell states (alive or dead). 
# The grid is updated iteratively according to 4 simple rules:
# - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
# - Any live cell with two or three live neighbours lives on to the next generation.
# - Any live cell with more than three live neighbours dies, as if by overpopulation.
# - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
# Important note: In all of the following questions the game of life should be represented by a 2D list of boolean values. 

# Implement a single function that is given as an argument a 2D list of booleans
# representing cells and returns the next generation of cells as a 2d list of booleans 
# completing one generation of Conway's game of life.
def update_gol(cells):
    pass

# --------------------------------------------------------------------------------
# In a system that implements game of life, we want to be able to easily control the initial state of the cells, 
# to allow game of life to run from this starting state.
# We can imagine a small configuration language for populating the intial state of the 2D list that supports different syntax for different uses.
# develop the parse_start_coords() function to accept a multiline string and return a 2d list of the provided dimesions with the following features:
# Coordinates: Space seperated intergers representing the coordinate for a living cell
# example input:
"""
0 0
1 0
100 10
100 11
100 12
"""
# you should handle excess white space and new lines gracefully (without stopping exectution)
# lines starting with two slashes ie. // should be considered comments and coords on that line shoudl be ignored
# note you should handle your own exceptions if you use them, uncaught exceptions will stop execution!

# The function takes a multiline string as input and a tuple representing the x and y dimensions of a grid
def parse_start_coords(start_grid_string, xy_size):
    pass
# --------------------------------------------------------------------------------
# Alternatively we may want to be able to easily insert predefined cell patterns at relative positions.
# this is often done with a syntax as follows:
# a "." is used to represent a dead cell, while an "O" (capital o) is used to represent an alive cell.
# a line may have an uneven number of characters and in the absence of a character a dead cell is placed
# for example the following string represents a simple glider:
"""
.O.
..O
OOO
"""
# Implement parse_start_pattern such that it returns a grid of the given dimensions 
# populated according to the pattern provided and the position it should be inserted at
# The function takes a multiline string as input, 
# a tuple representing the x and y dimensions of a grid 
# and a tuple for the position that the pattern should be placed (representing the top left)
def parse_start_pattern(start_grid_string, xy_size, xy_position):
    pass