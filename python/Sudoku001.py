import numpy as np

#TODO: fix this - funny always the same results
#source: https://www.youtube.com/watch?v=G_UYXzGuqvM&list=RDCMUC9-y-6csu5WGm29I7JiwpnA&start_radio=1&rv=G_UYXzGuqvM&t=0


#input grid to be solved
grid = [[5,3,0,0,7,0,0,0,0],
        [6,0,0,1,9,5,0,0,0],
        [0,9,8,0,0,0,0,6,0],
        [8,0,0,0,6,0,0,0,3],
        [4,0,0,8,0,3,0,0,1],
        [7,0,0,0,2,0,0,0,6],
        [0,6,0,0,0,0,2,8,0],
        [0,0,0,4,1,9,0,0,5],
        [0,0,0,0,8,0,0,7,9]]

#print (">>>>> sudoku gride before solution ...")
#print (np.matrix(grid))

#function to check if we can put a number n in a
#grid position x,y - according to sudoku's rules
def possible(y,x,n):
    global grid
    
    if grid[y][x] != 0:
        return False #Already filled

    # check if # in line
    for i in range(0,9):
        if grid[y][i] == n:
            return False;
        
    # check if # in column columns
    for i in range(0,9):
        if grid[i][x] == n:
            return False;

    # floor division -> Returns the integral part of the quotient.
    # e.g.:
    #>>> 5.0 / 2
    #   2.5
    #>>> 5.0 // 2
    #   2.0

    # check if number allowed in the 3x3 sub-grid related to x, y
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
            #print("!!!solving for: y=",y," x=",x)
            
            #checking empty positions in the grid
            if grid[y][x] == 0:
                #try to put a number values: 1 to 9
                for n in range(1,10):
                    #print("!!! n=",n)
                   
                    if possible(y,x,n):
                        #try to add n in this position
                        grid[y][x] = n

                        #continue trying to add mor numbers
                        #solving for a smaller set of the problem
                        if solve():
                            return True

                        #backtracking - we
                        # try via grid[y][x] = n , then
                        # if i does not work, we remove it
                        # backtrack - via grid[y][x] = 0
                        # to make the position free again
                        #take number off - it was a bad choice
                        grid[y][x] = 0
                return False #could not find a solution
    return True
    
    
def main():
    while(1):
        print("Solving sudoku - starting ...")
        print()
        print (">>>>> sudoku gride before solution ...")
        print (np.matrix(grid))
        solve()    
        print()
        print (">>>>> sudoku gride AFTER solution ...")
        print (np.matrix(grid))
        again = input ("More(Y/N)?")    
        if (again != 'Y' and again !='y' ):
            return

if __name__ == "__main__":
    main()
    

    
    
