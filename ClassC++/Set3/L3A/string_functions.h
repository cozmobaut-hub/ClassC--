#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include <string>
#include <vector>

/**
 * @brief Returns the length of a string
 * @param STR string to return the length of
 * @return length of the input string
 */
size_t string_length(const std::string STR);

/**
 * @brief Returns the character of a string at a given index
 * @param STR full string
 * @param IDX index to access string at
 * @return character from STR at index IDX
 */
char string_char_at(const std::string STR, const size_t IDX);

/**
 * @brief Returns a concatenation of strings left and right
 * @param LEFT string to be appended to
 * @param RIGHT string to be appended
 * @return concatenated string LEFTRIGHT
 */
std::string string_append(const std::string LEFT, const std::string RIGHT);

/**
 * @brief Returns the result of inserting a string into another at a given position
 * @param STR original string
 * @param TO_INSERT string to be inserted into STR
 * @param IDX location within STR to insert TO_INSERT
 * @return a new string with TO_INSERT inserted at index IDX of STR
 */
std::string string_insert(const std::string STR, const std::string TO_INSERT, const size_t IDX);

/**
 * @brief Returns the first index of a character in a string
 * @param STR string to search within (the haystack)
 * @param C character to search for (the needle)
 * @return if found, first position within STR that C is located.  otherwise returns string::npos
 */
size_t string_find(const std::string STR, const char C);

/**
 * @brief Returns part of a string
 * @param STR original full string
 * @param IDX starting position to return a substring from
 * @param LEN length of substring to return
 * @return a substring of length LEN from STR
 */
std::string string_substring(const std::string STR, const size_t IDX, const size_t LEN);

/**
 * @brief Replaces part of a string
 * @param STR original full string (the haystack)
 * @param TEXT_TO_REPLACE the existing text to replace (the needle)
 * @param REPLACE_WITH the new text to insert
 * @return modified string (if text found), otherwise the original string
 */
std::string string_replace(const std::string STR, const std::string TEXT_TO_REPLACE, const std::string REPLACE_WITH);

/**
 * @brief Returns the first word, given a sentence
 * @param STR original full string
 * @return substring up to the first whitespace
 */
std::string string_first_word(const std::string STR);

/**
 * @brief Returns the string with the first word removed
 * @param STR original full string
 * @return substring after the first whitespace
 */
std::string string_remove_first_word(const std::string STR);

/**
 * @brief Returns the second word, given a sentence
 * @param STR original full string
 * @return substring after the first whitespace up to the second whitespace
 */
std::string string_second_word(const std::string STR);

/**
 * @brief Returns the third word, given a sentence
 * @param STR original full string
 * @return substring after the second whitespace up to the third whitespace
 */
std::string string_third_word(const std::string STR);

/**
 * @brief Returns the nth word, given a sentence
 * @param STR original full string
 * @param N word within STR to return (beginning at 1)
 * @return corresponding word from STR
 */
std::string string_nth_word(const std::string STR, const int N);

/**
 * @brief Splits a string into a list of tokens deliminated by a given character
 * 
 * @param STR string to tokenize
 * @param DELIMINATOR character to split on
 * @return vector<string> list of all tokens in the order present in the original string
 */
std::vector<std::string> string_tokenize(const std::string STR, const char DELIMINATOR);

/**
 * @brief Returns a string substituting target character with replacement character
 * @param STR original full string (the haystack)
 * @param TARGET character to replace (the needle)
 * @param REPLACEMENT character to substitute with
 * @return string with all instance of TARGET replaced with REPLACEMENT
 */
std::string string_substitute(const std::string STR, const char TARGET, const char REPLACEMENT);

/**
 * @brief Returns a string with all uppercase characters converted to lowercase characters
 * 
 * @param STR original string
 * @return string with lowercase characters
 */
std::string string_to_lower(const std::string STR);

/**
 * @brief Returns a string with all lowercase characters converted to uppercase characters
 * 
 * @param STR original string
 * @return string with uppercase characters
 */
std::string string_to_upper(const std::string STR);

/**
 * @brief Compares two strings to determine their ordering or equality.  Returns -1 if 
 * LHS < RHS.  Returns 0 if LHS == RHS.  Returns 1 if LHS > RHS
 * 
 * @param LHS left hand string
 * @param RHS right hand string
 * @return int representing relationship of LHS to RHS
 */
int string_compare(const std::string LHS, const std::string RHS);

#endif