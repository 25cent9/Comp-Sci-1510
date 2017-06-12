/*
  Programmer: Innocent Niyibizi
  File: mybstree.h
  Date: 4/9/17
  Class: 1510 - B
  Instuctor: Taylor
  Description: Header file for a linked list implementation of a binary search tree
*/

#ifndef MYBSTREE
#define MYBSTREE

#include "abstractbstree.h"
template <typename T>
class TreeNode
{
public:
   T m_data;
   TreeNode* m_right;
   TreeNode* m_left;
};

template <typename T>
class MyBSTree : public AbstractBSTree<T>
{
private:

  TreeNode<T>* m_root;
  int m_size;

   //Function to help get the min of tree
   const T& recursive_getMin(TreeNode<T>* t) const
   {
      if ( t->m_left == NULL )
          return t->m_data;
      else
          return recursive_getMin( t->m_left );
   }

   //Function to help get the max of tree
   const T& recursive_getMax(TreeNode<T>* t) const
   {
       if ( t->m_right == NULL )
           return t->m_data;
       else
           return recursive_getMax( t->m_right );
    }

    //Function to get the pointer to the smallest node in tree
    TreeNode<T>* getSmallestNode(TreeNode<T>* t)
    {
      if ( t->m_right == NULL )
          return t;
      else
          return getSmallestNode( t->m_right );
    }

public:

  /*
   Description: Constructor
   Pre:         None
   Post:        A binary search tree with type T will be created
  */
   MyBSTree();

   /*
    Description: Copy Constructor
    Pre:         cpy must be initialized
    Post:        A binary search tree with type T will be created from cpy
   */
   MyBSTree(const MyBSTree<T>& cpy);

   /*
    Description: Destructor
    Pre:         None
    Post:        All nodes in bst will be deleted
   */
   ~MyBSTree();

   /*
    Description: Function to return the size of the binary search tree
    Pre:         None
    Post:        Size is returned
   */
   int size() const;

   /*
    Description: Function to return if bst is empty
    Pre:         None
    Post:        true is retured if empty, else false is retured if not
   */
   bool isEmpty() const;

   /*
    Description: Function to return the height of the tree
    Pre:         None
    Post:        Height of bst is returned
   */
   int height() const;

   /*
    Description: Funtion to find the max of the tree
    Pre:         None
    Post:        The max value is returned. Oopa ia thrown if tree is empty
   */
   const T& getMax() const throw (Oops);

   /*
    Description: Funtion to find the min of the tree
    Pre:         None
    Post:        The min value is returned. Oopa ia thrown if tree is empty
   */
   const T& getMin() const throw (Oops);

   /*
    Description: Funtion to find the given value in the tree
    Pre:         None
    Post:        Level in tree of value is returned, negative if not found
   */
   int find(const T& x) const;

   /*
    Description: Funtion to clear all nodes
    Pre:         None
    Post:        All nodes are deleted and tree will be empty
   */
   void clear();

   /*
    Description: Funtion to insert x into the tre
    Pre:         None
    Post:        x will be inserted into the correct spot of tree
   */
   void insert(const T& x);

   /*
    Description: Funtion to remove x from the tree
    Pre:         None
    Post:        x is no longer in the tree
   */
   void remove(const T& x);

   /*
    Description: Funtion to print the tree in pre-order style
    Pre:         None
    Post:        Tree is printed in pre-order style
   */
   void printPreOrder() const;

   /*
    Description: Funtion to print the tree in post-order style
    Pre:         None
    Post:        Tree is printed in post-order style
   */
   void printPostOrder() const;

   /*
    Description: Funtion to print the tree
    Pre:         None
    Post:        Tree is printed
   */
   void print() const;

   //Function to help print tree in pre-order style
   void preOrderPrint(const TreeNode<T>* t) const;

   //Function to help print tree in post-order style
   void postOrderPrint(const TreeNode<T>* t) const;

   //Function to help print tree in a pretty style
   void prettyPrint(const TreeNode<T>* t, int pad) const;

   //Function to help insert x into the tree
   TreeNode<T>* insertNode(TreeNode<T>* t, const T& x);

   //Functio to help get the height of tree
   int getHeigt(TreeNode<T>* t, int count) const;

   //Function to help delete the nodes
   void deleteNodes(TreeNode<T>* t);

   //Function to clone a tree
   TreeNode<T>* clone(const TreeNode<T>* t);

   //Function to help find x in tree
   int findNode(TreeNode<T>* t, const T& x, int& count) const;

   //Function to help remove x from tree
   TreeNode<T>* removeNode(TreeNode<T>* t, const T& x);

   /*
    Description: Funtion to copy the contents of rhs tree to lhs tree
    Pre:         rhs tree must be intitalized
    Post:        lhs tree is the same as rhs
   */
   MyBSTree& operator =(const MyBSTree& rhs);

};

#include "mybstree.hpp"

#endif
