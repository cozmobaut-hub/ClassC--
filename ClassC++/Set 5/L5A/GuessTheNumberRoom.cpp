#include "GuessTheNumberRoom.h"
#include <iostream>
#include <cstdlib>
using namespace std;

GuessTheNumberRoom::GuessTheNumberRoom() {
    cout << "GuessTheNumberRoom() called" << endl;
    mRoomName = "Guess The Number Room";
    mSecretNumber = (rand() % 20) + 1;
}

GuessTheNumberRoom::~GuessTheNumberRoom() {
    cout << "~GuessTheNumberRoom() called" << endl;
}

bool GuessTheNumberRoom::escapeTheRoom() {
    int guessesMade = 0;
    int guess = 0;

    while (guessesMade < 5) {
        cout << "Enter your guess: ";
        cin >> guess;
        guessesMade++;

        if (guess < mSecretNumber) {
            cout << "Too low!" << endl;
        } else if (guess > mSecretNumber) {
            cout << "Too high!" << endl;
        } else {
            cout << "Correct! You escaped!" << endl;
            return true;
        }
    }

    cout << "You failed to guess the number." << endl;
    return false;
}