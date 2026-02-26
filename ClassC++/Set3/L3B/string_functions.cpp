#include "string_functions.h"

#include <iostream>

using namespace std;

size_t string_length(const string STR)  {
    size_t result = 0;
    result = STR.length();  // set result to the length of the string
    return result;
}

char string_char_at(const string STR, const size_t IDX) {
    char result = '\0';
    // TODO 01: set result to the character of a string at a given index
    std::cout << "TODO: implement string_char_at(\"" << STR << "\", " << IDX << ")" << std::endl;
    return result;
}

string string_append(const string LEFT, const string RIGHT)  {
    string result = LEFT;
    // TODO 02: set result to the concatenation of strings LEFT and RIGHT
    std::cout << "TODO: implement string_append(\"" << LEFT << "\", \"" << RIGHT << "\")" << std::endl;
    return result;
}

string string_insert(const string STR, const string TO_INSERT, const size_t IDX) {
    string result = STR;
    // TODO 03: set result to the result of inserting a string into another
    std::cout << "TODO: implement string_insert(\"" << STR << "\", \"" << TO_INSERT << "\", " << IDX << ")" << std::endl;
    return result;
}

size_t string_find(const string STR, const char C)  {
    size_t result = 0;
    // TODO 04: set result to the index of the first occurrence of the character
    std::cout << "TODO: implement string_find(\"" << STR << "\", '" << C << "')" << std::endl;
    return result;
}

string string_substring(const string STR, const size_t IDX, const size_t LEN) {
    string result = STR;
    // TODO 05: set result to be a substring starting at index of given length
    std::cout << "TODO: implement string_substring(\"" << STR << "\", " << IDX << ", " << LEN << ")" << std::endl;
    return result;
}

string string_replace(const string STR, const string TEXT_TO_REPLACE, const string REPLACE_WITH) {
    string result = STR;
    // TODO 06: set result to be the string with the given text replaced
    std::cout << "TODO: implement string_replace(\"" << STR << "\", \"" << TEXT_TO_REPLACE << "\", \"" << REPLACE_WITH << ")\"" << std::endl;
    return result;
}

string string_first_word(const string STR)  {
    string result = STR;
    // TODO 07: set result to the first word from the string
    std::cout << "TODO: implement string_first_word(\"" << STR << "\")" << std::endl;
    return result;
}

string string_remove_first_word(const string STR)  {
    string result = STR;
    // TODO 08: set result to be the string with the first word removed
    std::cout << "TODO: implement string_remove_first_word(\"" << STR << ")\"" << std::endl;
    return result;
}

string string_second_word(const string STR)  {
    string result = STR;
    // TODO 09: set result to be the second word from the string
    std::cout << "TODO: implement string_second_word(\"" << STR << "\")" << std::endl;
    return result;
}

string string_third_word(const string STR)  {
    string result = STR;
    // TODO 10: set result to be the third word from the string
    std::cout << "TODO: implement string_third_word(\"" << STR << "\")" << std::endl;
    return result;
}

string string_nth_word(const string STR, const int N)  {
    string result = STR;
    // TODO 11: set result to be the nth word from the string
    std::cout << "TODO: implement string_nth_word(\"" << STR << "\", " << N << ")" << std::endl;
    return result;
}

vector<string> string_tokenize(const string STR, const char DELIMINATOR) {
    vector<string> result;
    // TODO 12: split the string by the given deliminator
    std::cout << "TODO: implement string_tokenize(\"" << STR << "\", '" << DELIMINATOR << "')" << std::endl;
    return result;
}

string string_substitute(const string STR, const char TARGET, const char REPLACEMENT)  {
    string result = STR;
    // TODO 13: set result to be the string with all instances of TARGET replaced
    std::cout << "TODO: implement string_substitute(\"" << STR << "\", '" << TARGET << "', '" << REPLACEMENT << "')" << std::endl;
    return result;
}

string string_to_lower(const string STR) {
    string result = STR;
    // TODO 14: convert all characters to lower case
    std::cout << "TODO: implement string_to_lower(\"" << STR << "\")" << std::endl;
    return result;
}

string string_to_upper(const string STR) {
    string result = STR;
    // TODO 15: convert all characters to upper case
    std::cout << "TODO: implement string_to_upper(\"" << STR << "\")" << std::endl;
    return result;
}

int string_compare(const string LHS, const string RHS) {
    int result = 0;
    // TODO 16: compare LHS and RHS
    std::cout << "TODO: implement string_compare(\"" << LHS << "\", \"" << RHS << "\")" << std::endl;
    return result;
}