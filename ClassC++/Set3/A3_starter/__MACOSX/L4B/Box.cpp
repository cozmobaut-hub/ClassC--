#include "Box.h"

Box::Box() {
    // initialize to unit cube by default
    _size = 1.0;
}

Box::Box(const double SIZE) {
    // if desired size is positive, assign
    if(SIZE > 0) _size = SIZE;
    // otherwise default to one
    else _size = 1.0;
}

double Box::getBoxSize() const {
    return _size;
}
void Box::setBoxSize(const double SIZE) {
    // if desired size is positive, assign
    if(SIZE > 0) _size = SIZE;
}

std::ostream& operator<<(std::ostream& os, const Box& BOX) {
    os << BOX.getBoxSize();
    return os;
}