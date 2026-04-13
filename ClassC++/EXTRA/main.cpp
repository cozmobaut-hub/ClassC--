#include <iostream>
#include "BinarySearchTree.h"

int main()
{
    BinarySearchTree<int> tree;
    int count;
    int value;

    std::cout << "How many integers? ";
    std::cin >> count;

    for (int i = 0; i < count; i++)
    {
        std::cin >> value;
        tree.insert(value);
    }

    std::cout << "In Order:      ";
    tree.printInOrder();

    std::cout << "Pre Order:     ";
    tree.printPreOrder();

    std::cout << "Post Order:    ";
    tree.printPostOrder();

    std::cout << "Breadth Order: ";
    tree.printBreadthOrder();

    std::cout << "Depth Order:   ";
    tree.printDepthOrder();

    std::cout << "By Levels:" << std::endl;
    tree.printByLevels();

    std::cout << "Height: ";
    tree.height();

    return 0;
}
