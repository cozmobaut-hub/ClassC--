/* CSCI 200: Fix Loop and Function Errors
 *
 * Author: XXXX (_INSERT_YOUR_NAME_HERE_)
 *
 * Description:
 *    This program illustrates a variety of common loop and function 
 *    errors.  Fix the errors in each section.
 * 
 * Copyright 2026 Dr. Jeffrey Paone
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

#include <iostream>     // for cout, cin, endl etc.
#include <random>       // for mt19937 generator
using namespace std;

/**
 * @brief adds five to the given parameter
 * @param x integer to be added to
 * @returns parameter plus five
 */
int add_five( int x ) {
    // Error 4: Function does not return a value
    // Fix 4: Change return type to int and add return statement
    x += 5;
    return x;
}

/**
 * @brief generates a single random integer number within the expected range
 * @param MIN lower inclusive bound of range
 * @param MAX upper inclusive bound of range
 * @returns random integer within the range [MIN, MAX]
 */
int generate_random_integer(const int MIN, const int MAX) {
    // create the Mersenne Twister generator
    // Error 1: Unused Paramater Min and Max
    // Fix 1: Use uniform_int_distribution with Min and Max
    random_device rd;
    mt19937 mt( rd() );
    uniform_int_distribution<int> dist(MIN, MAX);

    return dist(mt);
}

/**
 * @brief generates a single random floating point number within the expected range
 * @param MIN lower inclusive bound of range
 * @param MAX upper inclusive bound of range
 * @return random float within the range [MIN, MAX]
 */
float generate_random_float(const float MIN, const float MAX) {
    // create the Mersenne Twister generator
    // Error 2: Unused Paramater Min and Max
    // Fix 2: Use uniform_real_distribution with Min and Max
    random_device rd;
    mt19937 mt( rd() );
    uniform_real_distribution<float> dist(MIN, MAX);

    return dist(mt);
}

/**
 * @brief sums three integer values
 * @param x first value to be added
 * @param y second value to be added
 * @param z third value to be added
 * @returns the sum of all three parameters
 */
int sum( int x, int y, int z ) {
    // Error 3: Only sums x parameter
    // Fix 3: Sum all three parameters
    return x + y + z;
}

/**
 * @brief multiples two floats together
 * @param a first value to multiply
 * @param b second value to multipl
 * @returns the product of the two float parameters
 */
float multiply( float a, float b ){
    return a * b;   
}

/**
 * @brief runs test summing numbers in the range [1, N]
 */
void loop_test_1() {
    // FIX = initialize sum and fix loop bound to include n
    // TESTS (provide input/output pairs that verify proper operation):
    //   Input: 2   → Output: 3
    //   Input: 3   → Output: 6
    //   Input: 5   → Output: 15
    //   Input: 10  → Output: 55

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 1 " << endl;
    cout << "******************" << endl;

    int n;
    cout << "Enter a number greater than 1 to sum up to: ";
    cin >> n;

    long int sum = 0;                // initialize
    for (int i = 1; i <= n; ++i) {   // include n
        sum += i;
    }

    cout << "The sum of the numbers from 1 to " << n
         << " (inclusive) is: " << sum << endl;
}


/**
 * @brief runs test summing set of prices entered by the user
 */
void loop_test_2() {
    // FIX = correct counter increment position, instead of 0 so it counts properly, also initialize totalPrice so you're not 
    // adding to garbage value
    // TESTS (provide input/output pairs that verify proper operation): 

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 2 " << endl;
    cout << "******************" << endl;

    int numItems;
    cout << "How many items do you have? ";
    cin >> numItems;
    cout << endl;

    int counter = 0;
    float totalPrice = 0, price;
    while (counter < numItems) {
        cout << "Enter the price of item " << counter << ": ";
        cin >> price;
        totalPrice += price;
        counter++;
    }
    cout << "The total price is: " << totalPrice << endl;
}

