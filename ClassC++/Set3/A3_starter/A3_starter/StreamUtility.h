#ifndef STREAM_UTILITY_H
#define STREAM_UTILITY_H

#include <iostream>

class StreamUtility {
public:
    std::istream* selectInput();
    std::ostream* selectOutput();
};

#endif
