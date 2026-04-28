#ifndef LIST_HPP
#define LIST_HPP

template<typename T>
class IList {
public:
    virtual ~IList() = default;

    virtual int size() const = 0;
    virtual T get(const int POS) const = 0;
    virtual void set(const int POS, const T VALUE) = 0;
    virtual void insert(const int POS, const T VALUE) = 0;
    virtual void remove(const int POS) = 0;
    virtual T min() const = 0;
    virtual T max() const = 0;
    virtual int find(const T VALUE) const = 0;
    virtual int rfind(const T VALUE) const = 0;
    
    // NEW METHODS FOR LAB 6A
    virtual void sort() = 0;
    virtual int search(const T VALUE) const = 0;
};

#endif//LIST_HPP