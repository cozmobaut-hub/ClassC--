/*
 * CSCI 200 – Spring 2026
 * Lab 2C – Coordinate Conversion By Pointer
 * Author: Austin Haas
 * Date:   02/16/2026
 *
 * Description: Simple coordinate converter using pass-by-pointer.
 */

#include <iostream>
#include "coordinate_conversion.h"

using namespace std;

int main() {
    cout << "Coordinate Conversion\n";
    cout << "1) (r, theta) -> (x, y)\n";
    cout << "2) (x, y) -> (r, theta)\n";
    cout << "Enter choice (1 or 2): ";

    int choice;
    cin >> choice;

    if (choice == 1) {
        double r, theta;
        double x, y;

        cout << "Enter r and theta: ";
        cin >> r >> theta;

        polar_to_cartesian(r, theta, &x, &y);

        cout << "x = " << x << ", y = " << y << endl;
    } else if (choice == 2) {
        double x, y;
        double r, theta;

        cout << "Enter x and y: ";
        cin >> x >> y;

        cartesian_to_polar(x, y, &r, &theta);

        cout << "r = " << r << ", theta = " << theta << endl;
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
