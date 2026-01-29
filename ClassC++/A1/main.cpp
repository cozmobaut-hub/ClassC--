/* CSCI 200: Assignment 1: A1 - Let's Make A Deal
 *
 * Author: Austin Haas 
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // No outside resources were used other than whats available on the course website
 *
 * XXXXXXXX (MORE_COMPLETE_DESCRIPTION_HERE)
 */
// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.
#include <random>
// We will (most of the time) use the standard library namespace in our programs.
using namespace std;
// Define any constants below this comment.
const int NUM_DOORS = 3;
// Must have a function named "main", which is the starting point of a C++ program.
int main() {
     /******** INSERT YOUR CODE BELOW HERE ********/
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, NUM_DOORS);

    char play;

    do {
        int carDoor = dist(mt);
        int userChoice; 
        do {
        cout << "Choose a door (1, 2, or 3): ";
        cin >> userChoice;
        } while (userChoice < 1 || userChoice > NUM_DOORS || !cin);

        int revealedDoor;
        if (userChoice == carDoor) {
            do {
                revealedDoor = dist(mt);
            } while (revealedDoor == userChoice);
        } else {
            revealedDoor = 6 - userChoice - carDoor;
        }
        cout << "Door #" << revealedDoor << " contains a goat." << endl;    

        char switchChoice;
        do {
            cout << "Do you wish to change doors, Y or N: ";
            cin >> switchChoice;
            switchChoice = toupper(switchChoice);
        } while (switchChoice != 'Y' && switchChoice != 'N');   
    
        int final;

        if (switchChoice == 'Y') {
            final = 6 - userChoice - revealedDoor;
        } else {
            final = userChoice;
        }

        cout << "Behind your Door #" << final << " is a ";
        if (final == carDoor) {
            cout << "CAR!" << endl << "Good job ";;
            if (switchChoice == 'Y') {
                cout << "switching";
            } else {
                cout << "not switching";
            }
            cout << " doors!" << endl;
        } else {
            cout << "goat" << endl;
            if (switchChoice == 'Y') {
                cout << "You shouldn't have switched doors." << endl;
            } else {
                cout << "You should have switched doors." << endl;
            }
        }

        do {
            cout << "Do you wish to play again, Y or N: ";
            cin >> play;
            play = toupper(play);
        } while (play != 'Y' && play != 'N');

    } while (play == 'Y' || play == 'y');

    unsigned int trials;
    do {
        cout << "How many trials do you wish to run: ";
        cin >> trials;
    } while (trials < 1); 

    unsigned int stayWins = 0;
    unsigned int switchWins = 0;

    for (unsigned int i = 0; i < trials; ++i) {
        int carDoor = dist(mt);
        int userChoice = dist(mt);

        int revealedDoor;
        if (userChoice == carDoor) {
            do {
                revealedDoor = dist(mt);
            } while (revealedDoor == userChoice);
        } else {
            revealedDoor = 6 - userChoice - carDoor;
        }

        int stayFinal = userChoice;
        int switchFinal = 6 - userChoice - revealedDoor;

        if (stayFinal == carDoor) {
            ++stayWins;
        }
        if (switchFinal == carDoor) {
            ++switchWins;
        }
    }

    cout << "Out of " << trials << " trials:" << endl;
    cout << "Stay " << stayWins << "      " << (stayWins * 100.0 / trials) << "%"<< endl;
    cout << "Switch " << switchWins << "    " << (switchWins * 100.0 / trials) << "%"<< endl;

     /******** INSERT YOUR CODE ABOVE HERE ********/
    return 0; // signals the operating system that our program ended OK.
}
