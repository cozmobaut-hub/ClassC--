#ifndef INPUT_PROCESSOR_H
#define INPUT_PROCESSOR_H

#include <iostream>
#include <vector>
#include <string>

class InputProcessor {
private:
    std::vector<std::string> words;

public:
    InputProcessor();

    void readFromStream(std::istream& in);
    void sanitizeWords(const std::string& punctuation);
    std::vector<std::string> getAllWords() const;
};

#endif
