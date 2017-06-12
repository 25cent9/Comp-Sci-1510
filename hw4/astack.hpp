/*
  Programmer: Innocent Niyibizi
  File: astack.hpp
  Date: 3/15/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Templated hpp file for an arraylist implementation of a stack
*/

template <typename T>
AStack<T>::AStack()
{
  maxSize = 8;
  topIndex = 0;
  itemArray = new T[maxSize];
}

template <typename T>
AStack<T>::~AStack()
{
  clear();
  delete [] itemArray;
  itemArray = NULL;
}

template <typename T>
void AStack<T>::clear()
{
  topIndex = 0;
  return;
}

template <typename T>
bool AStack<T>::isEmpty() const
{
  return (topIndex==0)?true:false;
}

template <typename T>
void AStack<T>::pop()
{
  if(!isEmpty())
  {
    topIndex--;
    if(topIndex<=(maxSize/4))
      shrink();
  }
  else
  {
    throw Oops(": INVALID!");
  }

  return;
}

template <typename T>
void AStack<T>::push(const T& item)
{
  itemArray[topIndex++] = item;
  if(topIndex==maxSize)
    grow();
  return;
}

template <typename T>
const T& AStack<T>::top() const throw (Oops)
{
  if(topIndex != 0)
    return itemArray[topIndex-1];
  throw Oops("Unable to acess empty stack");
}

template <typename T>
void AStack<T>::grow()
{
  int newSize = maxSize*2;
  T* newM_data = new T[newSize];
  maxSize = newSize;
  for(int i=0; i<topIndex; i++)
  {
    newM_data[i] = itemArray[i];
  }
  delete []itemArray;
  itemArray = newM_data;
  return;
}

template <typename T>
void AStack<T>::shrink()
{
  int newSize = maxSize/2;
  T* newM_data = new T[newSize];
  maxSize = newSize;
  for(int i=0; i<topIndex; i++)
  {
    newM_data[i] = itemArray[i];
  }
  delete []itemArray;
  itemArray = newM_data;
  return;
}
