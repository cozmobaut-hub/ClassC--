#include <iostream>
using namespace std;

double a = 1.0;
double *pA = new double;
double b = 2.0;

int main() {
    *pA = 10.0;
    double *ogpA = pA;
    cout << "1: a=" << a << ", b=" << b << ", *pA=" << *pA << ", pA=" << pA << ", &a=" << &a << ", &b=" << &b << endl;
    
    pA = &a;
    cout << "2: a=" << a << ", b=" << b << ", *pA=" << *pA << ", pA=" << pA << ", &a=" << &a << ", &b=" << &b << endl;
    
    a = 18;
    cout << "3: a=" << a << ", b=" << b << ", *pA=" << *pA << ", pA=" << pA << ", &a=" << &a << ", &b=" << &b << endl;
    
    *pA = 42;
    cout << "4: a=" << a << ", b=" << b << ", *pA=" << *pA << ", pA=" << pA << ", &a=" << &a << ", &b=" << &b << endl;
    
    pA = &b;
    cout << "5: a=" << a << ", b=" << b << ", *pA=" << *pA << ", pA=" << pA << ", &a=" << &a << ", &b=" << &b << endl;
    
    pA = ogpA;
    cout << "6: a=" << a << ", b=" << b << ", pA=" << pA << ", &a=" << &a << ", &b=" << &b << endl;
    delete pA;
    pA = nullptr;
    ogpA = nullptr;
    cout << "7: a=" << a << ", b=" << b << ", pA=" << pA << ", &a=" << &a << ", &b=" << &b << endl;
    
    return 0;
}
