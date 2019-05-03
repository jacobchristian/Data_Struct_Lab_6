#include <iostream>
#include <iomanip>
#include <random>
#include <memory>
#include <chrono>
#include "BinarySearchTree.h"


void display(int& anEntry){
    std::cout << std::setw(3) << anEntry << " ";
}
int main()
{
    const int MAX_ENTRIES = 11;
    //Create a seed for the mt_generator (note: bug in GCC compiler does not alter/change the
    //seed. Known Windows + GCC error
    //[see: https://bit.ly/2Xk3sYu]
    //One way to generate random numbers is to seed the generator is to use OS internal time
    //with the <chrono library>
  //  auto seed = (std::chrono::system_clock::now().time_since_epoch().count());
    auto seed = 0;
    std::mt19937_64 generator(seed);
    std::uniform_int_distribution<int> dist(1,100);

    //Initialize sorted list object
    std::_MakeUniq<BinarySearchTree<int>>::__single_object sortedTree;
    sortedTree = std::make_unique<BinarySearchTree<int>>();

    //Add random numbers to sorted list
    int lastRandomNumberCreated = 0;    //compiler didn't like that variable wasn't initialized
    std::cout << "\t\t***RANDOM NUMBERS GENERATED***\n";
    for (int i = 1; i <= MAX_ENTRIES; i++) {
        lastRandomNumberCreated = dist(generator);
        std::cout << lastRandomNumberCreated << " ";
        sortedTree->add(lastRandomNumberCreated);
    }
    std::cout << std::endl;
    std::cout << " PreorderTraverse: ";
    sortedTree->preorderTraverse(display);
    std::cout << std::endl;
    std::cout << "  InorderTraverse: ";
    sortedTree->inorderTraverse(display);
    std::cout << std::endl;
    std::cout << "PostorderTraverse: ";
    sortedTree->postorderTraverse(display);

    std::cout << "\n Height of tree  = " << sortedTree->getHeight();
    std::cout << "\n Number of nodes = " << sortedTree->getNumberOfNodes();
    try{
        std::cout << "\nItem found: " << sortedTree->getEntry(100) << std::endl;
        sortedTree->getEntry(33);
    }
    catch(NotFoundException& e) {
        std::cout << e.what();
    }
    try {
        std::cout << "\nSetting root data... ";
        sortedTree->setRootData(100);
    }
    catch (PrecondViolatedExcep& e){
        std::cout << e.what();

    }

    return 0;
}