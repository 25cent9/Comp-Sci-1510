/*
  Programmer: Innocent Niyibizi
  File: astack.cpp
  Date: 3/5/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Templated header file for an arraylist clas that inhereits the
                abstractstack class
*/

#ifndef ASTACK_H
#define ASTACK_H
#include "abstractstack.h"

template <typename T>
class AStack: public AbstractStack<T>
{
private:
  int maxSize;
  int topIndex;
  T *itemArray;
public:

  AStack();

  ~AStack();

  void clear();

  bool isEmpty() const;

  void pop();

  void push(const T& item);

  const T& top() const throw (Oops);

  void grow();

  void shrink();

};

#include "astack.hpp"

#endif