/**
 * @brief runs test summing numbers in the range [1, N]
 */
void loop_test_3() {
    // FIX = init counter at 0 so agin, you are not summing garBAGE VALUES  
    // TESTS (provide input/output pairs that verify proper operation): 
    //  Input: 2   → Output: 3
    //  Input: 3   → Output: 6
    //  Input: 5   → Output: 15
    //  Input: 10  → Output: 55

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 3 " << endl;
    cout << "******************" << endl;

    int n;
    cout << "What number do you wish me to sum to?" << endl;
    cin >> n;

    int sum = 0, counter =0;
    do {
        sum += counter;
        cout << "Sum so far: " << sum << endl;
        counter++;
    } while (counter <= n);
    cout << endl << "Section III Recap" << endl;

    cout << "I calculated the sum of numbers from 1 to " << n << " (inclusive) as " << sum << endl;
}

/**
 * @brief runs test summing i^2 in the range [1, N]
 */
void loop_test_4() {
    // FIX = change sum to unsigned long int to avoid overflow for larger n
    // TESTS (provide input/output pairs that verify proper operation): 
    //  Input: 2   → Output: 5
    //  Input: 3   → Output: 14
    //  Input: 5   → Output: 55
    //  Input: 10  → Output: 385

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 4 " << endl;
    cout << "******************" << endl;

    cout << "I will now calculate the sum of squares from 1 to N (inclusive)" << endl;
    
    int n;
    cout << "Enter N: ";
    cin >> n;

    unsigned long int sum = 0;
    for( int i = n; i > 0; --i ) {
        sum += i * i;
    }

    cout << "The sum of squares from 1 to " << n << " is: " << sum << endl;
}

/**
 * @brief runs test summing i^3 in the range [1, N]
 */
void loop_test_5() {
    // FIX = change while condition from counter < 10 to counter <= n; initialize counter=1 before loop
    // TESTS (provide input/output pairs that verify proper operation): 
    // Input: 1 → Output: The sum of cubes from 1 to 1 is: 1
    // Input: 5 → Output: The sum of cubes from 1 to 5 is: 225
    // Input: 10 → Output: The sum of cubes from 1 to 10 is: 3025

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Looping 5 " << endl;
    cout << "******************" << endl;

    cout << "I will now calculate the sum of cubes from 1 to N (inclusive)" << endl;

    int n;
    cout << "Enter N: ";
    cin >> n;

    int sum = 0, counter = 1;
    while( counter <= n ) {
        sum += (counter * counter * counter);
        ++counter;
    }

    cout << "The sum of cubes from 1 to " << n << " is: " << sum << endl;
}

/**
 * @brief runs test using function to add five to an entered value
 */
void function_test_1() {
    // FIX = add_five function to add five and return the result
    // TESTS (provide input/output pairs that verify proper operation): 
    //   Input: 0   → Output: 5
    //   Input: 3   → Output: 8
    //   Input: -2  → Output: 3

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 1" << endl;
    cout << "******************" << endl;

    int numTrees;
    cout << "How many trees do you currently have? ";
    cin >> numTrees;
    cout << "There are initially " << numTrees << " trees." << endl;
    numTrees = add_five( numTrees );
    cout << "We planted five trees, there are now " << numTrees << " trees." << endl;
}

void printSmileyFace() {
    cout << "  *****  " << endl;
    cout << " *     * " << endl;
    cout << "*  O O  *" << endl;
    cout << "*   ^   *" << endl;
    cout << "*  '-'  *" << endl;
    cout << " *     * " << endl;
    cout << "  *****  " << endl;
}

/**
 * @brief runs test to call a function that outputs a smiley face to the standard out
 * 
 */
void function_test_2() {
    // FIX =
    // TESTS (provide input/output pairs that verify proper operation): 

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 2" << endl;
    cout << "******************" << endl;

    printSmileyFace();
    // Error 5: Function does not exist
    // Fix 5: Implement printSmileyFace function
}

