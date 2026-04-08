#ifndef ROOM_H
#define ROOM_H

#include <string>

class ARoom {
public:
    /**
     * @brief Construct a new ARoom object
     */
    ARoom();

    /**
     * @brief Destroy the ARoom object
     */
    virtual ~ARoom();

    /**
     * @brief Get the Room Name object
     *
     * @return std::string name of the room
     */
    std::string getRoomName() const;

    /**
     * @brief attempts to get out of the room
     *
     * @return true if the room has been escaped from
     * @return false if you are still trapped in the room
     */
    virtual bool escapeTheRoom() = 0;

protected:
    /**
     * @brief name of the room
     */
    std::string mRoomName;

private:

};

#endif // ROOM_H