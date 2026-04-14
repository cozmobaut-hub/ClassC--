#include <iostream>

#include "test_suite.h"

#include "Array.hpp"
#include "LinkedList.hpp"

int main() {

    int numTestsToRun;
    while(true) {
        std::cout << "How many tests do you wish to run? (Enter an integer, negative value will run all tests): ";
        std::cin >> numTestsToRun;
        if(!std::cin.fail()) break;

        std::cin.clear();
        char badChar = ' ';
        do { badChar = (char)std::cin.get(); } while(badChar != '\n');
    }
    if(numTestsToRun < 0) numTestsToRun = 9999;

    if(numTestsToRun > 0) {
        int listType;
        while(true) {
            std::cout << "Which list type do you wish to test? 1 - Array 2 - LinkedList: ";
            std::cin >> listType;
            if(!std::cin.fail()) break;

            std::cin.clear();
            char badChar = ' ';
            do { badChar = (char)std::cin.get(); } while(badChar != '\n');
        }
        if(listType != 1 && listType != 2) {
            std::cout << "Unknown list type chosen, defaulting to Array implementation" << std::endl;
            listType = 1;
        }

        std::cout << "Testing your list functions..." << std::endl << std::endl;
        if( run_all_tests(numTestsToRun, listType) ) {
            std::cout << "ALL TESTS PASSED!" << std::endl;
        } else {
            std::cout << "Not all tests are passing, errors remain..." << std::endl;
        }
    }

    std::cout << std::endl << "Running stress tests..." << std::endl;
    run_stress_tests();
    std::cout << "...stress tests complete" << std::endl;

    return 0;
}