/**
 * @brief runs test to generate five random integers within a provided range
 */
void function_test_3() {
    // FIX = generate random integers within the provided range, originally had no range
    // TESTS (provide input/output pairs that verify proper operation): 
    // Input: min=10, max=20  → Output:  17 16 18 18 15 

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 3" << endl;
    cout << "******************" << endl;

    int min, max;
    cout << "Enter the minimum integer range value: ";
    cin >> min;
    cout << "Enter the maximum integer range value: ";
    cin >> max;

    cout << "Five different random numbers are: " << endl;
    for( int i = 0; i < 5; i++ ) {
        cout << "\t" << generate_random_integer(min, max) << endl;
    }
}

/**
 * @brief runs test to use function to sum three values
 */
void function_test_4() {
    // FIX = Fixed the sum function to sum all three parameters
    // TESTS (provide input/output pairs that verify proper operation): 
    // Input: 1 2 3  → Output: 6
    // Input: 5 5 5  → Output: 15
    // Input: -1 1 0 → Output: 0
    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 4" << endl;
    cout << "******************" << endl;

    int num1, num2, num3;
    cout << "Enter three integer numbers: ";
    cin >> num1 >> num2 >> num3;
    cout << "The sum of all three is " << sum( num1, num2, num3 ) << endl;
    // Error 6: Function sum does not sum all three parameters
    // Fix 6: Modify sum function to sum all three parameters
}

/**
 * @brief runs test to generate five random floats within a provided range
 */
void function_test_5() {
    // FIX = generate random floats within the provided range, originally had no range
    // TESTS (provide input/output pairs that verify proper operation): 
    // Input: min=1.5, max=5.5  → Output:  3.2 4.7 1.9 5.1 2.6
    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 5" << endl;
    cout << "******************" << endl;

    float min, max;
    cout << "Enter the minimum float range value: ";
    cin >> min;
    cout << "Enter the maximum float range value: ";
    cin >> max;
    cout << "Five different random floats are: " << endl;
    for( int i = 0; i < 5; ++i ) {
        cout << "\t" << generate_random_float(min, max) << endl;
    }
    // Error 7: Function generate_random_float does not use min and max parameters
    // Fix 7: Modify generate_random_float function to use min and max parameters
}

/**
 * @brief runs test to use function to multiply two provided numbers
 */
void function_test_6() {
    // FIX = define multiply function to return product of two float parameters, originally didn't actually define it
    // TESTS (provide input/output pairs that verify proper operation): 
    // Input: 2.0 3.0  → Output: 6.0
    // Input: 1.5 4.0  → Output: 6.
    cout << endl;
    cout << "******************" << endl;
    cout << "Section Function 6" << endl;
    cout << "******************" << endl;

    float leftHandSide, rightHandSide;
    cout << "Enter two floats: ";
    cin >> leftHandSide >> rightHandSide;
    cout << "Their product is: " << multiply( leftHandSide, rightHandSide ) << endl;
    // Error 8: Function multiply is only declared, not defined
    // Fix 8: Define multiply function to return product of two float parameters
}

int main() {
    cout << "Welcome To Looping Function World!" << endl;
    
    loop_test_1();        // run looping test 1
    loop_test_2();        // run looping test 2
    loop_test_3();        // run looping test 3
    loop_test_4();        // run looping test 4
    loop_test_5();        // run looping test 5

    function_test_1();    // run function test 1
    function_test_2();    // run function test 2
    function_test_3();    // run function test 3
    function_test_4();    // run function test 4
    function_test_5();    // run function test 5
    function_test_6();    // run function test 6

    cout << endl;
    cout << "******************" << endl;
    cout << "Section Done" << endl;
    cout << "******************" << endl;

    cout << endl << "Congrats!  You fixed them all (hopefully correctly!)" << endl << endl << "Goodbye" << endl << endl;

    return 0;
}

