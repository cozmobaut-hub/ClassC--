#ifndef WAREHOUSE_HPP
#define WAREHOUSE_HPP

#include "Box.hpp"
#include <vector>
#include <ostream>

/**
 * @brief takes in things and puts them into a list.  stores all the items internally
 */
template<typename T>
class Warehouse {
public:
    /**
     * @brief Construct a new Warehouse object with no items by default
     */
    Warehouse();

    /**
     * @brief Don't allow a Warehouse to be copied
     */
    Warehouse(const Warehouse<T>&) = delete;

    /**
     * @brief Don't allow a Warehouse to be copied
     */
    Warehouse<T>& operator=(const Warehouse<T>&) = delete;

    /**
     * @brief Destroy the Warehouse object
     */
    ~Warehouse();

    /**
     * @brief puts the item into the warehouse
     * @param ITEM item to store
     */
    void store(const T& ITEM);

    /**
     * @brief Get the item at given position within the warehouse
     * @param ITEM_POS position to retrieve
     * @return T& corresponding item
     */
    T& retrieve(const size_t ITEM_POS) const;

    /**
     * @brief Get the Number Of items
     * @return size_t 
     */
    size_t getNumberOfItems() const;

    /**
     * @brief retrieves the warehouse letter identifier
     * @return char warehouse letter identifier
     */
    char getWarehouseLetter() const;

    /**
     * @brief sets the warehouse letter identifier
     * @param warehouseLetter letter to identify warehouse by
     */
    void setWarehouseLetter(char warehouseLetter);

private:
    /**
     * @brief holds a list of items
     */
    std::vector<T>* _pItems;

    /**
     * @brief Warehouse letter identifier
     */
    char _warehouseLetter;
};

template<typename T>
Warehouse<T>::Warehouse() {
    _pItems = new std::vector<T>;
}

template<typename T>
Warehouse<T>::~Warehouse() {
    delete _pItems;
}

template<typename T>
void Warehouse<T>::store(const T& ITEM) {
    _pItems->push_back(ITEM);
}

template<typename T>
T& Warehouse<T>::retrieve(const size_t ITEM_POS) const {
    return _pItems->at(ITEM_POS);
}

template<typename T>
size_t Warehouse<T>::getNumberOfItems() const {
    return _pItems->size();
}

template<typename T>
char Warehouse<T>::getWarehouseLetter() const {
    return _warehouseLetter;
}

template<typename T>
void Warehouse<T>::setWarehouseLetter(char warehouseLetter) {
    _warehouseLetter = warehouseLetter;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Warehouse<T>& WH) {
    const size_t NUM_ITEMS = WH.getNumberOfItems();
    os << "Warehouse " << WH.getWarehouseLetter()
       << " has " << NUM_ITEMS << " items (";
    for (size_t i = 0; i < NUM_ITEMS; ++i) {
        os << WH.retrieve(i);
        if (i + 1 < NUM_ITEMS) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

#endif // WAREHOUSE_HPP
