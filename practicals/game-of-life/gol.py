import os
from PIL import Image, ImageSequence
# Conway’s Game of Life

# A GameOfLife class with methods for each of the four rules:
# underpopulation(rule): Applies the underpopulation rule to a cell.
# overpopulation(rule): Applies the overpopulation rule to a cell.
# reproduction(rule): Applies the reproduction rule to a cell.
# stasis(rule): Applies the stasis rule to a cell.

class GameOfLife:
    def __init__(self, frames, x, y):
        # create a 3d list with given dimensions and frame length
        # it is made up of boolean values to indicate either a living or dead cell
        self.data = [[[False for _ in range(x)] for _ in range(y)] for _ in range(frames)]

    def get_previous_cell(self, current_frame, x, y):
        # get the value of a cell from a previous frame
        pass
        
    def get_prev_neighbours(self, x, y):
        # use get_previous_cell to get the number of neighbours for a cell from the previous frame
        pass

    def underpopulation(self,  x, y):
        # Any live cell with fewer than two live neighbours dies (underpopulation)
        pass

    def overpopulation(self, x, y):
        # Any live cell with more than three live neighbours dies (overpopulation)
        pass

    def reproduction(self, x, y):
        # Any dead cell with exactly three live neighbours becomes a live cell (reproduction)
        pass

    def stasis(self, x, y):
        # Any live cell with two or three live neighbours lives on to the next generation
        pass
    
    def evolve(self):
        # for frames 
        #     for x 
        #         for y
        #             rule_one x y
        #             rule_two x y
        #             rule_three x y
        #             rule_four x y
        pass


    def set_start_grid(self, file_name, size_x, size_y):
        """
        Reads a space-delimited file, parses the positions, and sets the corresponding positions in a 3D list to True.
        for example, we can draw a glider in the middle of 100x100 grid with the following postitions 
        48 51
        49 52
        50 50
        50 51
        50 52

        Args:
            file_name (str): Name of the file to read from.
            size_x (int): Size of the 3D list in the x dimension.
            size_y (int): Size of the 3D list in the y dimension.
        """
        # Read the file and parse the positions
        with open(file_name, 'r') as file:
            for line in file:
                # Split the line into space-delimited values
                x, y = map(int, line.split())

                # Check if the position is within the bounds of the 3D list
                if 0 <= x < size_x and 0 <= y < size_y:
                    # Set the position to True
                    self.data[0][x][y] = True

    def generate_gif(self, filename, frame_duration):
        # Assuming your 3D list is named 'data' with shape (frames, rows, cols)
        frames, rows, cols = len(self.data), len(self.data[0]), len(self.data[0][0])

        # Convert 3D list to a sequence of 2D arrays (images)
        images = []
        for f, frame in enumerate(self.data):
            img = Image.new('RGB', (cols, rows))  # Create a new image
            for i, row in enumerate(frame):
                for j, col in enumerate(row):
                    if self.data[f][i][j]:
                        img.putpixel((j, i), (255,255,255))
                    else:
                        img.putpixel((j, i), 0)
            images.append(img)

        frame_one = images[0]
        frame_one.save(f"{filename}.gif", format="GIF", append_images=images,
                    save_all=True, duration=frame_duration, loop=0)

if __name__ == '__main__':
    f, x, y = 100, 100,100
    game = GameOfLife(f, x, y)
    game.set_start_grid('initial_grid.txt', x, y)
    game.evolve()
    game.generate_gif('game_of_life', 2000)

