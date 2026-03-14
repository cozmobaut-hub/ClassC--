#ifndef BOX_HPP
#define BOX_HPP

#include <ostream>

/**
 * @brief Stores the size of a Box
 * 
 */
class Box {
public:
    /**
     * @brief Construct a new Box object
     * of unit dimensions
     * 
     */
    Box(); // default constructor
    
    /**
     * @brief Construct a new Box object
     * for given dimension.  If dimension
     * is not positive, defaults dimension to 1
     * 
     * @param SIZE size of the Box
     */
    Box(const double SIZE); // parameterized constructor

    /**
     * @brief Get the Size of the Box
     * 
     * @return double current Box size
     */
    double getBoxSize() const; // accessor - getter

    /**
     * @brief Set the Size only
     * if positive
     * 
     * @param SIZE size to set on Box
     */
    void setBoxSize(const double SIZE); // mutator - setter

private:
    /**
     * @brief current Box size
     * 
     */
    double _size;
};

std::ostream& operator<<(std::ostream& os, const Box& BOX);

inline Box::Box() {
    _size = 1.0;
}

inline Box::Box(const double SIZE) {
    if (SIZE > 0) _size = SIZE;
    else _size = 1.0;
}

inline double Box::getBoxSize() const {
    return _size;
}

inline void Box::setBoxSize(const double SIZE) {
    if (SIZE > 0) _size = SIZE;
}

inline std::ostream& operator<<(std::ostream& os, const Box& BOX) {
    os << BOX.getBoxSize();
    return os;
}

#endif // BOX_HPP
