/* 
 * CSCI 200: Lecture 03: C++11 Random and Makefile usage
 *
 * Author: Dr. Jeffrey Paone
 *
 * Demonstrates how to use the C++11 random library to generate random numbers in a given range
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

#include <iostream>     // For cin, cout, etc.
#include <random>       // C++11 random library
using namespace std;    // saves us from having to specify std:: everytime

int main() {
    // seed a Mersenne Twister pseudorandom number generator (PRNG)
    random_device rd;
    mt19937 mt( rd() ); // route rd through the mt PRNG
    
    // specify a uniform integer distribution mapped to a specific range
    uniform_int_distribution<int> dist(20, 24); // call a distribution object and typecast it to int, with range 20 to 24 inclusive
    cout << "Here are five random ints:   ";
    cout << dist(mt) << "\t";    // generate the next value from the PRNG mapped to our distribution
    cout << dist(mt) << "\t";
    cout << dist(mt) << "\t";
    cout << dist(mt) << "\t";
    cout << dist(mt) << endl;

    cout << endl;

    // specify a uniform real distribution mapped to floats within a specific range
    uniform_real_distribution<float> floatDist(24.0f, 88.0f);
    cout << "Here are five random floats: ";
    cout << floatDist(mt) << "\t";  // generate the next value from the PRNG mapped to our distribution
    cout << floatDist(mt) << "\t";
    cout << floatDist(mt) << "\t";
    cout << floatDist(mt) << "\t";
    cout << floatDist(mt) << endl;
    
    return 0;
}
