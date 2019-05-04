//Â  Created by Frank M. Carrano and Timothy M. Henry.
//Â  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** A class of nodes for a link-based binary tree.
 Listing 16-2.
 @file BinaryNode.h */

#ifndef LAB_6_BST_BINARYNODE_H
#define LAB_6_BST_BINARYNODE_H


#include <memory>
#include <cstddef>

template<class ItemType>
class BinaryNode
{
private:
   ItemType              item;           // Data portion
   std::shared_ptr<BinaryNode<ItemType>> leftChildPtr;   // Pointer to left child
   std::shared_ptr<BinaryNode<ItemType>> rightChildPtr;  // Pointer to right child

public:
   BinaryNode();
   BinaryNode(const ItemType& anItem);
   BinaryNode(const ItemType& anItem,
              std::shared_ptr<BinaryNode<ItemType>> leftPtr,
              std::shared_ptr<BinaryNode<ItemType>> rightPtr);

   void setItem(const ItemType& anItem);
   ItemType getItem() const;

   bool isLeaf() const;

    std::shared_ptr<BinaryNode<ItemType>> getLeftChildPtr() const;
    std::shared_ptr<BinaryNode<ItemType>> getRightChildPtr() const;

   void setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr);
   void setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr);
}; // end BinaryNode


/*******************************************************************************
**                       IMPLEMENTATION                                       **
*******************************************************************************/
template<class ItemType>
BinaryNode<ItemType>::BinaryNode()
        : leftChildPtr(nullptr), rightChildPtr(nullptr)
{ }  // end default constructor

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
        : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr)
{ }  // end constructor

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,
                                 std::shared_ptr<BinaryNode<ItemType>> leftPtr,
                                 std::shared_ptr<BinaryNode<ItemType>> rightPtr)
        : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr)
{ }  // end constructor

template<class ItemType>
void BinaryNode<ItemType>::setItem(const ItemType& anItem)
{
    item = anItem;
}  // end setItem

template<class ItemType>
ItemType BinaryNode<ItemType>::getItem() const
{
    return item;
}  // end getItem

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
    return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
}

template<class ItemType>
void BinaryNode<ItemType>::setLeftChildPtr(std::shared_ptr<BinaryNode<ItemType>> leftPtr)
{
    leftChildPtr = leftPtr;
}  // end setLeftChildPtr

template<class ItemType>
void BinaryNode<ItemType>::setRightChildPtr(std::shared_ptr<BinaryNode<ItemType>> rightPtr)
{
    rightChildPtr = rightPtr;
}  // end setRightChildPtr

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getLeftChildPtr() const
{
    return leftChildPtr;
}  // end getLeftChildPtr

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinaryNode<ItemType>::getRightChildPtr() const
{
    return rightChildPtr;
}  // end getRightChildPtr

#endif //LAB_6_BST_BINARYNODE_H
