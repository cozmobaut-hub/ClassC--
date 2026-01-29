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
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, NUM_DOORS);
    
    char play;
    
    do {
        int car = dist(gen);
        int choice;
        
        
        do {
            cout << "Choose a door 1, 2, or 3: ";
            cin >> choice;
        } while (choice < 1 || choice > NUM_DOORS || !cin);
        

        int goat;
        if (choice == car) {
            do goat = dist(gen); while (goat == choice);
        } else {
            goat = 6 - choice - car;  
        }
        cout << "Door #" << goat << " contains a goat." << endl;
        
        
        char sw;
        do {
            cout << "Do you wish to change doors, Y or N: ";
            cin >> sw;
            sw = toupper(sw);
        } while (sw != 'Y' && sw != 'N');
        
        
        int final = (sw == 'Y') ? (6 - choice - goat) : choice;
        
        
        cout << "Behind your Door #" << final << " is a ";
        if (final == car) {
            cout << "CAR!" << endl << "Good job ";
            (sw == 'Y') ? cout << "switching" : cout << "not switching";
            cout << " doors!" << endl;
        } else {
            cout << "goat" << endl;
            (sw == 'Y') ? cout << "You shouldn't have switched doors." : cout << "You should have switched doors.";
            cout << endl;
        }
        
        
        do {
            cout << "Do you wish to play again, Y or N: ";
            cin >> play;
            play = toupper(play);
        } while (play != 'Y' && play != 'N');
        
    } while (play == 'Y');
    
    
    int trials;
    do {
        cout << "How many trials do you wish to run: ";
        cin >> trials;
    } while (trials < 1);
    
    int stay = 0, swtch = 0;
    for (int i = 0; i < trials; i++) {
        int car = dist(gen);
        int choice = dist(gen);
        int goat = (choice == car) ? dist(gen) : (6 - choice - car);
        int other = 6 - choice - goat;
        if (choice == car) stay++;
        if (other == car) swtch++;
    }
    
    double pstay = stay * 100.0 / trials;
    double psw = swtch * 100.0 / trials;
    
    cout << trials << " Trials:" << endl;
    cout << "Stay:   " << stay << "       " << pstay << "%" << endl;
    cout << "Switch: " << swtch << "       " << psw << "%" << endl;
     /******** INSERT YOUR CODE ABOVE HERE ********/
    return 0; // signals the operating system that our program ended OK.
}
