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
    //If the established node's item is > than the new node's item, then attach towards left branch
    else if (subTreePtr->getItem() > newNodePtr->getItem() ){
        auto tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
        subTreePtr->setLeftChildPtr(tempPtr);
    }
        //If the established node's item is < than the new node's item, then attach towards right branch
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

    //Mark if there is a single child and leaf in either the left or right branch
    bool hasSingleLeftChild = (nodePtr->getRightChildPtr() == nullptr) && (nodePtr->getLeftChildPtr() != nullptr);
    bool hasSingleRightChild = (nodePtr->getRightChildPtr() != nullptr) && (nodePtr->getLeftChildPtr() == nullptr);

    //If it's a leaf, we can delete this node
    if (nodePtr->isLeaf()) {
        nodePtr = nullptr;
        return nodePtr;
    }
    //If there's one child, then connect parent node to grandchild node of the child node being deleted
    else if (hasSingleLeftChild || hasSingleRightChild){
        auto nodeToConnectPtr = std::make_shared<BinaryNode<ItemType>>();        //Initialize node we're returning
        if (hasSingleLeftChild){
            nodeToConnectPtr = nodePtr->getLeftChildPtr();
        }
        else {
            nodeToConnectPtr = nodePtr->getRightChildPtr();
        }
        return nodeToConnectPtr;
    }
    else {   //nodePtr has two children
        //Find the inorder successor of the entry in nodePtr: it is the left subtree rooted
        //at nodePtr's right child

        //Mark the current node's item, will use to replace the node we're removing
        ItemType inorderSuccessor = nodePtr->getItem();
        //Traverse down the right branch's leftmost node (not necessarily child node)
        auto tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), inorderSuccessor);
        //Set local node's right child to the node found in tempPtr
        nodePtr->setRightChildPtr(tempPtr);
        //Set local node's item to the deleted node's item
        nodePtr->setItem(inorderSuccessor);
        return nodePtr;
    }
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeLeftmostNode(
        std::shared_ptr<BinaryNode<ItemType>> subTreePtr, ItemType& inorderSuccessor) {
    if (subTreePtr->getLeftChildPtr() == nullptr){
        //This is the node we're searching for, it has no left child, but might have a right subtree
        inorderSuccessor = subTreePtr->getItem();
        return removeNode(subTreePtr);
    }
    else {
        //Traverse down the right child of root, furthest left descendant.
        auto tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
        subTreePtr->setLeftChildPtr(tempPtr);
        return subTreePtr;
    }
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
                                                                 const ItemType &target) const {
    //If current subTree root is nullptr, we're at a leaf
    if (subTreePtr == nullptr){
        return subTreePtr;
    }
    //If child node is equal to the target, return pointer to this node
    else if (subTreePtr->getItem() == target) {
        return subTreePtr;
    }
    //If the local node's item is greater than the target, then search the left branch
    else if (subTreePtr->getItem() > target){
        return findNode(subTreePtr->getLeftChildPtr(), target);
    }
    //If the local node's item is leass than the target, then search the right branch
    else {
        return findNode(subTreePtr->getRightChildPtr(), target);
    }
}

#endif //LAB_6_BST_BINARYSEARCHTREE_H