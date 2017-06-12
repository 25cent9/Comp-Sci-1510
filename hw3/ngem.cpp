/*
  Programmer: Innocent Niyibizi
  File: ngem.cpp
  Date: 2/22/17
  Class: 1510 - B
  Instuctor: Taylor
  Description:
*/
#include <iostream>
#include <string>
#include "linkedlist.h"
using namespace std;

/***Constants*********/
const int MAX = 5;  //Max number of strands
const int BASES_MAX = 7;  //Max number of bases
const int COMMAND_COUNT = 8;  //Number of commands that exist
//String array of all the commands
const string COMMANDS[COMMAND_COUNT] = {"append","trim","clip","slice","copy",
"swap","transcribe","print"};
//Char array of all the bases
const char BASES[BASES_MAX] = {'P', 'Y', 'O', 'T', 'K', 'M', 'B'};

//Function prototypes
int findCommand(const string);
void getCompliment(LinkedList<char>&);
bool invalidBase(const char);
bool append(LinkedList<char> []);
bool trim(LinkedList<char> []);
bool clip(LinkedList<char> []);
bool slice(LinkedList<char> []);
bool copy(LinkedList<char> []);
bool swap(LinkedList<char> []);
bool transcribe(LinkedList<char> []);
void print(LinkedList<char> []);
void printErrors(string [], bool []);

int main()
{
  //Array of size MAX that will the DNA strands
  LinkedList<char> strands[MAX]={};

  //Strings
  string sequence = "", command = "", commandsUsed[COMMAND_COUNT-1] ={""};
  int charCount = 0, cmdUsedCnt =0;

  //Boolean array that will hold all of the errors from the commands
  bool errors[COMMAND_COUNT-1]={false};
  //Loop to run MAX times and place the given DNA strand into a LinkedList
  //The strand is then placed into the strands array
  for(int i = 0; i<MAX; i++)
  {
    charCount = 0;
    cin>>sequence;
    while(sequence[charCount]!='\0')
    {
      //Inserting front if list is empty
      //otherwise it is inserting in the back
      if(strands[i].isEmpty())
        strands[i].insert_front(sequence[charCount]);
      else
        strands[i].insert_back(sequence[charCount]);
      charCount++;
    }
  }

  //Loop to run as long as there are still commands that are in the input
  while (cin>>command)
  {
    //Switch that determines which function to call based on the return of the
    //findCommand function
    //Each case will increment the cmdUsedCnt value, get the corresoponding
    //boolean value into the errors array, and then set the current index of the
    //commandsUsed array to match the function name
    switch (findCommand(command))
    {
      case 0:
        cmdUsedCnt++;
        errors[cmdUsedCnt]=append(strands);
        commandsUsed[cmdUsedCnt] = "append";
        break;
      case 1:
        cmdUsedCnt++;
        errors[cmdUsedCnt]=trim(strands);
        commandsUsed[cmdUsedCnt] = "trim";
        break;
      case 2:
        cmdUsedCnt++;
        errors[cmdUsedCnt]=clip(strands);
        commandsUsed[cmdUsedCnt] = "clip";
        break;
      case 3:
        cmdUsedCnt++;
        errors[cmdUsedCnt]=slice(strands);
        commandsUsed[cmdUsedCnt] = "slice";
        break;
      case 4:
        cmdUsedCnt++;
        errors[cmdUsedCnt]=copy(strands);
        commandsUsed[cmdUsedCnt] = "copy";
        break;
      case 5:
        cmdUsedCnt++;
        errors[cmdUsedCnt]=swap(strands);
        commandsUsed[cmdUsedCnt] = "copy";
        break;
      case 6:
        cmdUsedCnt++;
        errors[cmdUsedCnt]=transcribe(strands);
        commandsUsed[cmdUsedCnt] = "transcribe";
        break;
      case 7:
        print(strands);
        printErrors(commandsUsed, errors);
        cmdUsedCnt=0;
        break;
    }
  }
  //Priting errors at end of input if print was not the last command
  if(cmdUsedCnt!=0)
    printErrors(commandsUsed, errors);
  return 0;
}

//Function to find the index of the command passed through
//Returns int for the index to be used in the main switch
int findCommand(const string command)
{
  for(int i =0; i<COMMAND_COUNT; i++)
  {
    if(command == COMMANDS[i])
    {
      return i;
    }
  }
  return -1;
}

//Function to get complpiment of the given strand and reverse it
//The complpimented and reversed strand is assigned to the strand passed through
void getCompliment(LinkedList<char>& list)
{
  char data = ' ';
  char insert = ' ';
  for(int i=0; i<list.size(); i++)
  {
    data = list.getAtPtr(i)->m_data;
    switch (data)
    {
      case 'P':
      case 'Y':
        insert = (data=='P')?'Y':'P';
        list.getAtPtr(i)->m_data=insert;
        break;
      case 'O':
      case 'T':
        insert = (data=='O')?'T':'O';
        list.getAtPtr(i)->m_data=insert;
        break;
      case 'K':
      case 'M':
        insert = (data=='K')?'M':'K';
        list.getAtPtr(i)->m_data=insert;
        break;
    }
  }

  return ;
}

//Function to find an invalid base
//If an invalid base is found then true is returned
bool invalidBase(const char base)
{
  bool invalid = false;
  switch (base)
  {
    case 'K':
    case 'T':
    case 'P':
    case 'O':
    case 'Y':
    case 'B':
    case 'M':
      invalid = false;
      break;
    default:
      invalid = true;
  }
  return invalid;
}

