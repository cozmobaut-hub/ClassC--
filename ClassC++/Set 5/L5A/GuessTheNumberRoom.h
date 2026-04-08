#ifndef GUESSTHENUMBERROOM_H
#define GUESSTHENUMBERROOM_H

#include "Room.h"

class GuessTheNumberRoom : public ARoom {
public:
    GuessTheNumberRoom();
    virtual ~GuessTheNumberRoom();

    bool escapeTheRoom() override;

private:
    int mSecretNumber;
};

#endif // GUESSTHENUMBERROOM_H