#include <iostream>

// Assuming Stack and Node are implemented as per UML
class RockCairn {
private:
    Stack cairn;

public:
    // Constructor
    RockCairn() {}

    // push: returns true if pushed, false if not
    bool push(int val) {
        // If stack is empty, always push the first rock
        if (cairn.size() == 0) {
            cairn.push(val);
            return true;
        }

        // Only push if the new value is smaller than the current top
        if (val < cairn.peek()) {
            cairn.push(val);
            return true;
        }

        return false;
    }

    // pop: removes and returns the top value
    int pop() {
        return cairn.pop();
    }

    // size: returns the current height of the cairn
    int size() {
        return cairn.size();
    }
};
