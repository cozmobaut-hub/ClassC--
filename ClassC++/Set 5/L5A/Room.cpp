#include "Room.h"

#include <iostream>
using namespace std;

ARoom::ARoom() {
    cout << "ARoom() called" << endl;
    mRoomName = "Vacant Room";
}

ARoom::~ARoom() {
    cout << "~ARoom() called" << endl;
}

string ARoom::getRoomName() const {
    return mRoomName;
}