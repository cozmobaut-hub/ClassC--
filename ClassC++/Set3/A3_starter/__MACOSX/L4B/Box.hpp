#ifndef BOX_HPP
#define BOX_HPP

#include <ostream>

/**
 * @brief Stores the size/value of a Box
 */
template<typename T>
class Box {
public:
    /**
     * @brief Construct a new Box object
     * default-initialized value
     */
    Box(); // default constructor

    /**
     * @brief Construct a new Box object
     * for given value
     *
     * @param VALUE value of the Box
     */
    Box(const T& VALUE); // parameterized constructor

    /**
     * @brief Get the value stored in the Box
     *
     * @return T current Box value
     */
    T getBoxSize() const; // accessor - getter

    /**
     * @brief Set the value in the Box
     *
     * @param VALUE value to set on Box
     */
    void setBoxSize(const T& VALUE); // mutator - setter

private:
    /**
     * @brief current Box value
     */
    T _size;
};

template<typename T>
Box<T>::Box() {
    // default-initialized T
    _size = T();
}

template<typename T>
Box<T>::Box(const T& VALUE) {
    _size = VALUE;
}

template<typename T>
T Box<T>::getBoxSize() const {
    return _size;
}

template<typename T>
void Box<T>::setBoxSize(const T& VALUE) {
    _size = VALUE;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Box<T>& BOX) {
    os << BOX.getBoxSize();
    return os;
}

#endif // BOX_HPP
