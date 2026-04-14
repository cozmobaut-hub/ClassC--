#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP


#include "List.hpp"


#include <exception>
#include <iostream>
#include <string>


template<typename T>
class LinkedList final : public IList<T> {
public:
    LinkedList();
    ~LinkedList();


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
    struct Node {
        T value;
        Node* pNext;
        Node* pPrev;
    };


    Node* _pHead;
    Node* _pTail;
    int _size;
};


//---------------------------------------------------------


template<typename T>
LinkedList<T>::LinkedList() {
  // set size to zero
  _size = 0;

  // set head to be a nullptr
  _pHead = nullptr;
  
  // set tail to be a nullptr
  _pTail = nullptr;
}


template<typename T>
LinkedList<T>::~LinkedList() {
    // remove each node in the list
    Node* current = _pHead;
    while (current != nullptr) {
        Node* next = current->pNext;
        delete current;
        current = next;
    }
    _pHead = nullptr;
    _pTail = nullptr;
    _size = 0;
}


template<typename T>
int LinkedList<T>::size() const {
    return _size;
}


template<typename T>
T LinkedList<T>::get(const int POS) const {
    // if POS is out of range, throw std::out_of_range exception
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("LinkedList::get position out of range");
    }

    // set current node to head
    Node* current = _pHead;
    
    // advance current node to POS
    for (int i = 0; i < POS; ++i) {
        current = current->pNext;
    }
    
    // return value of current node
    return current->value;
}


template<typename T>
void LinkedList<T>::set(const int POS, const T VALUE) {
  // if POS is out of range, throw std::out_of_range exception
  if (POS < 0 || POS >= _size) {
      throw std::out_of_range("LinkedList::set position out of range");
  }

  // set current node to head
  Node* current = _pHead;

  // advance current node to POS
  for (int i = 0; i < POS; ++i) {
      current = current->pNext;
  }

  // set value of current node   
  current->value = VALUE;
}


template<typename T>
void LinkedList<T>::insert(const int POS_IN, const T VALUE) {
    int POS = POS_IN;

    // if POS is before zero, clamp to zero
    if (POS < 0) {
        POS = 0;
    }
    
    // if POS is after size, clamp to size
    if (POS > _size) {
        POS = _size;
    }
    
    // create pointer to new node
    Node* pNew = new Node;

    // set value to be VALUE
    pNew->value = VALUE;
    
    // set previous pointer to nullptr
    pNew->pPrev = nullptr;
    
    // set next pointer to nullptr
    pNew->pNext = nullptr;
    
    // if list is currently empty
    if (_size == 0) {
        // set head and tail to new node
        _pHead = pNew;
        _pTail = pNew;
    }
    // otherwise
    else {
        // if position is before head
        if (POS == 0) {
            // set new node next to be head
            pNew->pNext = _pHead;
            // set head previous to be new node
            _pHead->pPrev = pNew;
            // set head to be new ndoe
            _pHead = pNew;
        }
        // else if position is after tail
        else if (POS == _size) {
            // set new node previous to be tail
            pNew->pPrev = _pTail;
            // set tail next to be new node
            _pTail->pNext = pNew;
            // set tail to be new ndoe
            _pTail = pNew;
        }
        // otherwise
        else {
            // set current node to head
            Node* current = _pHead;
            // advance current node to pos
            for (int i = 0; i < POS; ++i) {
                current = current->pNext;
            }

            // link new node into current list
            pNew->pNext = current;
            pNew->pPrev = current->pPrev;

            // link current list to new node
            current->pPrev->pNext = pNew;
            current->pPrev = pNew;
        }
    }
    
    // increment size
    ++_size;
}


template<typename T>
void LinkedList<T>::remove(const int POS_IN) {
    // if array is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("LinkedList::remove on empty list");
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
    
    Node* pDelete = nullptr;

    // if list has one element
    if (_size == 1) {
        // set node to delete to head
        pDelete = _pHead;
        // set head and tail to be nullptr
        _pHead = nullptr;
        _pTail = nullptr;
    }
    // otherwise
    else {
        // if deleting head
        if (POS == 0) {
            // set node to delete to head
            pDelete = _pHead;
            // advance head to next
            _pHead = _pHead->pNext;
            // set head previous to nullptr
            _pHead->pPrev = nullptr;
        }
        // else if deleting tail
        else if (POS == _size - 1) {
            // set node to delete to tail
            pDelete = _pTail;
            // step tail to previous
            _pTail = _pTail->pPrev;
            // set tail next to nullptr
            _pTail->pNext = nullptr;
        }
        // otherwise
        else {
            // set current node to head
            Node* current = _pHead;
            // advance current node to space before position
            for (int i = 0; i < POS - 1; ++i) {
                current = current->pNext;
            }
            // set node to delete to the current node's next node
            pDelete = current->pNext;
            // unlink node to delete
            current->pNext = pDelete->pNext;
            pDelete->pNext->pPrev = current;
        }
    }
    
    // delete node
    delete pDelete;
    
    // decrement size
    --_size;
}


template<typename T>
T LinkedList<T>::min() const {
    // if list is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("LinkedList::min on empty list");
    }
    
    // find minimum value within list
    Node* current = _pHead;
    T currentMin = current->value;
    current = current->pNext;
    while (current != nullptr) {
        if (current->value < currentMin) {
            currentMin = current->value;
        }
        current = current->pNext;
    }
    
    // return min value
    return currentMin;
}


template<typename T>
T LinkedList<T>::max() const {
    // if list is empty, throw std::out_of_range exception
    if (_size == 0) {
        throw std::out_of_range("LinkedList::max on empty list");
    }
    
    // find maxiumum value within list
    Node* current = _pHead;
    T currentMax = current->value;
    current = current->pNext;
    while (current != nullptr) {
        if (current->value > currentMax) {
            currentMax = current->value;
        }
        current = current->pNext;
    }
    
    // return max value
    return currentMax;
}


template<typename T>
int LinkedList<T>::find(const T VALUE) const {
    // search for first occurrence of VALUE
    // hint: start at the beginning and go forward
    Node* current = _pHead;
    int index = 0;
    while (current != nullptr) {
        if (current->value == VALUE) {
            // return index of first occurrence if found
            return index;
        }
        current = current->pNext;
        ++index;
    }
    
    // otherwise return -1
    return -1;
}


template<typename T>
int LinkedList<T>::rfind(const T VALUE) const {
    // search for last occurrence of VALUE
    // hint: start at the end and go backward
    Node* current = _pTail;
    int index = _size - 1;
    while (current != nullptr) {
        if (current->value == VALUE) {
            // return index of last occurrence if found
            return index;
        }
        current = current->pPrev;
        --index;
    }

    // otherwise return -1
    return -1;
}


#endif//LINKED_LIST_HPP