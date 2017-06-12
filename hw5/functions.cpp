/*
  Name: Innocent Niyibizi
  File: functions.cpp
  Section:  B
  Instructor: Taylor
  Date: 3-29-17
*/

#include "functions.h"
#include <iostream>
using namespace std;
void printGrind(char** grid, const int rows, const int cols)
{
  for(int i =0; i<rows; i++)
  {
    for(int j =0; j<cols; j++)
      cout<<grid[i][j];
    cout<<endl;
  }
  return;
}

void deallocate(char **grid, const int rows)
{
  //Loop to run and deallocate the memory needed for the arrays at each pointer
  for(int i = 0; i<rows; i++)
  {
    delete [] grid[i];
  }
  //Deallocating the array of pointers for the rows
  delete [] grid;
  grid = NULL;  //Setting the value of the first pointer in the array to null

  return;
}

bool solve(char* grid[], int x, int y)
{
  int oldX = x, oldY = y, testX, testY;
  for(short c=0; c<4; c++)
  {
    testX = x + DIRECTIONS[c][0];
    testY = y + DIRECTIONS[c][1];
    if(grid[testX][testY]==' ' || grid[testX][testY]=='E')
    {
      x = testX;
      y = testY;
      if(grid[x][y]=='E')
      {
        return true;
      }
      else
      {
        grid[x][y]='.';
        if(solve(grid, x, y))
        {
          return true;
        }
        else
        {
          grid[x][y]=' ';
          x = oldX;
          y = oldY;
        }
      }
    }
  }
  return false;
}
