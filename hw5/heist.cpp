/*
  Name: Innocent Niyibizi
  File: heist.cpp
  Section:  B
  Instructor: Taylor
  Date: 3-29-17
*/


#include <iostream>
#include "functions.h"

using namespace std;

int main()
{
  int numRow, numCol, map = 0, benderX=0, benderY=0;
  char dummy = '\0';
  cin>>numRow;
  while(numRow!=0)
  {
    cin>>numCol;
    cin.ignore();
    char **grid = new char*[numRow];
    for(int i = 0; i<numRow; i++)
    {
      grid[i] = new char[numCol];
      for(int j=0; j<numCol; j++)
      {
        cin.get(grid[i][j]);
        if(grid[i][j]=='B')
        {
          benderX = i;
          benderY = j;
        }
      }
      cin.get(dummy);
    }
    solve(grid, benderX, benderY);
    cout<<"Map : "<<map++<<endl;
    printGrind(grid, numRow, numCol);
    cout<<endl;
    deallocate(grid, numRow);
    cin>>numRow;
  }

  return 0;
}
