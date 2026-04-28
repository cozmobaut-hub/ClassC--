#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "Array.hpp"
#include "LinkedList.hpp"

void printList(IList<int>* list) {
    for (int i = 0; i < list->size(); ++i) {
        std::cout << list->get(i);
        if (i < list->size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void printList(IList<std::string>* list) {
    for (int i = 0; i < list->size(); ++i) {
        std::cout << list->get(i);
        if (i < list->size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::srand(std::time(nullptr));
    
    // Test Array sorting with integers
    std::cout << "Sorting an array:" << std::endl;
    Array<int> arr;
    int values[] = {4, 3, 8, 1, 5, 9, 7, 2, 6};
    for (int i = 0; i < 9; ++i) {
        arr.insert(i, values[i]);
    }
    
    std::cout << "Initial array: ";
    printList(&arr);
    
    arr.sort();
    
    std::cout << "Sorted array: ";
    printList(&arr);
    std::cout << std::endl;
    
    // Test LinkedList sorting with integers
    std::cout << "Sorting a Linked List:" << std::endl;
    LinkedList<int> ll;
    for (int i = 0; i < 9; ++i) {
        ll.insert(i, values[i]);
    }
    
    std::cout << "Initial list: ";
    printList(&ll);
    
    ll.sort();
    
    std::cout << "Sorted list: ";
    printList(&ll);
    std::cout << std::endl;
    
    // Test LinkedList sorting with strings
    std::cout << "Sorting a Linked List:" << std::endl;
    LinkedList<std::string> llStr;
    llStr.insert(0, "dog");
    llStr.insert(1, "cat");
    llStr.insert(2, "bird");
    llStr.insert(3, "elephant");
    
    std::cout << "Initial list: ";
    printList(&llStr);
    
    llStr.sort();
    
    std::cout << "Sorted list: ";
    printList(&llStr);
    std::cout << std::endl;
    
    // Search test
    int listType;
    std::cout << "Which list implementation to use? 1 - Array 2 - LinkedList: ";
    std::cin >> listType;
    
    int n, minVal, maxVal;
    std::cout << "How many integers to enter: ";
    std::cin >> n;
    std::cout << "Smallest value to generate: ";
    std::cin >> minVal;
    std::cout << "Largest value to generate: ";
    std::cin >> maxVal;
    
    IList<int>* testList = nullptr;
    
    if (listType == 1) {
        testList = new Array<int>();
    } else {
        testList = new LinkedList<int>();
    }
    
    for (int i = 0; i < n; ++i) {
        int randVal = minVal + std::rand() % (maxVal - minVal + 1);
        testList->insert(i, randVal);
    }
    
    std::cout << "Unsorted list: ";
    printList(testList);
    
    testList->sort();
    
    std::cout << "Sorted list: ";
    printList(testList);
    
    int numSearches;
    std::cout << "How many target values to search for: ";
    std::cin >> numSearches;
    
    for (int i = 0; i < numSearches; ++i) {
        int target;
        std::cout << "Enter target value: ";
        std::cin >> target;
        
        int pos = testList->search(target);
        std::cout << "Value " << target << " found at position: " << pos << std::endl;
    }
    
    delete testList;
    
    return 0;
}