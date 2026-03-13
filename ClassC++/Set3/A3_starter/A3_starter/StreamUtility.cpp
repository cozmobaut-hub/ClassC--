#include "StreamUtility.h"
#include <fstream>
#include <string>

std::istream* StreamUtility::selectInput() {
    while (true) {
        std::cout << "Select input source:\n"
                  << "\t(1) - Standard Input\n"
                  << "\t(2) - File Input\n"
                  << "Choice: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::cin.ignore(10000, '\n');
            std::cout << "Enter text to analyze (\"ENDEND\" will cease input): ";
            return &std::cin;
        } else if (choice == 2) {
            std::string filename;
            std::cout << "Enter the name of the file to read from: ";
            std::cin >> filename;
            std::ifstream* inFile = new std::ifstream(filename.c_str());
            if (!inFile->is_open()) {
                delete inFile;
                return nullptr;
            }
            return inFile;
        } else {
            // loop again and reprint menu
        }
    }
}

std::ostream* StreamUtility::selectOutput() {
    while (true) {
        std::cout << "Select output destination:\n"
                  << "\t(1) - Standard Output\n"
                  << "\t(2) - File Output\n"
                  << "Choice: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            return &std::cout;
        } else if (choice == 2) {
            std::string filename;
            std::cout << "Enter the name of the file to write to: ";
            std::cin >> filename;
            std::ofstream* outFile = new std::ofstream(filename.c_str());
            if (!outFile->is_open()) {
                delete outFile;
                return nullptr;
            }
            return outFile;
        } else {
            // loop again and reprint menu
        }
    }
}
