/*
  Programmer: Innocent Niyibizi
  File: fishbomb.cpp
  Date: 1/29/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Create program to help bender fish
*/

#include <iostream>
#include <fstream>
using namespace std;

//Constants
const short NUM_BOMBS = 3;  //Number of bombs per grid
const short BLAST_SIZE = 5; //Blast size of bomd
const short BLAST_RAD = BLAST_SIZE/2; //Finding the blast radius by dividing
                                      //blast size by 2

//Struct that will hold x and y values of bomb
struct Point
{
  short x;
  short y;
};

/*
  Description: Fucntion that will deallocate a two level pointer array
  Pre:         Array must be intialized
  Post:        Array is deallocate from memory and first pointer is set to null
*/
void deallocate(int**, const int);

int main()
{
  //Declaring variables
  int numRows, numCols, numTests, numFish = 0, rowEdge = 0, colEdge = 0;

  cin>>numTests;  //Reading in number of tests

  //Loop that will run for the given number of test cases
  for(int counter = 0; counter<numTests; counter++)
  {
    numFish = 0;  //Setting number of fish to 0
    //Getting the dimensions of the grid
    cin>>numRows;
    cin>>numCols;

    //Allocating memory space for the user defined array
    int **array = new int*[numRows];
    for(int i = 0; i< numRows; i++)
    {
      array[i] = new int[numCols];
      for(int j=0; j<numCols; j++)
      {
        cin>>array[i][j];
      }
    }

    Point point;  //Creating a point
    //Loop that will run until the number of bombs are set off for that grid
    for(int i =0; i<NUM_BOMBS; i++)
    {
      //Collecting x and y coordinate of bomb
      cin>>point.x;
      cin>>point.y;
      //Setting the value of rowEdge and colEdge
      rowEdge = point.x-BLAST_RAD;
      colEdge = point.y-BLAST_RAD;
      //Loop to run until the x and y coordinates are at the bomb's radius
      for(int row = 0; row<BLAST_SIZE; row++)
      {
        for(int col = 0; col<BLAST_SIZE; col++)
        {
          //Adding the value of the array currrent x and y coordinates to the
          //fish count
          numFish+=array[rowEdge+row][colEdge+col];
          array[rowEdge+row][colEdge+col] = 0;  //Setting value to 0
        }
      }
    }
    //Displaying the results for the current test case
    cout<<"#"<<counter<<": Bender catches "<<numFish<<" fish"<<endl;

    deallocate(array, numRows);
  }

  return 0;
}

void deallocate(int **grid, const int rows)
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
