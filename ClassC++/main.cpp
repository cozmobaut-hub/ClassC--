/* 
 * CSCI 200: Lecture 05: Fix the Loop Errors
 *
 * Author: Dr. Jeffrey Paone
 *
 *    This program illustrates a variety of common loop errors.
 *    Fix the errors in each section.
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

#include <iostream>
using namespace std;

int main() {
    cout << "Welcome to Loop World" << endl;

    // SECTION 1
    // Sum from 1 to n, where n is the value entered by the user

    cout << endl;
    cout << "******************" << endl;
    cout << "Section I" << endl;
    cout << "******************" << endl;

    int sum;      // Accumulates the total
    int i;        // Used as loop control variable
    int numIter;  // The number of times to iterate
    cout << "Enter a number greater than 1 to sum up to: ";
    cin >> numIter;
    for (i = 1; i < numIter; ++i) {
         sum += i;
     }
    cout << "The sum of the numbers from 1 to " << numIter << " (inclusive) is: " << sum << endl;

    // Section 2
    // Ask user how many items they have, n
    // Sum the total of all n items entered by the user

    cout << endl;
    cout << "******************" << endl;
    cout << "Section II" << endl;
    cout << "******************" << endl;

    double total;     // Accumulates total
    double price;     // Gets next price from user
    int numItems;     // Number of items
    int counter = 1;  // Loop control counter

    cout << "How many items do you have? ";
    cin >> numItems;
    cout << endl;

    while (counter <= numItems) {
        total = 0;
        cout << "Enter the price of item " << counter << ": ";
        cin >> price;
        cout << endl;
        total += price;
        counter++;
    }
    cout << "The total price is: " << total << endl;

    // Section 3
    // Sum from 1 to n, where n is the value entered by the user

    cout << endl;
    cout << "******************" << endl;
    cout << "Section III" << endl;
    cout << "******************" << endl;

    int sum2 = 0;
    int counter2 = 1;
    int numIter2;

    cout << "What number do you wish me to sum from 1 up to?" << endl;
    cin >> numIter2;

    do {
        sum2 += counter2;
        cout << "Sum so far: " << sum2 << endl;
    } while (counter2 <= sum2);

    cout << endl << "Section III Recap" << endl;

    cout << "I calculated the sum of numbers from 1 to " << numIter2 << " (inclusive) as " << sum2 << endl;

    // Section 4
    // Sum 1^2, 2^2, up to n^2

    cout << endl;
    cout << "******************" << endl;
    cout << "Section IV" << endl;
    cout << "******************" << endl;

    cout << "I will now calculate ";
    cout << "the sum of squares from 1 to ? (inclusive)" << endl;
    
    unsigned int numIter3;
    cin >> numIter3;

    unsigned int sum3 = 0;
    for (unsigned int i3 = numIter3; i3 >= 0; i3++) {
        sum3 += i3*i3;
    }

    cout << "The sum of squares from 1 to " << numIter3 << " is: " << sum3 << endl;

    // Section 5
    // Sum from 1^3, 2^3, up to n^3

    cout << endl;
    cout << "******************" << endl;
    cout << "Section V" << endl;
    cout << "******************" << endl;

    cout << "I will now calculate the sum of cubes from 1 to ? (inclusive)" << endl;

    int numIter4;
    cin >> numIter4;

    int sum4 = 0;
    int counter4 = 1;

    while (counter4 < 10) {
        sum4 += (counter4 * counter4 * counter4);
    }

    counter4++;

    cout << "The sum of cubes from 1 to " << numIter4 << " is: " << sum4 << endl;

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Done" << endl;
    cout << "******************" << endl;

    cout << endl << "Congrats!  You fixed them all (hopefully correctly!)" << endl << endl << "Goodbye" << endl << endl;

    return 0;
}
