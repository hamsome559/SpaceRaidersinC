# IN CLASS TEST 2 PART 2 [of 3]
# Note: you should NOT use input() or print() (other than for your own debugging purposes)
# Use the functions arguments as input and return values as output

# This section involves writing some more substantial functions focusing on grades from 2:2 -> 2:1 
# First class is possible by completing only part 1 and 2 but requires high accuracy
# --------------------------------------------------------------------------------

# --------------------------------------------------------------------------------
# implement a function that takes a string as an argument and returns the number of vowels in the string.
# it should count both upper and lower case values
# you can assume input will always be a string
def count_vowels(s):
    i = 0
    for char in s:
        if char in "aeiouAEIOU":
            i = i + 1
    return i


# --------------------------------------------------------------------------------
# implement a function that takes a list of numbers and returns the largest value in that list
# you can assume input will always be a list of numbers
def largest_found(lst):
    largest = lst[0]
    for number in lst:
        if number > largest:
            largest = number
    return largest

# --------------------------------------------------------------------------------
# implement a function that takes a 2D list of strings and a string to search for.
# The function should return a tuple of the string it found and the number of times it found it (number first then string). 
# If nothing is found it should still return the string that it searched for and indicate that it was found 0 times in the tuple.
# you can assume input will always be a list of strings but target may also be a number.
# If a number is provided for target you should search for the string representation of that number in the list of strings.
def find(lst, target):
    target = str(target)
    count = 0
    for row in lst:
        count += row.count(target)
    return (count , target)

# --------------------------------------------------------------------------------
# write a function that given a 2d array of strings (representing a tic tac toe board), checks to see if a player won
# The function should return 'x' or 'o' for a respective winner, 'tie' if there is no win possible 
# and '' (empty string) if there is no winner but play can still continue
# (the grid argument is a 2d list where 'x' and 'o' are used to represent player moves and available spaces are ' ')
# Bonus: for additional marks your function should also work where empty spaces in the grid are represented by numbers 1-9 not just an empty space
def check_win(grid):
    #wins in row
    for r in range(3):
        if grid[r][0] == grid[r][1] == grid[r][2] and grid[r][0] != ' ':
            return grid[r][0]

    #wins in column
    for c in range(3):
        if grid[0][c] == grid[1][c] == grid[2][c] and grid[0][c] != ' ':
            return grid[0][c]
    
    #wins in diagonal
    if grid[0][0] == grid[1][1] == grid[2][2] and grid[0][0] != ' ':
        return grid[0][0]
    
    if grid[0][2] == grid[1][1] == grid[2][0] and grid[0][2] != ' ':
        return grid[0][2]

    #check gaps or draw
    for cell in grid:
        if ' ' in cell:
            return ''
    return 'tie'