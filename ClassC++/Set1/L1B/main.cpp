/* CSCI 200: Lab 1B
 * Austin Haas
 * 1/26/2026
 */

#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 mt(rd());
    
    char again;
    
    while (true) { // loop courtesy of google
        float min, max;
        cout << "Enter the minimum value: ";
        cin >> min;
        cout << "Enter the maximum value: ";
        cin >> max;
        
        uniform_real_distribution<float> dist(min, max);
        float value = dist(mt);
        cout << "A random value is: " << value << endl;
        
        float q1 = min + (max-min)/4;
        float q2 = min + 2*(max-min)/4;
        float q3 = min + 3*(max-min)/4;
        
        if (value < q1) cout << "This is in the first quartile" << endl;
        else if (value < q2) cout << "This is in the second quartile" << endl;
        else if (value < q3) cout << "This is in the third quartile" << endl;
        else cout << "This is in the fourth quartile" << endl;
        
        cout << "Do you want another random value? (Y/N) ";
        cin >> again;
        if (again != 'Y') break;
        cout << endl;
    }
    
    cout << "Have a nice day!" << endl;
    return 0;
}
