/*
  Programmer: Innocent Niyibizi
  File: linkedbstree.hpp
  Date: 4/9/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Create hpp to implement the linkedlistbstree class
*/

#include <iostream>
using namespace std;

template <typename T>
MyBSTree<T>::MyBSTree()
{
  m_size = 0;
  m_root = NULL;
}

template <typename T>
MyBSTree<T>::~MyBSTree()
{
  clear();
}

template <typename T>
const T& MyBSTree<T>::getMin() const throw (Oops)
{
  if(isEmpty())
    throw Oops("OOPS! : Tree is Empty!!");
  else
     return recursive_getMin(m_root);
}

template <typename T>
const T& MyBSTree<T>::getMax() const throw (Oops)
{
  if(isEmpty())
    throw Oops("OOPS! : Tree is Empty!!");
  else
     return recursive_getMax(m_root);
}

template <typename T>
int MyBSTree<T>::size() const
{
  return m_size;
}

template <typename T>
int MyBSTree<T>::height() const
{
  int count = 0;
  return getHeigt(m_root, count)+1;
}

template <typename T>
int MyBSTree<T>::getHeigt(TreeNode<T>* t, int count) const
{
  if(t==NULL)
    return 0;
  else
  {
    count = getHeigt(t->m_left, count);
    count = getHeigt(t->m_right, count);
  }
  count++;
  return count;
}

template <typename T>
bool MyBSTree<T>::isEmpty() const
{
  if(m_size>0)
    return false;
  else
    return true;
}

template <typename T>
void MyBSTree<T>::print() const
{
  prettyPrint(m_root, 0);
  return;
}

template <typename T>
void MyBSTree<T>::prettyPrint(const TreeNode<T>* t, int pad) const
{
 string s(pad, ' ');
 if (t == NULL)
     cout << endl;
 else{
   prettyPrint(t->m_right, pad+4);
   cout << s << t->m_data << endl;
   prettyPrint(t->m_left, pad+4);
 }
}
template <typename T>
void MyBSTree<T>::printPreOrder() const
{
  preOrderPrint(m_root);
  return;
}

template <typename T>
void MyBSTree<T>::preOrderPrint(const TreeNode<T>* t) const
{
  if(t==NULL)
   return;
  cout<<t->m_data<<" ";
  preOrderPrint(t->m_left);
  preOrderPrint(t->m_right);
  return;
}

template <typename T>
void MyBSTree<T>::printPostOrder() const
{
  postOrderPrint(m_root);
  return;
}

template <typename T>
void MyBSTree<T>::postOrderPrint(const TreeNode<T>* t) const
{
  if(t==NULL)
   return;
  postOrderPrint(t->m_left);
  postOrderPrint(t->m_right);
  cout<<t->m_data<<" ";
  return;
}
template <typename T>
void MyBSTree<T>::insert(const T& x)
{
  int found =  1;
  found = findNode(m_root, x, found);
  if( found <= 1 )
  {
    m_root = insertNode(m_root, x);
    m_size++;
  }
  return;
}

template <typename T>
TreeNode<T>* MyBSTree<T>::insertNode(TreeNode<T>* t, const T& x)
{
  if(t==NULL)
  {
    t = new TreeNode<T>;
    t->m_data = x;
    t->m_left = NULL;
    t->m_right = NULL;
    return t;
  }
  else if(x < t->m_data)
   t->m_left = insertNode(t->m_left, x);
  else
   t->m_right = insertNode(t->m_right, x);
  return t;
}
template <typename T>
void MyBSTree<T>::remove(const T& x)
{
  m_root  = removeNode(m_root, x);
  m_size--;
  return;
}

template <typename T>
void MyBSTree<T>::deleteNodes(TreeNode<T>* t)
{
  if(t==NULL)
     return;
  deleteNodes(t->m_left);
  deleteNodes(t->m_right);
  delete t;
}

template <typename T>
TreeNode<T>* MyBSTree<T>::removeNode(TreeNode<T>* t, const T& x)
{
  if(t==NULL)
   return NULL;
  else if(x < t->m_data)
  {
    t->m_left = removeNode(t->m_left, x);
  }
  else if(x > t->m_data)
  {
    t->m_right = removeNode(t->m_right, x);
  }
  else
  {
    if(t->m_left == NULL)
    {
      TreeNode<T>* temp = t->m_right;
      delete t;
      return temp;
    }
    else if(t->m_right == NULL)
    {
      TreeNode<T>* temp = t->m_left;
      delete t;
      return temp;
    }
    else
    {
     TreeNode<T>* temp = getSmallestNode(t->m_left);
     t->m_data = temp->m_data;
     t->m_right = removeNode(t->m_right, temp->m_data);
     t->m_left = removeNode(t->m_left, t->m_data);
    }
  }
  return t;
}

template <typename T>
int MyBSTree<T>::find(const T& x) const
{
  int levelCount = 1;
  levelCount = findNode(m_root, x, levelCount);
  return levelCount;
}

template <typename T>
int MyBSTree<T>::findNode(TreeNode<T>* t, const T& x, int& count) const
{
  if(t == NULL)
   return count*-1;
  else if(x < t->m_data)
   return findNode(t->m_left, x, ++count);
  else if( x > t->m_data)
   return findNode(t->m_right, x, ++count);
  return count;
}

template <typename T>
void MyBSTree<T>::clear()
{
  deleteNodes(m_root);
  m_root = NULL;
  m_size = 0;
  return;
}

template <typename T>
MyBSTree<T>& MyBSTree<T>::operator=(const MyBSTree& rhs)
{
   m_root = clone(rhs.m_root);
   m_size = rhs.size();
   return *this;
}

template <typename T>
MyBSTree<T>::MyBSTree(const MyBSTree<T>& cpy)
{
  *this = cpy;
}

template <typename T>
TreeNode<T>* MyBSTree<T>::clone(const TreeNode<T>* t)
{
  if (t == NULL)
   return NULL;
  else
  {
   TreeNode<T>* node =  new TreeNode<T>;
   node->m_data = t->m_data;
   node->m_left = clone(t->m_left);
   node -> m_right = clone(t->m_right);
   return node;
  }
}
