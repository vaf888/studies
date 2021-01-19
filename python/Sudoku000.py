import numpy as np

grid = [[5,3,0,0,7,0,0,0,0],
        [6,0,0,1,9,5,0,0,0],
        [0,9,8,0,0,0,0,6,0],
        [8,0,0,0,6,0,0,0,3],
        [4,0,0,8,0,3,0,0,1],
        [7,0,0,0,2,0,0,0,6],
        [0,6,0,0,0,0,2,8,0],
        [0,0,0,4,1,9,0,0,5],
        [0,0,0,0,8,0,0,7,9]]

print (">>>>> sudoku gride before solution ...")
print (np.matrix(grid))

#function to define if in a certain position
#we can put a number
def possible(y,x,n):
    global grid

    # check lines
    for i in range(0,9):
        if grid[y][i] == n:
            return False;
        
    # check columns
    for i in range(0,9):
        if grid[i][x] == n:
            return False;

    # floor division -> Returns the integral part of the quotient.
    # e.g.:
    #>>> 5.0 / 2
    #   2.5
    #>>> 5.0 // 2
    #   2.0

    # check if number allowed in each one of 3x3 matrix
    x0 = (x//3)*3
    y0 = (y//3)*3
    for i in range(0,3):
        for j in range(0,3):
            if grid[y0+i][x0+i] == n:
                return False

    # ok, number n can be added at position y,x
    return True
    
#solve the game
def solve():
    global grid
    for y in range(9):
        for x in range(9):
            print("!!!solving for: y=",y," x=",x)
            
            #checking empty positions in the grid
            if grid[y][x] == 0:
                #try to put a number values: 1 to 9
                for n in range(1,10):
                    print("!!! n=",n)
                   
                    if possible(y,x,n):
                        #try to add n in this position
                        grid[y][x] = n

                        #continue trying to add mor numbers
                        #solving for a smaller set of the problem
                        solve()

                        #this is the backtracking - we
                        # try via grid[y][x] = n , then
                        # if i does not work, we remove it
                        # backtrack - via grid[y][x] = 0
                        # to make the position free again
                        #take number off - it was a bad choice
                        grid[y][x] = 0
                        
    print (">>>>> sudoku gride AFTER solution ...")
    print (np.matrix(grid))
    input ("More?")
    
    
