#ifndef LIST_HPP
#define LIST_HPP

template<typename T>
class IList {
public:
    virtual ~IList() = default;

    /**
     * @brief returns the current size of the list
     * 
     * @return int list size
     */
    virtual int size() const = 0;

    /**
     * @brief returns the value of the list at a given position
     * 
     * @param POS position to retrieve value from
     * @return T value at position
     * @throws std::out_of_range if POS is out of range or list is empty
     */
    virtual T get(const int POS) const = 0;

    /**
     * @brief sets the value of the list at a given position
     * 
     * @param POS position to set value at
     * @param VALUE value to set
     * @throws std::out_of_range if POS is out of range or list is empty
     */
    virtual void set(const int POS, const T VALUE) = 0;

    /**
     * @brief inserts an element with provided value before the current element at the 
     * provided position.  upon completion, new element will exist at the provided
     * position with all elements after the position shifted over one position
     * 
     * @param POS current position to insert in front of
     * @param VALUE value to insert
     * @note if POS is out of range, POS will be clamped to head/tail as appropriate
     */
    virtual void insert(const int POS, const T VALUE) = 0;

    /**
     * @brief removes the element at the provided position.  upon completion, all elements after
     * the position will be shifted over one position
     * 
     * @param POS current position to remove
     * @throws std::out_of_range if list is empty
     * @note if POS is out of range, POS will be clamped to head/tail as appropriate
     */
    virtual void remove(const int POS) = 0;

    /**
     * @brief returns the smallest value in the list
     * 
     * @return T smallest value
     * @throws std::out_of_range if list is empty
     */
    virtual T min() const = 0;

    /**
     * @brief returns the largest value in the list
     * 
     * @return T largest value
     * @throws std::out_of_range if list is empty
     */
    virtual T max() const = 0;

    /**
     * @brief returns first occurrence of target value in the list.  if target is
     * not present in the list, returns -1
     * 
     * @param VALUE target value to search for
     * @return int 
     */
    virtual int find(const T VALUE) const = 0;

    /**
     * @brief returns last occurrence of target value in the list.  if target is
     * not present in the list, returns -1
     *
     * @param VALUE target value to search for
     * @return int
     */
    virtual int rfind(const T VALUE) const = 0;
};

#endif//LIST_HPP