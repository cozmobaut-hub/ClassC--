#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Box.h"
#include <ostream>
#include <vector>

/**
 * @brief takes in sized things and puts them into boxes.  stores
 * all the boxes internally
 * 
 */
class Warehouse {
public:
    /**
     * @brief Construct a new Warehouse object with
     * no boxes by default
     * 
     */
    Warehouse();
    
    /**
     * @brief Copy constructor - deep copy
     */
    Warehouse(const Warehouse& other);
    
    /**
     * @brief Copy assignment operator - deep copy
     */
    Warehouse& operator=(const Warehouse& other);
    
    /**
     * @brief Destructor - deep cleanup
     */
    ~Warehouse();
    
    /**
     * @brief puts the item into a Box of given size
     * @param SIZE size of the cube shaped box to store
     */
    void storeInBox(const int SIZE);
    
    /**
     * @brief Get the Box object at given position within the list
     * @param BOX_POS position within the list to retrieve
     * @return Box* pointer to the corresponding Box object
     */
    Box* getBox(const size_t BOX_POS) const;
    
    /**
     * @brief Get the number Of box objects
     * @return size_t number of boxes
     */
    size_t getNumberOfBoxes() const;
    
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
     * @brief holds a list of pointers to Boxes
     * 
     */
    std::vector<Box*>* _pBoxen;
    
    /**
     * @brief Warehouse letter identifier
     */
    char _warehouseLetter;
    
    // Private helper methods
    void deallocate();
    void deepCopy(const Warehouse& other);
};

std::ostream& operator<<(std::ostream&, const Warehouse&);

#endif//WAREHOUSE_H
