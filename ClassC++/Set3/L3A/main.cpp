/*
 * CSCI 200 – Spring 2026
 * Lab 3A – Secret Moosage
 * Author: Austin Haas
 * Date:   02/16/2026
 *
 * Description: Simple secret message decipherer from my weirdass txt file.
 */


#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // open input
    ifstream secretMessage("secretMessage.txt");
    if (secretMessage.fail()) {
        cerr << "Error opening input file" << endl;
        return -1;
    }

    // open output
    ofstream decipheredMessage("decipheredMessage.txt");
    if (decipheredMessage.fail()) {
        cerr << "Error opening output file" << endl;
        return -1;
    }

    char c;
    // read one character at a time (including whitespace)
    while (secretMessage.get(c)) {
        if (c == '\n') {
            decipheredMessage << '\n';
        } else if (c == '~') {
            decipheredMessage << ' ';
        } else {
            decipheredMessage << static_cast<char>(c + 1);
        }
    }

    secretMessage.close();
    decipheredMessage.close();

    return 0;
}
