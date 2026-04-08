#ifndef EXITROOM_H
#define EXITROOM_H

#include "Room.h"

class ExitRoom : public ARoom {
public:
    ExitRoom();
    virtual ~ExitRoom();

    bool escapeTheRoom() override;
};

#endif // EXITROOM_H