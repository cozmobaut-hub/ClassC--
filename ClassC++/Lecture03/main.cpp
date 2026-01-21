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
    mt19937 mt( rd() );
    
    // specify a uniform integer distribution mapped to a specific range
    uniform_int_distribution<int> dist(20, 24);
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
// Random number notes 
// How are values stored in memory? Binary!
// Data type tells us how to interpret binary values.
// Statically typed, variables will always refer to the same data type.
// Integer types: char, short, int, long, long long (signed and unsigned variants)
// Floating point types: float, double, long double
// Integer types store whole numbers, floating point types store real numbers (with fractional parts)
// Integer types have limited ranges based on their size in memory (e.g., short is typically 2 bytes, so -32,768 to 32,767 for signed short)
// Floating point types have much larger ranges but limited precision.
// Overflow occurs when a calculation exceeds the maximum value a data type can hold, causing it to wrap around to the minimum value.
// Use larger data types or floating point types to avoid overflow in calculations. 
// Memory Map: int numCars = 5; (need 4 bytes for int)
// Address:   0xf3da8004 -> numCars value 0x00000005
// double temp = 37.1 0xf3da880c and 0xf3da8010 Identifier temp value 0x40428ccccccccccd
// Char mcAns; mcAns = 'd', mcAns += 1 -> 'e' (next ASCII value)
// you can temporarily type case as well: (int)mcAns + 1 -> 102
// Random number generation requires a source of entropy (randomness).
// Computers are deterministic, so they use pseudorandom number generators (PRNGs) that use algorithms to produce sequences of numbers that approximate the properties of random numbers.
// C++11 introduced a comprehensive random number generation library that includes various PRNGs and distributions.
// Common PRNGs include Mersenne Twister (mt19937), which is widely used for its speed and quality of randomness.
// Distributions define how random numbers are mapped to specific ranges or patterns (e.g., uniform, normal).
// Always seed your PRNG with a good source of entropy (like random_device) to ensure different sequences on each run.
// Example distributions: uniform_int_distribution, uniform_real_distribution, normal_distribution, etc.   
// Example usage:
// random_device rd; // obtain a random number from hardware
// mt19937 mt(rd()); // seed the generator
// uniform_int_distribution<int> dist(1, 6); // define the range
// int random_number = dist(mt); // generate number 
// Note: Different systems may have different sizes for data types (e.g., int may be 2 or 4 bytes), so always check your system's specifications for portability.
// DON'T USE RAND(), DON'T USE RAND % 100 OR RAND_MAX +1 FOR NUMBERS, DON'T MESS WITH FLOATING POINTS, because then you'll have 2.00001 problems instead of 1
// Use random_device and mt19937/mt19937_64 instead for better randomness and distribution control. "uniform_int_distribution" and "uniform_real_distribution" for specific ranges.
