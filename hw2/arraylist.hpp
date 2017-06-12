/*
  Programmer: Innocent Niyibizi
  File: arraylist.hpp
  Date: 2/5/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Create hpp to implement the arraylist class
*/
#include <iostream>
using namespace std;

/*
 * ----- Auxiliary Functions -----
 */
 //function to grow arraylist by two times the current max
template <typename T>
void ArrayList<T>::grow()
{
  if(m_max==0)
    m_max=1;
  int newSize = m_max*2;
  T* newM_data = new T[newSize];
  m_max = newSize;
  for(int i=0; i<m_size; i++)
  {
    newM_data[i] = m_data[i];
  }
  delete []m_data;
  m_data = newM_data;
  return;
}

//Function to shrink the arraylist in half
template<typename T> void ArrayList<T>::shrink()
{
  int newSize = m_max/2;
  T* newM_data = new T[newSize];
  m_max = newSize;
  for(int i=0; i<m_size-1; i++)
  {
    newM_data[i] = m_data[i];
  }
  delete []m_data;
  m_data = newM_data;
  return;
}

/*
 * ---- Constructors ---
 */
 //Destructor
template <typename T>
ArrayList<T>::~ArrayList()
{
 delete[] m_data;
}

//Overloaded constructor
template <typename T>
ArrayList<T>::ArrayList(int size, const T& val)
{
  m_size = size;
  m_max = size+1;
  m_data[0] = val;
}

//Functions for copying
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy)
{
    m_size = cpy.size();
    m_max = cpy.max();
    m_data = new T[m_size];
    for(int i = 0; i<m_size; i++)
    {
      m_data[i] = cpy.m_data[i];
    }
}

template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs)
{
  m_size = rhs.size();
  m_max = rhs.max();
  m_data = new T[m_size];
  for(int i = 0; i<m_size; i++)
  {
    m_data[i] = rhs.m_data[i];
  }
  return *this;
}

/*
 * ----- Basic Accessor Operations -----
 */
//Function to find and return the position of a given value
template <typename T>
int ArrayList<T>::find(const T& val) const
{
  bool found = false;
  int first = 0;
  for(int i=0; i<m_size; i++)
  {
    if(m_data[i]==val)
    {
      found = true;
      first = i;
    }

  }

  if(found)
    return first;
  else
    return -1;
}

//Function to see if the first index exists
template <typename T>
const T& ArrayList<T>::first() const
{
  if(m_size == 0)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST.first()!! (List is empty)"<<endl;
    return m_errobj;
  }
  else
    return m_data[0];
}

//Function to return the size of the arraylist
template <typename T>
int ArrayList<T>::size ()const {return m_size;}

//Overloaded [] operators used to return value at given index
//One is read-only and the other is read and write
template <typename T>
const T& ArrayList<T>::operator[] (int i) const
{
  if(i>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.[]  (index out of bounds)"<<endl;
    return m_errobj;
  }
  else
    return m_data[i];
}

template <typename T>
T& ArrayList<T>::operator[](int i)
{
  if(i>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.[]  (index out of bounds)"<<endl;
    return m_errobj;
  }
  else
    return m_data[i];
}

/*
 * ----- Basic Mutator Operations -----
 */
 //Function to clear the arraylist
 template <typename T>
 void ArrayList<T>::clear()
 {
   m_size = m_max = 0;
   delete []m_data;
   m_data = NULL;
   return;
 }

//Fuinction to insert given value to back of the arraylist
template<typename T>
void ArrayList<T>::insert_back(const T& value)
{
 if(m_size+1>=m_max)
 {
   grow();
   m_data[m_size] = value;
   m_size++;
 }
 else
 {
   m_data[m_size] = value;
   m_size++;
 }

 return;
}

//Function to insert given value at given index
template <typename T>
void ArrayList<T>::insert(const T& val, int pos)
{
  if(pos>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.insert()  (index out of bounds)"
        <<endl;
    return;
  }
  else
  {
    for(int i=m_size; i>pos; i--)
    {
      m_data[i] = m_data[i-1];
    }
    m_data[pos] = val;

    m_size++;
    if(m_size==m_max)
      grow();

    return;
  }
}

//Function to remove value at given index
template <typename T>
void ArrayList<T>::remove(int pos)
{
  if(pos>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.remove()  (index out of bounds)"
    <<endl;
    return;
  }
  else
  {
    for(int i = pos; i<m_size-1; i++)
    {
      m_data[i] = m_data[i+1];
    }

    if(m_size>0)
    {
      m_size--;
    }
    if(m_size < (m_max/4))
    {
      shrink();
    }
    return;
  }
}

/*
 * ----- Complex Mutator Operations -----
 */
 //Function to reverse the order of the arraylist
template <typename T>
void ArrayList<T>::reverse()
{
  //Formula was given on line 230 on largetester.cpp
 for (int i=0; i< m_size/2; i++)
 {
   swap(i,m_size-1-i);
 }
 return;
}

//Function to swap the values of two given positions
template <typename T>
void ArrayList<T>::swap(int pos1, int pos2)
{
  if(pos1>m_size || pos2>m_size)
  {
    cout<<"!-- ERROR : PANIC in ARRAYLIST!!.swap()  (index out of bounds)"
    <<endl;
    return;
  }
  else
  {
    T temp = m_data[pos1];
    m_data[pos1] = m_data[pos2];
    m_data[pos2] = temp;
    return;
  }
}

//Function to append the array passed through to the object
template <typename T>
void ArrayList<T>::append(const ArrayList<T>& alist)
{
 int oldSize = m_size;
 m_size+=alist.size();
 int copyCount = 0;
 for(int i = oldSize; i<m_size; i++)
 {
   m_data[i]=alist.m_data[copyCount++];
 }
 return;
}
