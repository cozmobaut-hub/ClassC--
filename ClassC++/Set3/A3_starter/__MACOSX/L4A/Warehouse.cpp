#include "Warehouse.h"

using namespace std;


void Warehouse::deallocate() {
    for (size_t i = 0; i < _pBoxen->size(); i++) {
        delete (*_pBoxen)[i];
    }
    _pBoxen->clear();
}

void Warehouse::deepCopy(const Warehouse& other) {
    _pBoxen->clear();
    for (size_t i = 0; i < other._pBoxen->size(); i++) {
        (*_pBoxen).push_back(new Box(*(other._pBoxen->at(i))));
    }
    _warehouseLetter = other._warehouseLetter;
}

Warehouse::Warehouse() {
    _pBoxen = new vector<Box*>;
    _warehouseLetter = '?';
}

Warehouse::Warehouse(const Warehouse& other) {
    _pBoxen = new vector<Box*>;
    deepCopy(other);
}

Warehouse& Warehouse::operator=(const Warehouse& other) {
    if (this != &other) {
        deallocate();
        deepCopy(other);
    }
    return *this;
}

Warehouse::~Warehouse() {
    deallocate();
    delete _pBoxen;
}

void Warehouse::storeInBox(const int SIZE) {
    _pBoxen->push_back( new Box(SIZE) );
}

Box* Warehouse::getBox(const size_t BOX_POS) const {
    return _pBoxen->at(BOX_POS);
}

size_t Warehouse::getNumberOfBoxes() const {
    return _pBoxen->size();
}

char Warehouse::getWarehouseLetter() const {
    return _warehouseLetter;
}

void Warehouse::setWarehouseLetter(const char warehouseLetter) {
    _warehouseLetter = warehouseLetter;
}

std::ostream& operator<<(ostream& os, const Warehouse& WH) {
    os << "Warehouse " << WH.getWarehouseLetter() << " has " << WH.getNumberOfBoxes() << " boxes (";
    for(size_t i = 0; i < WH.getNumberOfBoxes(); i++) {
        os << WH.getBox(i)->getBoxSize();
        if(i < WH.getNumberOfBoxes() - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}
