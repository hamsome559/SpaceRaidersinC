# simple programs level 2
# refactoring tic tac toe

# we can explore better practices and consider 
# that task 1 leans heavily on global data.

# Refactor task one in this file, following the strucutre and
# unit tests but passing the board structure into functions and return the 
# modified structure

# You may choose to work in a group and engage in discussion with staff on the topic

def create_board():
    return  [
    [' ', ' ' , ' '],
    [' ', ' ' , ' '],
    [' ', ' ' , ' '],
]      

# Function to print the game board
# You can choose how you wish to display this!
def print_board(board):
    print(board[0][0] + "|" + board[0][1] + "|" + board[0][2])
    print("-+-+-")
    print(board[1][0] + "|" + board[1][1] + "|" + board[1][2])
    print("-+-+-")
    print(board[2][0] + "|" + board[2][1] + "|" + board[2][2])



# Function to check if a player has won
# The current player should be provided as an argument
def check_win(board, player):
    #wins in the row section
    for r in range(3):
        if board[r][0] == board[r][1] == board[r][2] == player:
            return True
        
    #wins in the column section
    for c in range(3):
        if board[0][c] == board[1][c] == board[2][c] == player:
            return True

    #wins in diagonally
    if board[0][0] == board[1][1] == board[2][2] == player:
        return True
    if board[0][2] == board[1][1] == board[2][0] == player:
        return True
    return False        

# Function to check if the game is a draw
def check_draw(board):
    for row in board:
        for cell in row:
            if cell == ' ':
                return False
    return True

# a function that takes the current position
def check_valid_placement(board, placement_position):
    if not placement_position.isdigit():
        return False
    
    pos = int(placement_position)

    if pos < 1 or pos > 9:
        return False
    
    row = (pos - 1) // 3
    col = (pos - 1 ) % 3

    if board[row][col] == ' ':
        return True
    else:
        return False
# Main game loop
def play_game(board):

    # Set current player
    player = "X"
    turns = 0
    game_over = False

    # Loop the Game
    while not game_over:
        # print board
        print("\nCurrent board:")
        print_board(board)
        # get players placement (using input() function!)
        move = input(f"\nPlayer {player}, choose a position from 1 to 9: ")

        if not check_valid_placement(board, move):
            print("That was an incorrect move, try again!")
            continue

        # update board with move
        pos = int(move)
        row = (pos - 1) // 3
        col = (pos - 1 ) % 3
        board[row][col] = player
        turns += 1


        # check for win 
        if check_win(board,player):
            print("\nCurrent board:")
            print_board(board)
            print(f"\nPlayer {player} wins!")
            game_over = True       
        # check for draw   
        elif check_draw(board):
            print("\nCurrent board:")
            print_board(board)
            print("\nIt's a draw")
            game_over = True  
        # flip players
        else:
            player = "O" if player == "X" else "X"

if __name__ == '__main__':
    play_game(create_board())