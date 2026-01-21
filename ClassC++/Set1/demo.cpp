/* CSCI 200: Lab 1A Demo - Signed Short Overflow
 * Author:  Austin Haas
 * Mt. Elbert (14440) + Everest (29032) = 43472 > 32767 → wraps to negative
 */

#include <iostream>
using namespace std;

int main() {
    short elbert = 14440;  
    short everest = 29032; 
    short total = elbert + everest;
    
    cout << "Mt. Elbert: " << elbert << " ft" << endl;
    cout << "Mt. Everest: " << everest << " ft" << endl;
    cout << "Short max: 32767 ft" << endl;
    cout << "Total height: " << total << " ft (WRAPPED!)" << endl; 
    
    return 0;
}
