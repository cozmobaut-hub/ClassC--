#include "GuessTheNumberRoom.h"
#include "ExitRoom.h"

#include <iostream>
#include <random>
using namespace std;


ARoom* go_to_next_room(int randRoomChoice) {
    switch (randRoomChoice) {
    case 7:
        // 10% chance: Exit Room
        return new ExitRoom();
    default:
        // 90% chance: Guess The Number Room
        return new GuessTheNumberRoom();
    }
}

int main() {
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(1, 10);

    
    ARoom* currentRoom = 0;

    do {
        
        if (currentRoom != 0) {
            delete currentRoom;
            currentRoom = 0;
        }

        // Get the next room
        currentRoom = go_to_next_room(dist(mt));

        cout << "Welcome to the " << currentRoom->getRoomName() << endl;
    } while (!currentRoom->escapeTheRoom());

    cout << "You made it out!" << endl;

    // Clean up the last room
    delete currentRoom;
    currentRoom = 0;

    return 0;
}