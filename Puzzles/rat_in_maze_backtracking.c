
/*
  A Maze is given as N*N binary matrix of blocks where source block is the
  upper left most block i.e., maze[0][0] and destination block is lower
  rightmost block i.e., maze[N-1][N-1]. A rat starts from source and has to
  reach destination. The rat can move only in two directions: forward and
  down.  In the maze matrix, 0 means the block is dead end and 1 means the
  block can be used in the path from source to destination. Note that this is
  a simple version of the typical Maze problem. For example, a more complex
  version can be that the rat can move in 4 directions and a more complex
  version can be with limited number of moves.

*/

#include <stdbool.h>

// Maze size
#define N 4
 
 
/* A utility function to print solution matrix sol[N][N] */
static void printMaze(int sol[N][N], bool isSolution)
{
    int i, j;
    if (isSolution) {
        printf("This is the solition: \n");
    } else {
        printf("This is the rat maze: \n");
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}
 
/* A utility function to check if x,y is valid index for N*N maze */
static bool isSafe(int maze[N][N], int x, int y)
{
    // if (x,y outside maze) return false
    if(x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1)
        return true;
 
    return false;
}
 
 
/* A recursive utility function to solve Maze problem */
static bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
    // if (x,y is goal) return true
    if(x == N-1 && y == N-1)
    {
        sol[x][y] = 1;
        return true;
    }
 
    // Check if maze[x][y] is valid
    if(isSafe(maze, x, y) == true)
    {
        // mark x,y as part of solution path
        sol[x][y] = 1;
 
        /* Move forward in x direction */
        if (solveMazeUtil(maze, x+1, y, sol) == true)
            return true;
 
        /* If moving in x direction doesn't give solution then
           Move down in y direction  */
        if (solveMazeUtil(maze, x, y+1, sol) == true)
            return true;
 
        /* If none of the above movements work then BACKTRACK:
            unmark x,y as part of solution path */
        sol[x][y] = 0;
        return false;
    }  
 
    return false;
}

/* This function solves the Maze problem using Backtracking.  It mainly uses
solveMazeUtil() to solve the problem. It returns false if no path is possible,
otherwise return true and prints the path in the form of 1s. Please note that
there may be more than one solutions, this function prints one of the feasible
solutions.*/
static bool solveMaze(int maze[N][N])
{
    int sol[N][N] = { {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
 
    if(solveMazeUtil(maze, 0, 0, sol) == false)
    {
        printf("Solution doesn't exist");
        return false;
    }
 
    printMaze(sol, 1);
    return true;
}
 
// driver program to test above function
int main()
{
    int maze[N][N]  =  { {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    printMaze(maze, 0);
    solveMaze(maze);
    getchar();
    return 0;
}
