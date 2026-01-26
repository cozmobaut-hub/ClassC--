/* CSCI 200: Lab 1A: Hello World 
 *
 * Author: Austin Haas
 * Date: 1/25/2026
 */

#include <iostream>     
#include <random>      
using namespace std;   

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
