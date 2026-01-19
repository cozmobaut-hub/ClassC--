/* CSCI 200: Lab 1A Demo - Signed Short Overflow
 * Author:  Austin Haas
 * Mt. Elbert (14440) + Everest (29032) = 43472 > 32767 → wraps to negative
 */

#include <iostream>
using namespace std;

int main() {
    short elbert = 14440;  // Mt. Elbert height (ft)
    short everest = 29032; // Mt. Everest height (ft)  
    short total = elbert + everest;
    
    cout << "Mt. Elbert: " << elbert << " ft" << endl;
    cout << "Mt. Everest: " << everest << " ft" << endl;
    cout << "Short max: 32767 ft" << endl;
    cout << "Total height: " << total << " ft (WRAPPED!)" << endl;  // -22094
    
    return 0;
}
