#include <iostream>

class Foo {
private:
    int* data;

public:
    // 1. Default constructor
    Foo(int value = 0)
        : data(new int(value)) { }

    // 2. Destructor
    ~Foo() {
        delete data;
    }

    // 3. Copy constructor
    Foo(const Foo& other)
        : data(new int(*other.data)) { }

    // 4. Copy assignment
    Foo& operator=(const Foo& other) {
        if (this != &other) {
            delete data;                 // free old
            data = new int(*other.data); // deep copy
        }
        return *this;
    }

    // 5. Move constructor
    Foo(Foo&& other) noexcept
        : data(other.data) {
        other.data = nullptr;            // give up ownership
    }

    // 6. Move assignment
    Foo& operator=(Foo&& other) noexcept {
        if (this != &other) {
            delete data;                 // free old
            data = other.data;           // steal pointer
            other.data = nullptr;        // give up ownership
        }
        return *this;
    }

    int get() const { return *data; }
    void set(int v) { *data = v; }
};

int main() {
    Foo a(10);          // default ctor
    Foo b = a;          // copy ctor
    Foo c;              // default ctor
    c = a;              // copy assignment

    Foo d = Foo(20);    // move ctor (likely)
    Foo e;              // default ctor
    e = Foo(30);        // move assignment (likely)
}