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
    
    // NEW METHODS
    void sort() override;
    int search(const T VALUE) const override;

private: 
    struct Node {
        T value;
        Node* pNext;
        Node* pPrev;
    };

    Node* _pHead;
    Node* _pTail;
    int _size;
    
    // Helper methods for merge sort
    Node* mergeSort(Node* head);
    Node* split(Node* head);
    Node* merge(Node* left, Node* right);
};

//---------------------------------------------------------

template<typename T>
LinkedList<T>::LinkedList() {
    _size = 0;
    _pHead = nullptr;
    _pTail = nullptr;
}

template<typename T>
LinkedList<T>::~LinkedList() {
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
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("LinkedList::get position out of range");
    }
    Node* current = _pHead;
    for (int i = 0; i < POS; ++i) {
        current = current->pNext;
    }
    return current->value;
}

template<typename T>
void LinkedList<T>::set(const int POS, const T VALUE) {
    if (POS < 0 || POS >= _size) {
        throw std::out_of_range("LinkedList::set position out of range");
    }
    Node* current = _pHead;
    for (int i = 0; i < POS; ++i) {
        current = current->pNext;
    }
    current->value = VALUE;
}

template<typename T>
void LinkedList<T>::insert(const int POS_IN, const T VALUE) {
    int POS = POS_IN;
    if (POS < 0) {
        POS = 0;
    }
    if (POS > _size) {
        POS = _size;
    }
    Node* pNew = new Node;
    pNew->value = VALUE;
    pNew->pPrev = nullptr;
    pNew->pNext = nullptr;
    
    if (_size == 0) {
        _pHead = pNew;
        _pTail = pNew;
    } else {
        if (POS == 0) {
            pNew->pNext = _pHead;
            _pHead->pPrev = pNew;
            _pHead = pNew;
        } else if (POS == _size) {
            pNew->pPrev = _pTail;
            _pTail->pNext = pNew;
            _pTail = pNew;
        } else {
            Node* current = _pHead;
            for (int i = 0; i < POS; ++i) {
                current = current->pNext;
            }
            pNew->pNext = current;
            pNew->pPrev = current->pPrev;
            current->pPrev->pNext = pNew;
            current->pPrev = pNew;
        }
    }
    ++_size;
}

template<typename T>
void LinkedList<T>::remove(const int POS_IN) {
    if (_size == 0) {
        throw std::out_of_range("LinkedList::remove on empty list");
    }
    int POS = POS_IN;
    if (POS < 0) {
        POS = 0;
    }
    if (POS >= _size) {
        POS = _size - 1;
    }
    Node* pDelete = nullptr;
    if (_size == 1) {
        pDelete = _pHead;
        _pHead = nullptr;
        _pTail = nullptr;
    } else {
        if (POS == 0) {
            pDelete = _pHead;
            _pHead = _pHead->pNext;
            _pHead->pPrev = nullptr;
        } else if (POS == _size - 1) {
            pDelete = _pTail;
            _pTail = _pTail->pPrev;
            _pTail->pNext = nullptr;
        } else {
            Node* current = _pHead;
            for (int i = 0; i < POS - 1; ++i) {
                current = current->pNext;
            }
            pDelete = current->pNext;
            current->pNext = pDelete->pNext;
            pDelete->pNext->pPrev = current;
        }
    }
    delete pDelete;
    --_size;
}

template<typename T>
T LinkedList<T>::min() const {
    if (_size == 0) {
        throw std::out_of_range("LinkedList::min on empty list");
    }
    Node* current = _pHead;
    T currentMin = current->value;
    current = current->pNext;
    while (current != nullptr) {
        if (current->value < currentMin) {
            currentMin = current->value;
        }
        current = current->pNext;
    }
    return currentMin;
}

template<typename T>
T LinkedList<T>::max() const {
    if (_size == 0) {
        throw std::out_of_range("LinkedList::max on empty list");
    }
    Node* current = _pHead;
    T currentMax = current->value;
    current = current->pNext;
    while (current != nullptr) {
        if (current->value > currentMax) {
            currentMax = current->value;
        }
        current = current->pNext;
    }
    return currentMax;
}

template<typename T>
int LinkedList<T>::find(const T VALUE) const {
    Node* current = _pHead;
    int index = 0;
    while (current != nullptr) {
        if (current->value == VALUE) {
            return index;
        }
        current = current->pNext;
        ++index;
    }
    return -1;
}

template<typename T>
int LinkedList<T>::rfind(const T VALUE) const {
    Node* current = _pTail;
    int index = _size - 1;
    while (current != nullptr) {
        if (current->value == VALUE) {
            return index;
        }
        current = current->pPrev;
        --index;
    }
    return -1;
}

// ============== NEW METHODS ==============

template<typename T>
void LinkedList<T>::sort() {
    if (_size <= 1) {
        return;
    }
    
    _pHead = mergeSort(_pHead);
    
    _pHead->pPrev = nullptr;
    Node* current = _pHead;
    while (current->pNext != nullptr) {
        current->pNext->pPrev = current;
        current = current->pNext;
    }
    _pTail = current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::split(Node* head) {
    Node* fast = head;
    Node* slow = head;
    
    while (fast->pNext != nullptr && fast->pNext->pNext != nullptr) {
        fast = fast->pNext->pNext;
        slow = slow->pNext;
    }
    
    Node* mid = slow->pNext;
    slow->pNext = nullptr;
    return mid;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    
    Node* result = nullptr;
    
    if (left->value <= right->value) {
        result = left;
        result->pNext = merge(left->pNext, right);
    } else {
        result = right;
        result->pNext = merge(left, right->pNext);
    }
    
    return result;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::mergeSort(Node* head) {
    if (head == nullptr || head->pNext == nullptr) {
        return head;
    }
    
    Node* mid = split(head);
    
    Node* left = mergeSort(head);
    Node* right = mergeSort(mid);
    
    return merge(left, right);
}

template<typename T>
int LinkedList<T>::search(const T VALUE) const {
    Node* current = _pHead;
    int index = 0;
    
    while (current != nullptr) {
        if (current->value == VALUE) {
            return index;
        }
        current = current->pNext;
        ++index;
    }
    
    return -1;
}

#endif//LINKED_LIST_HPP