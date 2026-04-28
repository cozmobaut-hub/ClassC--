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
    
    // NEW METHODS
    void sort() override;
    int search(const T VALUE) const override;

private:
    int _size;
    T* _pArray;
    
    // Helper methods for merge sort
    void mergeSort(int left, int right);
    void merge(int left, int mid, int right);
};

//---------------------------------------------------------

template<typename T>
Array<T>::Array() {
    _size = 0;
    _pArray = nullptr;
}

template<typename T>
Array<T>::~Array() {
    delete[] _pArray;
    _pArray = nullptr;
}

template<typename T>
int Array<T>::size() const { 
    return _size;
}

template<typename T>
T Array<T>::get(const int POS) const {
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("Array::get position out of range");
    }
    return _pArray[POS];
}

template<typename T>
void Array<T>::set(const int POS, const T VALUE) {
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("Array::set position out of range");
    }
    _pArray[POS] = VALUE;
}

template<typename T>
void Array<T>::insert(const int POS_IN, const T VALUE) {
    int POS = POS_IN;
    if (POS < 0) {
        POS = 0;
    }
    if (POS > _size) {
        POS = _size;
    }
    T* pNewArray = new T[_size + 1];
    for (int i = 0; i < POS; ++i) {
        pNewArray[i] = _pArray[i];
    }
    pNewArray[POS] = VALUE;
    for (int i = POS; i < _size; ++i) {
        pNewArray[i + 1] = _pArray[i];
    }
    delete[] _pArray;
    _pArray = pNewArray;
    ++_size;
}

template<typename T>
void Array<T>::remove(const int POS_IN) {
    if (_size == 0) {
        throw std::out_of_range("Array::remove on empty array");
    }
    int POS = POS_IN;
    if (POS < 0) {
        POS = 0;
    }
    if (POS >= _size) {
        POS = _size - 1;
    }
    T* pNewArray = nullptr;
    if (_size - 1 > 0) {
        pNewArray = new T[_size - 1];
    }
    for (int i = 0; i < POS; ++i) {
        pNewArray[i] = _pArray[i];
    }
    for (int i = POS + 1; i < _size; ++i) {
        pNewArray[i - 1] = _pArray[i];
    }
    delete[] _pArray;
    _pArray = pNewArray;
    --_size;
}

template<typename T>
T Array<T>::min() const {
    if (_size == 0) {
        throw std::out_of_range("Array::min on empty array");
    }
    T currentMin = _pArray[0];
    for (int i = 1; i < _size; ++i) {
        if (_pArray[i] < currentMin) {
            currentMin = _pArray[i];
        }
    }
    return currentMin;
}

template<typename T>
T Array<T>::max() const {
    if (_size == 0) {
        throw std::out_of_range("Array::max on empty array");
    }
    T currentMax = _pArray[0];
    for (int i = 1; i < _size; ++i) {
        if (_pArray[i] > currentMax) {
            currentMax = _pArray[i];
        }
    }
    return currentMax;
}

template<typename T>
int Array<T>::find(const T VALUE) const {
    for (int i = 0; i < _size; ++i) {
        if (_pArray[i] == VALUE) {
            return i;
        }
    }
    return -1;
}

template<typename T>
int Array<T>::rfind(const T VALUE) const {
    for (int i = _size - 1; i >= 0; --i) {
        if (_pArray[i] == VALUE) {
            return i;
        }
    }
    return -1;
}

// ============== NEW METHODS ==============

template<typename T>
void Array<T>::sort() {
    if (_size > 1) {
        mergeSort(0, _size - 1);
    }
}

template<typename T>
void Array<T>::mergeSort(int left, int right) {
    if (left >= right) {
        return;
    }
    
    int mid = left + (right - left) / 2;
    
    mergeSort(left, mid);
    mergeSort(mid + 1, right);
    merge(left, mid, right);
}

template<typename T>
void Array<T>::merge(int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    
    T* leftArray = new T[leftSize];
    T* rightArray = new T[rightSize];
    
    for (int i = 0; i < leftSize; ++i) {
        leftArray[i] = _pArray[left + i];
    }
    for (int i = 0; i < rightSize; ++i) {
        rightArray[i] = _pArray[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            _pArray[k] = leftArray[i];
            ++i;
        } else {
            _pArray[k] = rightArray[j];
            ++j;
        }
        ++k;
    }
    
    while (i < leftSize) {
        _pArray[k] = leftArray[i];
        ++i;
        ++k;
    }
    
    while (j < rightSize) {
        _pArray[k] = rightArray[j];
        ++j;
        ++k;
    }
    
    delete[] leftArray;
    delete[] rightArray;
}

template<typename T>
int Array<T>::search(const T VALUE) const {
    if (_size == 0) {
        return -1;
    }
    
    int left = 0;
    int right = _size - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (_pArray[mid] == VALUE) {
            result = mid;
            right = mid - 1;
        } else if (_pArray[mid] < VALUE) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

#endif//ARRAY_HPP