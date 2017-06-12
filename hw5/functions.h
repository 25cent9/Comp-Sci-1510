/*
  Name: Innocent Niyibizi
  File: functions.h
  Section:  B
  Instructor: Taylor
  Date: 3-29-17
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//Constant short array for cardinal directions
const short DIRECTIONS[4][2]={{-1,0},{1,0},{0,1},{0,-1}};

/*
  Description: Fucntion that will print the given map
  Pre:         grid must not be a NULL pointer
  Post:        The given grid will printed with the passed rows and cols
*/
void printGrind(char** grid, const int rows, const int cols);

/*
  Description: Fucntion that will deallocate memory for a given dynamic array
  Pre:         None
  Post:        Dynamic array will be deallocated of memory
*/
void deallocate(char **grid, const int rows);

/*
  Description: Recursive function to solve the maze
  Pre:         grid must not be NULL, x and y must be a valid location
  Post:        True is returned if an exit is reached, else a false is returned
*/
bool solve(char* grid[], int x, int y);

#endif
