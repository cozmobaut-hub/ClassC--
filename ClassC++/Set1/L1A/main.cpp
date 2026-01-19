/* CSCI 200: Lab 1A: Hello World 
 *
 * Author: Austin Haas
 *
 * More complete description here...
 */

// The include section adds extra definitions from the C++ standard library.
#include <iostream> // For cin, cout, etc.

// We will (most of the time) use the standard library namespace in our programs.
using namespace std;

// Define any constants below this comment.

// Must have a function named "main", which is the starting point of a C++ program.
int main() {

  double voltage, resistance, current;
  cout << "Enter the voltage (V): ";
  cin >> voltage;
  cout << "Enter the resistance (ohms): ";
  cin >> resistance;
  current = voltage / resistance;
  cout << "The current (I) is: " << current << endl;

  double force, area, stress;
  cout << "Enter the force (F): ";
  cin >> force;
  cout << "Enter the area (A): ";
  cin >> area;
  stress = force / area;
  cout << "The stress (sigma) is: " << stress << endl;

  return 0; // signals the operating system that our program ended OK.
}