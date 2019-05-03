// Created by Frank M. Carrano and Timothy M. Henry.
// Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */

#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include <memory>
#include <vector>
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedEcxcep.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
// use this->rootPtr to access the BinaryNodeTree rootPtr

protected:
    //------------------------------------------------------------
    // Protected Utility Methods Section:
    // Recursive helper methods for the public methods.
    //------------------------------------------------------------
    // Recursively finds where the given node should be placed and
    // inserts it in a leaf at that point.
    std::shared_ptr<BinaryNode<ItemType>> placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                    std::shared_ptr<BinaryNode<ItemType>> newNode);

    // Removes the given target value from the tree while maintaining a
    // binary search tree.
    std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                      const ItemType& target,
                                                      bool& success) override;

    // Removes a given node from a tree while maintaining a
    // binary search tree.
    std::shared_ptr<BinaryNode<ItemType>> removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr);

    // Removes the leftmost node in the left subtree of the node
    // pointed to by nodePtr.
    // Sets inorderSuccessor to the value in this node.
    // Returns a pointer to the revised subtree.
    std::shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                             ItemType& inorderSuccessor);

    // Returns a pointer to the node containing the given value,
    // or nullptr if not found.
    std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                   const ItemType& target) const;

public:
    //------------------------------------------------------------
    // Constructor and Destructor Section.
    //------------------------------------------------------------
    // inherits from BinaryNodeTree

    //------------------------------------------------------------
    // Public Methods Section.
    //------------------------------------------------------------
    void setRootData(const ItemType& newData) const;
    bool add(const ItemType& newEntry) override;
    bool remove(const ItemType& anEntry) override;
    ItemType getEntry(const ItemType& anEntry) const override;
    bool contains(const ItemType& anEntry) const override;

}; // end BinarySearchTree



/*********************************************************************************************
**                      Public Method Implementations                                       **
*********************************************************************************************/
template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) const {
    std::string message = "Unable to set or change root, please do not use this public method\n";
    throw(PrecondViolatedExcep(message));
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry) {
    auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newEntry);
    this->rootPtr = placeNode(this->rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType &anEntry) {
    bool isSuccessful = false;
    this->rootPtr = removeValue(this->rootPtr, anEntry, isSuccessful);
    return isSuccessful;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType &anEntry) const {
    bool entryFound = contains(anEntry);
    if (entryFound) {
        return anEntry;
    }
    else{
        std::string message = "Item found found within binary tree.";
        throw(NotFoundException(message));
    }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType &anEntry) const {
    std::shared_ptr<BinaryNode<ItemType>> potentialItemNode = findNode(this->rootPtr, anEntry);
    if (potentialItemNode == nullptr)
        return false;
    else
        return potentialItemNode->getItem() == anEntry;
}

/*********************************************************************************************
**                   Protected Method Implementations                                       **
*********************************************************************************************/
template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                                  std::shared_ptr<BinaryNode<ItemType>> newNodePtr){
    if (subTreePtr == nullptr) {    //root of subtree
        return newNodePtr;
    }
    else if (subTreePtr->getItem() > newNodePtr->getItem() ){
        auto tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else {
        auto tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(
        std::shared_ptr<BinaryNode<ItemType>> subTreePtr, const ItemType& target, bool &success) {
    if (subTreePtr == nullptr){
        success = false;
    }
    else if (subTreePtr->getItem() == target)
    {
        //Item is in the root of the subtree
        subTreePtr = removeNode(subTreePtr);
        success = true;
    }
    else if (subTreePtr->getItem() > target){
        //Search left subTree
        auto tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
    else {
        //Search the right subTree
        auto tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
        subTreePtr->setRightChildPtr(tempPtr);
    }
    return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeNode(
        std::shared_ptr<BinaryNode<ItemType>> nodePtr) {
    if (nodePtr->isLeaf()) {
        nodePtr = nullptr;
        return nodePtr;
    }
    //STUB
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeLeftmostNode(
        std::shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType &inorderSuccessor) {
    return subTreePtr;
    //STUB
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                                 const ItemType &target) const {
    if (subTreePtr == nullptr){
        return subTreePtr;
    }
    else if (subTreePtr->getItem() == target) {
        return subTreePtr;
    }
    else if (subTreePtr->getItem() > target){
        return findNode(subTreePtr->getLeftChildPtr(), target);
    }
    else {
        return findNode(subTreePtr->getRightChildPtr(), target);
    }
}

#endif //LAB_6_BST_BINARYSEARCHTREE_H
