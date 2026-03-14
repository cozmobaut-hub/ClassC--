#include "Warehouse.h"

Warehouse::Warehouse() {
    _pItems = new std::vector<Box*>;
}

Warehouse::~Warehouse() {
    while( !_pItems->empty() ) {
        delete _pItems->back();
        _pItems->pop_back();
    }
    delete _pItems;
}

void Warehouse::store(const int ITEM) {
    _pItems->push_back( new Box(ITEM) );
}

Box& Warehouse::retrieve(const size_t ITEM_POS) const {
    return *(_pItems->at(ITEM_POS));
}

size_t Warehouse::getNumberOfItems() const {
    return _pItems->size();
}

char Warehouse::getWarehouseLetter() const {
    return _warehouseLetter;
}

void Warehouse::setWarehouseLetter(const char warehouseLetter) {
    _warehouseLetter = warehouseLetter;
}

std::ostream& operator<<(std::ostream& os, const Warehouse& WH) {
    const size_t NUM_ITEMS = WH.getNumberOfItems();
    os << "Warehouse " << WH.getWarehouseLetter() << " has " << NUM_ITEMS << " items (";
    for(size_t i = 0; i < NUM_ITEMS; i++) {
        os << WH.retrieve(i);
        if(i < NUM_ITEMS - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}