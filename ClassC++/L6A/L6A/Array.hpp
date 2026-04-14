#ifndef ARRAY_HPP
#define ARRAY_HPP


#include "List.hpp"


#include <exception>
#include <iostream>
#include <string>


template<typename T>
class Array final : public IList<T> {
public:
    Array();
    ~Array();


    int size() const override;
    T get(const int POS) const override;
    void set(const int POS, const T VALUE) override;
    void insert(const int POS, const T VALUE) override;
    void remove(const int POS) override;
    T min() const override;
    T max() const override;
    int find(const T VALUE) const override;
    int rfind(const T VALUE) const override;


private:
    int _size;
    T* _pArray;
};


//---------------------------------------------------------


template<typename T>
Array<T>::Array() {
    // set size to zero
    _size = 0;

    // set array to be a nullptr
    _pArray = nullptr;
}


template<typename T>
Array<T>::~Array() {
    // deallocate current array
    delete[] _pArray;
    _pArray = nullptr;
}


template<typename T>
int Array<T>::size() const { 
    return _size;
}


template<typename T>
T Array<T>::get(const int POS) const {
    // if POS is out of range, throw std::out_of_range exception
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("Array::get position out of range");
    }

    // return value at POS within array
    return _pArray[POS];
}


template<typename T>
void Array<T>::set(const int POS, const T VALUE) {
    // if POS is out of range, throw std::out_of_range exception
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("Array::set position out of range");
    }

    // set VALUE at POS within array    
    _pArray[POS] = VALUE;
}


template<typename T>
void Array<T>::insert(const int POS_IN, const T VALUE) {
    int POS = POS_IN;

    // if POS is before zero, clamp to zero
    if (POS < 0) {
        POS = 0;
    }

    // if POS is after size, clamp to size
    if (POS > _size) {
        POS = _size;
    }

    // create new array of size + 1
    T* pNewArray = new T[_size + 1];

    // copy elements 0 to POS from old array to new array
    for (int i = 0; i < POS; ++i) {
        pNewArray[i] = _pArray[i];
    }

    // set element at POS in new array to VALUE
    pNewArray[POS] = VALUE;

    // copy elements POS to size from old array to new array
    for (int i = POS; i < _size; ++i) {
        pNewArray[i + 1] = _pArray[i];
    }

    // delete old array
    delete[] _pArray;

    // set old array to be new array
    _pArray = pNewArray;

    // increment size
    ++_size;
}


template<typename T>
void Array<T>::remove(const int POS_IN) {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("Array::remove on empty array");
    }

    int POS = POS_IN;

    // if POS is before zero, clamp to zero
    if (POS < 0) {
        POS = 0;
    }

    // if POS is after size, clamp to size
    if (POS >= _size) {
        POS = _size - 1;
    }

    // create new array of size - 1
    T* pNewArray = nullptr;
    if (_size - 1 > 0) {
        pNewArray = new T[_size - 1];
    }

    // copy elements from 0 to POS from old array to  new array
    for (int i = 0; i < POS; ++i) {
        pNewArray[i] = _pArray[i];
    }

    // copy elements from POS+1 to size from old array to new array
    for (int i = POS + 1; i < _size; ++i) {
        pNewArray[i - 1] = _pArray[i];
    }

    // delete old array
    delete[] _pArray;

    // set old array to be new array
    _pArray = pNewArray;

    // decrement size
    --_size;
}


template<typename T>
T Array<T>::min() const {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("Array::min on empty array");
    }

    // find minimum value within array
    T currentMin = _pArray[0];
    for (int i = 1; i < _size; ++i) {
        if (_pArray[i] < currentMin) {
            currentMin = _pArray[i];
        }
    }

    // return min value
    return currentMin;
}


template<typename T>
T Array<T>::max() const {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("Array::max on empty array");
    }

    // find maximum value within array
    T currentMax = _pArray[0];
    for (int i = 1; i < _size; ++i) {
        if (_pArray[i] > currentMax) {
            currentMax = _pArray[i];
        }
    }

    // return max value
    return currentMax;
}


template<typename T>
int Array<T>::find(const T VALUE) const {
    // search for first occurrence of VALUE
    // hint: start at the beginning and go forward
    for (int i = 0; i < _size; ++i) {
        if (_pArray[i] == VALUE) {
            // return index of first occurrence if found
            return i;
        }
    }

    // otherwise return -1
    return -1;
}


template<typename T>
int Array<T>::rfind(const T VALUE) const {
    // search for last occurrence of VALUE
    // hint: start at the end and go backward
    for (int i = _size - 1; i >= 0; --i) {
        if (_pArray[i] == VALUE) {
            // return index of last occurrence if found
            return i;
        }
    }

    // otherwise return -1
    return -1;
}


#endif//ARRAY_HPP