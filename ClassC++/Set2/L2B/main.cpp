/* CSCI 200: Lab 2B - Pointers and Types
 *
 * Author: Austin Haas

 * 
 *
 */

#include <iostream>
using namespace std;

int main() {
    // Declare two integers
    int iNum = 4;
    int iNum2 = 5;

    // Declare two pointers to integers, initial nullptr
    int *pINum1 = nullptr;
    int *pINum2 = nullptr;

    // Assign addresses
    pINum1 = &iNum;
    pINum2 = &iNum2;

   
    cout << "Address of iNum (&iNum): " << &iNum << endl;
    cout << "Address of iNum (pINum1): " << pINum1 << endl;
    cout << "Address of iNum2 (&iNum2): " << &iNum2 << endl;
    cout << "Address of iNum2 (pINum2): " << pINum2 << endl;
    cout << "Value of iNum via pINum1 (*pINum1): " << *pINum1 << endl;
    cout << "Value of iNum2 via pINum2 (*pINum2): " << *pINum2 << endl;
    iNum = 6;
    cout << "Value of iNum directly: " << iNum << endl;
    cout << "Value of iNum via pINum1: " << *pINum1 << endl;

    // Indirectly change via pINum1 to 7
    *pINum1 = 7;
    cout << "Value of iNum after *pINum1=7: " << iNum << endl;

    // Assign pINum2 = pINum1 (using address from pINum1)
    pINum2 = pINum1;
    cout << "Value of pINum2: " << pINum2 << endl;
    cout << "Value pointed to by pINum2 (*pINum2): " << *pINum2 << endl;
    *pINum2 = 8;
    cout << "Value of iNum using pINum1 (*pINum1): " << *pINum1 << endl;
    cout << "Value of iNum using pINum2 (*pINum2): " << *pINum2 << endl;
    cout << "Value of iNum directly: " << iNum << endl;
    cout << "Value of iNum2 (unchanged): " << iNum2 << endl;

    double* pDNum = nullptr;

    
    // pDNum = &iNum;
    // Compile error: cannot convert 'int*' to 'double*' in assignment

    // pDNum = pINum1;
    // Compile error: cannot convert 'int*' to 'double*' in assignment

    double dNum = 14.25;

    
    pDNum = &dNum;
    cout << "Address of dNum using pDNum: " << pDNum << endl;
    cout << "Value of dNum using pDNum (*pDNum): " << *pDNum << endl;
    
    // Try to assign value pINum1 points at (*pINum1, int 8) to value pDNum points at (*pDNum)
    *pDNum = *pINum1;

    
    cout << "Value of dNum directly (after assign): " << dNum << endl;
    cout << "Value of dNum using pDNum (*pDNum, after assign): " << *pDNum << endl;

    return 0;
}