//Function to append the given sequence to the indicated strand
//If sequence is valid then it is appened to the strand
bool append(LinkedList<char> lists[])
{
  int id = 0;
  bool invalid = false;
  string sequence = "";
  cin>>id;
  cin>>sequence;
  int charCount = 0;
  if(id>MAX)
    invalid = true;
  while(sequence[charCount]!= '\0' && invalid==false)
  {
    if(invalidBase(sequence[charCount])==true)
    {
      invalid = true;
      break;
    }
    charCount++;
  }
  if(invalid == false)
  {
    charCount=0;
    while(sequence[charCount] != '\0')
    {
      lists[id].insert_back(sequence[charCount]);
      charCount++;
    }
  }
  return invalid;
}

//Function to trim the indicated strand if parameters are valid
//If the id or trim position is invalid then the strand does not change
bool trim(LinkedList<char> lists[])
{
  int id, trimPos, newSize;
  bool invalid = false;
  cin>>id;
  cin>>trimPos;
  if(id>MAX || (trimPos<0 || trimPos>lists[id].size()))
    invalid = true;
  if(invalid == false)
  {
    newSize = lists[id].size()-
                  (lists[id].size()-trimPos);
    while(lists[id].size()-1>=newSize)
    {
      lists[id].remove_back();
    }
  }
  return invalid;
}

//Function to clip the indicated strand from the start to stop positions
//If parameters are invalid then false is returned and strand is uncahnged
bool clip(LinkedList<char> lists[])
{
  int id, start, stop;
  bool invalid = true;
  cin>>id;
  cin>>start;
  cin>>stop;
  if((0<=id && id<MAX) && (0<=start && start<=stop && stop<lists[id].size()))
    invalid = false;
  if(invalid == false)
  {
    for(int i =0; i<stop-start+1; i++)
    {
      lists[id].remove(lists[id].getAtPtr(start));
    }
  }
  return invalid;
}

//Function to slice the indicated strand from the start to stop Postconditions
//If parameters are invalid then false is returned and strand is uncahnged
bool slice(LinkedList<char> lists[])
{
  int id, start, stop;
  bool invalid = false;
  cin>>id;
  cin>>start;
  cin>>stop;
  if(id>MAX || (start<0 || start>lists[id].size()) ||
    (stop<0 || stop>lists[id].size()))
    {
      invalid = true;
    }
  if(invalid == false)
  {
    int tempSize = lists[id].size();
    for(int i =0; i < tempSize - stop -1; i++)
    {
      lists[id].remove_back();
    }
    for(int i = 0; i<start; i++)
    {
      lists[id].remove_front();
    }
  }
  return invalid;
}

//Function to copy the first strand the value of the second strand
//If parameters are invalid then false is returned and strand is uncahnged
bool copy(LinkedList<char> lists[])
{
  int id, id2;
  bool invalid = false;
  cin>>id;
  cin>>id2;
  if((0<=id && id < MAX) && (0<=id2 && id2 < MAX))
  {
    lists[id2] = lists[id];
    invalid = false;
  }
  else
  {
    invalid = true;
  }
  return invalid;
}

//Function to swap the tails of one strand with another strand
//If parameters are invalid then false is returned and strand is uncahnged
bool swap(LinkedList<char> lists[])
{
  bool invalid = false;
  int id[2];
  int start[2];
  string tail[2] = {"", ""};
  cin>>id[0];
  cin>>start[0];
  cin>>id[1];
  cin>>start[1];
  if((0<=id[0] && id[0] < MAX) &&
     (0<=id[1] && id[1] < MAX) &&
     (0<=start[0] && start[0] < lists[id[0]].size()) &&
     (0<=start[1] && start[1] < lists[id[1]].size()))
     {
       for(int i=0; i< 2; i++)
       {
         while (lists[id[i]].getAtPtr(start[i]) != NULL)
         {
           tail[i] = lists[id[i]].getLastPtr()->m_data + tail[i];
           lists[id[i]].remove_back();
         }
       }
       for(unsigned int i =0; i<tail[1].size(); i++)
        lists[id[0]].insert_back(tail[1][i]);
       for(unsigned int i =0; i<tail[0].size(); i++)
        lists[id[1]].insert_back(tail[0][i]);
     }
  else
  {
    invalid = true;
  }
  return invalid;
}

//Function to transcribe the indicated strand with its base complimnets
//If parameters are invalid then false is returned and strand is uncahnged
bool transcribe(LinkedList<char> lists[])
{
  int id=0;
  bool invalid = false;
  string complimnet ="";
  cin>>id;
  if(id<0 || id>MAX)
    invalid = true;
  else
  {
    getCompliment(lists[id]);
    for(int i = 0; i<lists[id].size(); i++)
    {
      complimnet+=lists[id].getAtPtr(i)->m_data;
    }
    LinkedList<char> temp;
    for(int i =0; i<lists[id].size(); i++)
    {
      temp.insert_front(lists[id].getAtPtr(i)->m_data);
    }
    lists[id] = temp;
  }
  return invalid;
}

//Function to print off all of the strands
void print(LinkedList<char> lists[])
{
  for(int i=0; i<MAX; i++)
  {
    cout<<"#"<<i<<", ";
    cout<<lists[i].size()<<": ";
    cout<<lists[i]<<endl;
  }
  cout<<endl;
  return;
}

//Function to print off any errors that may have occured since the last print
void printErrors(string commands[], bool errors[])
{
  for(int i =0; i<COMMAND_COUNT-1; i++)
  {
    if(errors[i]==true)
    {
      cout<<"ERROR! "<<commands[i]<<": invalid parameters."<<endl;
    }
  }
}
