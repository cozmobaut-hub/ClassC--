#include <iostream>
using namespace std;

/**
 * @brief Function to enter coordinates using pointers.
 * @param pX Pointer to an integer for the x coordinate.
 * @param pY Pointer to an integer for the y coordinate.
 */

void enter_coordinates(int *pX, int *pY) {
    cout << "Enter x and y coordinates: ";
    cin >> *pX >> *pY;
}

/**
 * @brief Main function to demonstrate pointer usage.
 * @param None
 * @return int 
 */
int main() {
    int *px = new int;  // Free store (heap) allocation [web:22][web:28]
    int *py = new int;
    
    enter_coordinates(px, py);  // Pass pointers directly (no & needed)
    
    cout << "You entered: (" << *px << ", " << *py << ")" << endl;  // Dereference for values
    cout << "Memory addresses: x = " << px << ", y = " << py << endl;  // Pointer values are addresses
    
    px = nullptr;  // Avoid dangling pointer
    py = nullptr;
    delete px;  // Manual cleanup required
    delete py;
    return 0;
}
