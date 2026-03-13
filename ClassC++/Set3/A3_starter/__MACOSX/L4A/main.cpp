#include "Warehouse.h"

#include <iostream>
using namespace std;

void print_warehouse(Warehouse wh) {
  cout << wh << endl;
}

int main() {
    Warehouse warehouseH;
    warehouseH.setWarehouseLetter('H');
    warehouseH.storeInBox(4);
    warehouseH.storeInBox(2);
    cout << "> Made Warehouse H with 2 boxes of sizes 4 and 2" << endl;
    cout << warehouseH << endl;

    Warehouse warehouseC;
    warehouseC.setWarehouseLetter('C');
    warehouseC.storeInBox(3);
    cout << endl << "> Made Warehouse C with 1 box of size 3" << endl;
    cout << warehouseC << endl;

    warehouseC = warehouseH;
    warehouseC.setWarehouseLetter('C');
    cout << endl << "> Used copy assignment operator to copy from H to C, both have 2 boxes of sizes 4 and 2" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;

    warehouseH.storeInBox(3);
    cout << endl << "> Added box of size 3 to H, H has 3 boxes and C has 2 boxes" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;

    warehouseC.storeInBox(7);
    cout << endl << "> Adding box of size 7 to C, H has 3 boxes and C has 3 boxes" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;

    warehouseH.getBox(1)->setBoxSize(15);
    cout << endl << "> Changed H Box 1 from size 2 to size 15" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;

    Warehouse warehouseD( warehouseH );
    warehouseD.setWarehouseLetter('D');
    cout << endl << "> Used copy constructor to construct D from H, both have 3 boxes of sizes 4 15 and 3" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;
    cout << warehouseD << endl;

    warehouseH.storeInBox(5);
    cout << endl << "> Added box of size 5 to H, H has 4 boxes, C has 3 boxes, and D has 3 boxes" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;
    cout << warehouseD << endl;

    warehouseD.storeInBox(6);
    cout << endl << "> Added box of size 6 to D, H has 4 boxes and D has 4 boxes" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;
    cout << warehouseD << endl;

    warehouseH.getBox(2)->setBoxSize(25);
    cout << endl << "> Changed H Box 2 from size 3 to size 25" << endl;
    cout << warehouseH << endl;
    cout << warehouseC << endl;
    cout << warehouseD << endl;

    cout << endl << "> Passing objects to function by value to print (copy constructor and destructor implicitly called)" << endl;
    print_warehouse(warehouseH);
    print_warehouse(warehouseC);
    print_warehouse(warehouseD);

    return 0;
}
