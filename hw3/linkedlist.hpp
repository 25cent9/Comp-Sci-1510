/*
  Programmer: Innocent Niyibizi
  File: arraylist.hpp
  Date: 2/20/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Create hpp to implement the LinkedList class
*/
#include <iostream>
using namespace std;

template <typename T>
LinkedList<T>::LinkedList()
{
  m_head = NULL;
  m_back = NULL;
  m_size=0;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
  clear();
}

template <typename T>
LinkedList<T>:: LinkedList(const LinkedList<T>& rhs)
{
  m_head = NULL;
  m_back = NULL;
  m_size=0;
  *this = rhs;
}

template <class T>
const LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
  clear();
  const Node<T> *tmpR = rhs.getFirstPtr();
  for(int k = 0; k < rhs.size(); k++)
  {
    if (k == 0)
      insert_front(tmpR -> m_data);
    else insert_back(tmpR -> m_data);
    tmpR = tmpR -> m_next;
  }

  return *this;
}

template <typename T>
int LinkedList<T>::size() const
{
  return m_size;
}

template <typename T>
bool LinkedList<T>::isEmpty() const
{
  if(m_head == NULL)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template <typename T>
Node<T>* LinkedList<T>:: getFirstPtr()
{
  return m_head;
}

template <typename T>
const Node<T>* LinkedList<T>:: getFirstPtr() const
{
  return m_head;
}

template <typename T>
Node<T>* LinkedList<T>:: getLastPtr()
{
  if(isEmpty())
    return NULL;
  else
  {
    Node<T>* lastPoint = m_head;
    while(lastPoint!=m_back)
    {
      lastPoint = lastPoint->m_next;
    }
    return lastPoint;
  }
}

template <typename T>
Node<T>* LinkedList<T>:: getAtPtr(int i)
{
  if(i >= 0 && i<m_size)
  {
    Node<T>* temp = m_head;
    for(int k = 0; k<i; k++)
    {
      temp = temp -> m_next;
    }
    return temp;
  }
  else
    return NULL;
}

template <typename T>
void LinkedList<T>::clear()
{
  Node<T>* temp = m_head;
  for(int i = 0; i<m_size; i++)
  {
    m_head = temp -> m_next;
    delete temp;
    temp = m_head;
  }
  m_head = m_back = NULL;
  m_size = 0;
  return;
}

template <typename T>
void LinkedList<T>:: insert_front(const T& x)
{
  Node<T>* newNode = new Node<T>;
  newNode ->m_next = m_head;
  newNode ->m_data = x;
  m_head = newNode;
  if(m_size==0)
    m_back = newNode;
  m_size++;
  return;
}

template <typename T>
void LinkedList<T>:: insert_back(const T& x)
{
  if(m_size==0)
  {
    insert_front(x);
  }
  else
  {
    Node<T>* temp = new Node<T>;
    temp -> m_data = x;
    temp -> m_next = NULL;
    if(m_size > 0)
      m_back -> m_next = temp;
    m_back = temp;
    m_size++;
  }
  return;
}

template <typename T>
void LinkedList<T>::insert(const T& x, Node<T>* poz)
{
  Node<T>* temp = new Node<T>;
  temp->m_data = poz->m_data;
  temp->m_next = poz->m_next;
  poz->m_data = x;
  poz->m_next = temp;
  m_size++;
  return;
}

template <typename T>
void LinkedList<T>:: remove_front()
{
  Node<T> *tmp = m_head -> m_next;
  delete m_head;
  m_head = tmp;
  m_size--;
}

template <typename T>
void LinkedList<T>::remove_back()
{
  Node<T> *tmp = m_head;
  while(tmp -> m_next != m_back)
  {
    tmp = tmp -> m_next;
  }
  delete m_back;
  tmp -> m_next = NULL;
  m_back = tmp;
  m_size--;
}

template <typename T>
void LinkedList<T>::remove(Node<T>* pos)
{
  if(pos == m_head)
  {
    remove_front();
  }
  else if (pos == m_back)
  {
    remove_back();
  }
  else
  {
    Node<T> *tmp = m_head;
    while(tmp -> m_next != pos)
    {
      tmp = tmp -> m_next;
    }
    tmp -> m_next = pos -> m_next;
    delete pos;
    m_size--;
  }
}

template <typename T>
bool LinkedList<T>:: operator ==(const LinkedList<T>& rhs) const
{
  if(rhs.size() != m_size)
    return false;
  else
  {
    Node<T>* leftCursor = m_head;
    const Node<T>* rightCursor = rhs.getFirstPtr();
    while(leftCursor != NULL)
    {
      if(leftCursor->m_data != rightCursor->m_data)
      {
        return false;
      }
      else
      {
        leftCursor = leftCursor->m_next;
        rightCursor = rightCursor->m_next;
      }
    }
    return true;
  }
}

template <typename T>
std::ostream& operator<< (std::ostream& out, const LinkedList<T>& list)
{
  const Node<T>* cursor = list.getFirstPtr();
  while(cursor != NULL)
  {
    out<<cursor->m_data;
    cursor = cursor -> m_next;
  }
  return out;
}
