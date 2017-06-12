/*
  Programmer: Innocent Niyibizi
  File: mystringmap.h
  Date: 4/18/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Header file for an implementation of a string hash-table
*/

#ifndef MYSTRINGMAP_H
#define MYSTRINGMAP_H

#include "abstractstringmap.h"

template <typename V>
class KeyValue
{
private:
  string key;
  V value;
public:
  bool active;
  KeyValue(){}

  KeyValue(const string& k, const V& val)
  {
    key = k;
    value = val;
    active = false;
  }

  const V& getValue() const
  {
    return value;
  }

  void setValue(const V& val)
  {
    value = val;
    return;
  }

  void setKey(string& val)
  {
    key = val;
    return;
  }

  const string& getKey() const
  {
    return key;
  }

};

template <typename T>
class MyStringMap : public AbstractStringMap<T>
{
private:
  unsigned int m_max;
  unsigned int m_size;
  int reHash(const string &s, const int MAX) const;
  int hash(const string &s) const;
  KeyValue<T> *map; //Dynamic array of type KeyValue
  string EMPTYKEY;  //Value for the empty key

public:

  //Default constructor
  MyStringMap();

  //Overloaded Copy constructor
  MyStringMap(const MyStringMap<T>& cpy);

  //Overloaded = operator
  MyStringMap<T>& operator=(const MyStringMap<T>& rhs);

  //Destructor
  ~MyStringMap();

  //  Description: Function to return number of KeyValue pairs in the map
  //  Pre: None
  //  Post: m_size returned
  int size() const;

  int max() const {return m_max;};

  //  Description: Function to return if the map is empty
  //  Pre: None
  //  Post: True returned if map empty, else false is returned
  bool isEmpty() const;

  //  Description: Function to return the value of the given key
  //  Pre: None
  //  Post: value of key is returned, Oops is thrown if key does not exist
  const T& valueOf(const string& key) const throw ( Oops );

  //  Description: Function to clear map
  //  Pre: None
  //  Post: m_size set to zero, map pointer is deleted
  void clear();

  //  Description: Function to insert given key and value in to map
  //  Pre: Key must be a string type
  //  Post: KeyValue inserted into map or value at the given key is upadated key
  //        is updated with the new value
  void insert(const string& key, const T& val);

  //  Description: Function to remove KeyValue pair from map
  //  Pre: None
  //  Post: m_size decreased by one and the key is set to the EMPTYKEY value
  void remove(const string& k);

  //  Description: Function to pretty print the key value pairs
  //  Pre: None
  //  Post: All the key value pairs are printed in a pretty fashion
  void print() const;

  //  Description: Function to grow the map when it reaches a certain size
  //  Pre: None
  //  Post: Map is grown by 2 times the amount
  void grow();

};

#include "mystringmap.hpp"

#endif
