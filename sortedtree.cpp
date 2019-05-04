#include <iostream>
#include <iomanip>
#include <random>
#include <memory>
#include <chrono>
#include "BinarySearchTree.h"

//Display function for pre/in/post order traversal
void display(int& anEntry){
    std::cout << std::setw(3) << anEntry << " ";
}

int main()
{
    const int MAX_ENTRIES = 22;
    //Create a seed for the mt_generator (note: bug in GCC compiler does not alter/change the
    //seed. Known Windows + GCC error
    //[see: https://bit.ly/2Xk3sYu]
    //One way to generate random numbers is to seed the generator is to use OS internal time
    //with the <chrono library>
    auto seed = (std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int> dist(1,100);

    //Initialize sorted list object
    auto sortedTree = std::make_unique<BinarySearchTree<int>>();

    //Add random numbers to sorted list
    int lastRandomNumberCreated = 0;    //compiler didn't like that variable wasn't initialized

    std::cout << "\t\t***RANDOM NUMBERS GENERATED***\n";
    for (int i = 1; i <= MAX_ENTRIES; i++) {
        lastRandomNumberCreated = dist(generator);
        std::cout << lastRandomNumberCreated << " ";
        sortedTree->add(lastRandomNumberCreated);
    }

    //Displaying original list
    std::cout << "\n\t\t***Binary Tree generated.***";
    std::cout << "\n\n***Height of tree: " << sortedTree->getHeight();
    std::cout << "\n***Number of nodes: " << sortedTree->getNumberOfNodes();
    std::cout << "\n InorderTraverse: ";
    sortedTree->inorderTraverse(display);

    //Removing last entered number
    std::cout << "\n\nRemoving last entry generated. (Should be " << lastRandomNumberCreated << ")";
    sortedTree->remove(lastRandomNumberCreated);
    std::cout << "\n\n***Height of tree: " << sortedTree->getHeight();
    std::cout << "\n***Number of nodes: " << sortedTree->getNumberOfNodes();
    std::cout << "\n InorderTraverse: ";
    sortedTree->inorderTraverse(display);

    //Removing the root
    std::cout << "\n\nRemoving root of tree (should be " << sortedTree->getRootData() << ")...";
    std::cout << "\nDisplaying preorderTraversal. Root is " << sortedTree->getRootData();
    std::cout << "\npreOrderTraverse: ";
    sortedTree->preorderTraverse(display);
    sortedTree->remove(sortedTree->getRootData());
    std::cout << "\n\n***Height of tree: " << sortedTree->getHeight();
    std::cout << "\n***Number of nodes: " << sortedTree->getNumberOfNodes();
    std::cout << "\nPreorderTraverse: ";
    sortedTree->preorderTraverse(display);

    return 0;
}

/* EXAMPLE:
                   ***RANDOM NUMBERS GENERATED***
97 44 61 69 16 44 62 61 21 2 74 61 59 28 47 39 29 97 73 42 5 63
                ***Binary Tree generated.***

***Height of tree: 7
***Number of nodes: 22
 InorderTraverse:   2   5  16  21  28  29  39  42  44  44  47  59  61  61  61  62  63  69  73  74  97  97

Removing last entry generated. (Should be 63)

***Height of tree: 7
***Number of nodes: 21
 InorderTraverse:   2   5  16  21  28  29  39  42  44  44  47  59  61  61  61  62  69  73  74  97  97

Removing root of tree (should be 97)...
Displaying preorderTraversal. Root is 97
preOrderTraverse:  97  44  16   2   5  21  28  39  29  42  61  44  59  47  69  62  61  61  74  73  97

***Height of tree: 7
***Number of nodes: 20
PreorderTraverse:  97  44  16   2   5  21  28  39  29  42  61  44  59  47  69  62  61  61  74  73
*/