#include "string_functions.h"

#include <iostream>
using namespace std;

size_t string_length(const string STR) {
    size_t result = 0;
    result = STR.length();
    return result;
}

char string_char_at(const string STR, const size_t IDX) {
    char result = '\0';
    result = STR.at(IDX);
    return result;
}

string string_append(const string LEFT, const string RIGHT) {
    string result = LEFT;
    result += RIGHT;
    return result;
}
// string insertion and search helpers

string string_insert(const string STR, const string TO_INSERT, const size_t IDX) {
    string result = STR;
    result.insert(IDX, TO_INSERT);
    return result;
}

size_t string_find(const string STR, const char C) {
    size_t result = STR.find(C);
    return result;
}

string string_substring(const string STR, const size_t IDX, const size_t LEN) {
    string result = STR.substr(IDX, LEN);
    return result;
}
// replacement and first-word operations

string string_replace(const string STR, const string TEXT_TO_REPLACE, const string REPLACE_WITH) {
    string result = STR;
    size_t pos = result.find(TEXT_TO_REPLACE);
    if (pos != string::npos) {
        result.replace(pos, TEXT_TO_REPLACE.length(), REPLACE_WITH);
    }
    return result;
}

string string_first_word(const string STR) {
    if (STR.empty()) {
        return "";
    }
    size_t spacePos = STR.find(' ');
    if (spacePos == string::npos) {
        return STR;
    }
    return STR.substr(0, spacePos);
}

string string_remove_first_word(const string STR) {
    if (STR.empty()) {
        return "";
    }
    size_t spacePos = STR.find(' ');
    if (spacePos == string::npos) {
        return "";
    }
    return STR.substr(spacePos + 1);
}
// functions for 2nd, 3rd, and nth words

string string_second_word(const string STR) {
    if (STR.empty()) {
        return "";
    }
    size_t firstSpace = STR.find(' ');
    if (firstSpace == string::npos) {
        return "";
    }
    size_t secondSpace = STR.find(' ', firstSpace + 1);
    if (secondSpace == string::npos) {
        return STR.substr(firstSpace + 1);
    }
    return STR.substr(firstSpace + 1, secondSpace - (firstSpace + 1));
}

string string_third_word(const string STR) {
    if (STR.empty()) {
        return "";
    }
    size_t firstSpace = STR.find(' ');
    if (firstSpace == string::npos) {
        return "";
    }
    size_t secondSpace = STR.find(' ', firstSpace + 1);
    if (secondSpace == string::npos) {
        return "";
    }
    size_t thirdSpace = STR.find(' ', secondSpace + 1);
    if (thirdSpace == string::npos) {
        return STR.substr(secondSpace + 1);
    }
    return STR.substr(secondSpace + 1, thirdSpace - (secondSpace + 1));
}

string string_nth_word(const string STR, const int N) {
    if (STR.empty() || N <= 0) {
        return "";
    }

    size_t start = 0;
    int currentWord = 1;

    while (currentWord < N) {
        size_t spacePos = STR.find(' ', start);
        if (spacePos == string::npos) {
            return "";
        }
        start = spacePos + 1;
        currentWord++;
    }

    if (start >= STR.length()) {
        return "";
    }

    size_t endSpace = STR.find(' ', start);
    if (endSpace == string::npos) {
        return STR.substr(start);
    }
    return STR.substr(start, endSpace - start);
}
// tokenizing, substitution, and lowercase conversion

vector<string> string_tokenize(const string STR, const char DELIMINATOR) {
    vector<string> result;

    if (STR.empty()) {
        result.push_back("");
        return result;
    }

    size_t start = 0;
    while (true) {
        size_t pos = STR.find(DELIMINATOR, start);
        if (pos == string::npos) {
            result.push_back(STR.substr(start));
            break;
        } else {
            result.push_back(STR.substr(start, pos - start));
            start = pos + 1;
        }
    }

    return result;
}

string string_substitute(const string STR, const char TARGET, const char REPLACEMENT) {
    string result = STR;
    for (size_t i = 0; i < result.length(); ++i) {
        if (result.at(i) == TARGET) {
            result.at(i) = REPLACEMENT;
        }
    }
    return result;
}

string string_to_lower(const string STR) {
    string result = STR;
    for (size_t i = 0; i < result.length(); ++i) {
        result.at(i) = static_cast<char>(tolower(result.at(i)));
    }
    return result;
}
// uppercase conversion and compare

string string_to_upper(const string STR) {
    string result = STR;
    for (size_t i = 0; i < result.length(); ++i) {
        result.at(i) = static_cast<char>(toupper(result.at(i)));
    }
    return result;
}

int string_compare(const string LHS, const string RHS) {
    int cmp = LHS.compare(RHS);
    if (cmp < 0) {
        return -1;
    } else if (cmp > 0) {
        return 1;
    } else {
        return 0;
    }
}
