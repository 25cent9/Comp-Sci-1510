/*
 Programmer: Innocent Niyibizi
 File: dijkstra.cpp
 Date: 5/2/17
 Class: 1510 - B
 Instuctor: Taylor
 Description: Main cpp for implementing dijkstra's algorithm
*/

#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <map>

#define INFINITY 999999

using namespace std;

struct Tube
{
  string dest;
  int weight;
  Tube(){weight = INFINITY;}
};

struct Location
{
  string name;
  list<Tube> tubes;
};

const string START = "airport";
const string END = "robotbar";

bool operator<(const Tube &t1, const Tube t2)
{
  return t1.weight > t2.weight;
}

int findShortest(map<string, list<Tube> > theMap)
{
  map<string, int> dists;
  for(map<string, list<Tube> >::iterator it = theMap.begin(); it!=theMap.end(); it++)
  {
    dists[it->first] = INFINITY;
  }
  priority_queue<Tube> theQueue;
  Tube temp;
  temp.dest = START;
  temp.weight = 0;
  theQueue.push(temp);
  while (!theQueue.empty())
  {
    Tube current = theQueue.top();
    theQueue.pop();
    if(current.dest == END)
    {
      return current.weight;
    }
    if(current.weight <= dists[current.dest])
    {
      dists[current.dest] = current.weight;
      for(list<Tube>::iterator it = theMap[current.dest].begin(); it!=theMap[current.dest].end(); it++)
      {
        temp.dest = it->dest;
        temp.weight = current.weight + it->weight;
        theQueue.push(temp);
      }
    }
  }
  return -1;
}

int main()
{
  map<string, list<Tube> > locations;
  int numTests, weight, adj, numLocations;
  string cityName, currLocation, curr;
  cin>>numTests;
  for(int i = 0; i<numTests; i++)
  {
    cin>>cityName>>numLocations;
    for(int j = 0; j<numLocations; j++)
    {
      cin>>currLocation>>adj;
      locations[currLocation];
      list<Tube> tubes;
      for(int l = 0; l<adj; l++)
      {
        cin>>curr>>weight;
        Tube tube;
        tube.dest = curr;
        tube.weight = weight;
        tubes.push_back(tube);
      }
      locations[currLocation] = tubes;
    }
    cout<<"#"<<i+1<<" : "<<cityName<<", "<<findShortest(locations)<<" tokens."<<endl;
  }
  return 0;
}
