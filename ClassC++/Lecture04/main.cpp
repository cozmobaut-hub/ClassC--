/* 
 * CSCI 200: Lecture 04: Conditionals Practice
 *
 * Author: Dr. Jeffrey Paone
 *
 * Exercises to properly create and use conditionals within a program
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 * 
 */

#include <cmath>            // For sqrt()
#include <iomanip>          // For setprecision()
#include <iostream>         // For cin, cout, etc.
using namespace std;        // saves us from having to specify std:: everytime

int main() {
    
    //-----------------------------------------------------------------------------------
    // Programming Task #1 - Pi Day Discount!
    //-----------------------------------------------------------------------------------
    cout << "Programming Task #1 - Pi Day Discount!" << endl;
    double piePrice = 0.0;          // original cost of a pie
    cout << "Enter the price of a pie: ";
    cin >> piePrice;

    double discountedPrice = 0.0;   // will be set to the pie cost after discount applied

    // if the pie is greater than 10 dollars, deduct $3.14
    // otherwise, deduct $1.00
    // if (conditional)
    if (piePrice > 10.0){discountedPrice = piePrice - 3.14;} 
    else {discountedPrice = piePrice - 1.0;}

    cout << "After discount, the pie costs $" << discountedPrice << endl;

    //-----------------------------------------------------------------------------------
    // Programming Task #2 - Teenager Classifier
    //-----------------------------------------------------------------------------------
    cout << endl << "Programming Task #2 - Teenager Classifier" << endl;
    int age = 0;                    // user's age
    cout << "Enter your age: ";
    cin >> age;

    // if age is between 13 and 19, inclusive
    if (age >= 13 && age <= 19) {cout << "Teenager!" << endl;} 
    else {cout << "Not a teen" << endl;}

    //-----------------------------------------------------------------------------------
    // Programming Task #3 - When sqrt(n)^2 is not n
    //-----------------------------------------------------------------------------------
    cout << endl << "Programming Task #3 - When sqrt(n)^2 is not n" << endl;
    double value = 2.0;             // value to square root then square - n
    cout << "Enter a number: ";
    cin >> value;

    // square root the value - sqrt(n)
    double squareRoot = sqrt(value);
    // square the square root - should be n again
    double squareRootSquared = squareRoot * squareRoot;
    // test if we got n back
    if (squareRootSquared == value) {cout << "sqrt(" << value << ") squared is " << value << endl;} 
    else {cout << "sqrt(" << value << ") squared is not " << value << " but is " << setprecision(18) << squareRootSquared << endl;}

    return 0;
}
