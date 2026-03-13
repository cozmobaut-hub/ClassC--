#include "InputProcessor.h"
#include <cctype>

InputProcessor::InputProcessor()
    : words() {
}

void InputProcessor::readFromStream(std::istream& in) {
    words.clear();
    std::string token;

    while (in >> token) {
        if (token == "ENDEND") {
            break;
        }
        words.push_back(token);
    }
}

void InputProcessor::sanitizeWords(const std::string& punctuation) {
    for (std::size_t i = 0; i < words.size(); ++i) {
        std::string cleaned;
        const std::string& w = words[i];
        for (std::size_t j = 0; j < w.size(); ++j) {
            char ch = w[j];
            bool isPunct = false;
            for (std::size_t k = 0; k < punctuation.size(); ++k) {
                if (ch == punctuation[k]) {
                    isPunct = true;
                    break;
                }
            }
            if (!isPunct) {
                cleaned.push_back(static_cast<char>(
                    std::toupper(static_cast<unsigned char>(ch))));
            }
        }
        words[i] = cleaned;
    }
}

std::vector<std::string> InputProcessor::getAllWords() const {
    return words;
}
