#include "test_suite.h"
#include "string_functions.h"

#include <iomanip>
#include <iostream>
using namespace std;

const int MESSAGE_WIDTH = 45;

int test_int(int& testNum, const string MESSAGE, const int LHS, const int RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS == RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" != Expected: \"" << RHS << "\"\n";
    return LHS == RHS ? 1 : 0;
}

int test_size_t(int& testNum, const string MESSAGE, const size_t LHS, const size_t RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS == RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" != Expected: \"" << RHS << "\"\n";
    return LHS == RHS ? 1 : 0;
}

int test_char(int& testNum, const string MESSAGE, const char LHS, const char RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS == RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" != Expected: \"" << RHS << "\"\n";
    return LHS == RHS ? 1 : 0;
}

int test_string(int& testNum, const string MESSAGE, const string LHS, const string RHS)  {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;
    if (LHS == RHS)
        cout << "    PASSED   \n";
    else
        cout << " !!>FAILED<!! Returned: \"" << LHS << "\" != Expected: \"" << RHS << "\"\n";
    return LHS == RHS ? 1 : 0;
}

int test_vector_string(int& testNum, const string MESSAGE, const vector<string>& LHS, const vector<string>& RHS) {
    cout << "Test #" << setw(3) << right << ++testNum;
    cout << setw(MESSAGE_WIDTH) << right;
    cout << MESSAGE << ": ";
    cout << left;

    bool vectorsMatch = (LHS.size() == RHS.size());
    if (vectorsMatch) {
        for(unsigned int i = 0; i < LHS.size(); i++) {
            if(LHS.at(i) != RHS.at(i)) {
                vectorsMatch = false;
                break;
            }
        }
    }
    if (vectorsMatch) {
        cout << "    PASSED   \n";
    } else {
        cout << " !!>FAILED<!! Returned: {";
        for(unsigned int i = 0; i < LHS.size(); i++) {
            cout << "\"" << LHS.at(i) << "\"";
            if(i < LHS.size() - 1) {
                cout << ", ";
            }
        }
        cout << "} != Expected: {";
        for(unsigned int i = 0; i < RHS.size(); i++) {
            cout << "\"" << RHS.at(i) << "\"";
            if(i < RHS.size() - 1) {
                cout << ", ";
            }
        }
        cout << "}\n";
    }
    return vectorsMatch ? 1 : 0;
}

bool run_all_tests()  {
    int totalPassed = 0, totalNumTests = 0;
    totalPassed += test_size_t(        totalNumTests,  "Testing string_length()",              string_length("Now") , 3 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_length()",              string_length("Tablet") , 6 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_length()",              string_length("The length is 17.") , 17 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_length()",              string_length("A") , 1 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_length()",              string_length("string_length()") , 15 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_length()",              string_length("") , 0 );
    cout << endl;

    totalPassed += test_char(          totalNumTests,  "Testing string_char_at()",             string_char_at("Elephant", 3) , 'p' );
    totalPassed += test_char(          totalNumTests,  "Testing string_char_at()",             string_char_at("Giraffe", 2) , 'r' );
    totalPassed += test_char(          totalNumTests,  "Testing string_char_at()",             string_char_at("Armadillo", 4) , 'd' );
    totalPassed += test_char(          totalNumTests,  "Testing string_char_at()",             string_char_at("Armadillo", 1) , 'r' );
    totalPassed += test_char(          totalNumTests,  "Testing string_char_at()",             string_char_at("Armadillo", 0) , 'A' );
    totalPassed += test_char(          totalNumTests,  "Testing string_char_at()",             string_char_at("Armadillo", 3) , 'a' );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_append()",              string_append("There's a ", "natural mystic.") , "There's a natural mystic." );
    totalPassed += test_string(        totalNumTests,  "Testing string_append()",              string_append("There's a", " natural mystic.") , "There's a natural mystic." );
    totalPassed += test_string(        totalNumTests,  "Testing string_append()",              string_append("It's the ", "eye of the tiger.") , "It's the eye of the tiger." );
    totalPassed += test_string(        totalNumTests,  "Testing string_append()",              string_append("Some", "thing") , "Something" );
    totalPassed += test_string(        totalNumTests,  "Testing string_append()",              string_append("", "Nothing to something.") , "Nothing to something." );
    totalPassed += test_string(        totalNumTests,  "Testing string_append()",              string_append("Not adding anything.", "") , "Not adding anything." );
    totalPassed += test_string(        totalNumTests,  "Testing string_append()",              string_append("", "") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_append() twice",        string_append("A", string_append("B", "C")) , "ABC" );
    totalPassed += test_string(        totalNumTests,  "Testing string_append() twice",        string_append("A ", string_append("B ", "C")) , "A B C" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_insert()",              string_insert("If you carefully.", "listen ", 7) , "If you listen carefully." );
    totalPassed += test_string(        totalNumTests,  "Testing string_insert()",              string_insert("carefully.", "Watch ", 0) , "Watch carefully." );
    totalPassed += test_string(        totalNumTests,  "Testing string_insert()",              string_insert("Iner", "t", 2) , "Inter" );
    totalPassed += test_string(        totalNumTests,  "Testing string_insert()",              string_insert("", "TA DA!", 0) , "TA DA!" );
    totalPassed += test_string(        totalNumTests,  "Testing string_insert()",              string_insert("TA DA!", "", 0) , "TA DA!" );
    totalPassed += test_string(        totalNumTests,  "Testing string_insert()",              string_insert("TA DA!", "", 2) , "TA DA!" );
    totalPassed += test_string(        totalNumTests,  "Testing string_insert()",              string_insert("", "", 0) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_insert() thrice",       string_insert(string_insert("Iner ", "t", 2),
                                                                                                             string_insert("Mil", "an", 3),
                                                                                                             6),
                                                                                                             "Inter Milan" );
    cout << endl;

    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Have to face reality now.", 'o') , 6 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Have to face reality now.", 'e') , 3 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Have to face reality now.", 'r') , 13 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Have to face reality now.", 'a') , 1 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Will you find it?", 'o') , 6 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Will you find it?", 'l') , 2 );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Will you find it?", 'L') , string::npos );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Have to face reality now.", 'q') , string::npos );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("Have to face reality now.", 'h') , string::npos );
    totalPassed += test_size_t(        totalNumTests,  "Testing string_find()",                string_find("", '?') , string::npos );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_substring()",           string_substring("Such a natural mystic", 7, 7) , "natural" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substring()",           string_substring("Such a natural mystic", 8, 2) , "at" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substring()",           string_substring("Such a natural mystic", 0, 4) , "Such" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substring()",           string_substring("Something to nothing.", 0, 0) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substring()",           string_substring("Something to nothing.", 10, 0) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substring()",           string_substring("", 0, 0) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substring() twice",     string_substring(string_substring("Such a natural mystic", 0, 4), 1, 2), "uc" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_replace()",             string_replace("Strings are not the way", "Strings", "Things") , "Things are not the way" );
    totalPassed += test_string(        totalNumTests,  "Testing string_replace()",             string_replace("Strings are not the way", "not the", "the") , "Strings are the way" );
    totalPassed += test_string(        totalNumTests,  "Testing string_replace()",             string_replace("Show me the things", "things", "way") , "Show me the way" );
    totalPassed += test_string(        totalNumTests,  "Testing string_replace()",             string_replace("Show me the things", "car", "way") , "Show me the things" );
    totalPassed += test_string(        totalNumTests,  "Testing string_replace()",             string_replace("Show me the things", "the ", "") , "Show me things" );
    totalPassed += test_string(        totalNumTests,  "Testing string_replace()",             string_replace("", "now what?", "hmm") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_replace()",             string_replace("", "now", "") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_replace() thrice",      string_replace(string_replace(string_replace("Take me on", "me", "xyz"), "on", "me"), "xyz", "on") , "Take on me" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_first_word()",          string_first_word("The quick brown fox jumped over the lazy dog") , "The" );
    totalPassed += test_string(        totalNumTests,  "Testing string_first_word()",          string_first_word("A man a plan a canal Panama") , "A" );
    totalPassed += test_string(        totalNumTests,  "Testing string_first_word()",          string_first_word("I have the hang of this") , "I" );
    totalPassed += test_string(        totalNumTests,  "Testing string_first_word()",          string_first_word("Testing string_first_word()") , "Testing" );
    totalPassed += test_string(        totalNumTests,  "Testing string_first_word()",          string_first_word("Single") , "Single" );
    totalPassed += test_string(        totalNumTests,  "Testing string_first_word()",          string_first_word("Uh oh") , "Uh" );
    totalPassed += test_string(        totalNumTests,  "Testing string_first_word()",          string_first_word("") , "" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word()",   string_remove_first_word("The quick brown fox jumped over the lazy dog") , "quick brown fox jumped over the lazy dog" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word()",   string_remove_first_word("Testing string_remove_first_word()") , "string_remove_first_word()" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word()",   string_remove_first_word("Goodbye") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word()",   string_remove_first_word("") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word() twice",string_remove_first_word(string_remove_first_word("The quick brown fox jumped over the lazy dog")) , "brown fox jumped over the lazy dog" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word() twice",string_remove_first_word(string_remove_first_word("Testing string_remove_first_word()")) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word() twice",string_remove_first_word(string_remove_first_word("Goodbye")) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word() twice",string_remove_first_word(string_remove_first_word("")) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word() thrice",string_remove_first_word(string_remove_first_word(string_remove_first_word("The quick brown fox jumped over the lazy dog"))) , "fox jumped over the lazy dog" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word() thrice",string_remove_first_word(string_remove_first_word(string_remove_first_word("Testing string_remove_first_word()"))) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_remove_first_word() thrice",string_remove_first_word(string_remove_first_word(string_remove_first_word("Goodbye"))) , "" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_second_word()",         string_second_word("The quick brown fox jumped over the lazy dog") , "quick" );
    totalPassed += test_string(        totalNumTests,  "Testing string_second_word()",         string_second_word("A man a plan a canal Panama") , "man" );
    totalPassed += test_string(        totalNumTests,  "Testing string_second_word()",         string_second_word("Testing string_second_word()") , "string_second_word()" );
    totalPassed += test_string(        totalNumTests,  "Testing string_second_word()",         string_second_word("I have the hang of this") , "have" );
    totalPassed += test_string(        totalNumTests,  "Testing string_second_word()",         string_second_word("Uh oh") , "oh" );
    totalPassed += test_string(        totalNumTests,  "Testing string_second_word()",         string_second_word("Single") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_second_word()",         string_second_word("") , "" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_third_word()",          string_third_word("The quick brown fox jumped over the lazy dog") , "brown" );
    totalPassed += test_string(        totalNumTests,  "Testing string_third_word()",          string_third_word("A man a plan a canal Panama") , "a" );
    totalPassed += test_string(        totalNumTests,  "Testing string_third_word()", 	       string_third_word("I have the hang of this") , "the" );
    totalPassed += test_string(        totalNumTests,  "Testing string_third_word()", 	       string_third_word("Uh oh no") , "no" );
    totalPassed += test_string(        totalNumTests,  "Testing string_third_word()", 	       string_third_word("Uh oh") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_third_word()", 	       string_third_word("Single") , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_third_word()", 	       string_third_word("") , "" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(1)",           string_nth_word("The quick brown fox jumped over the lazy dog", 1) , "The" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(2)",           string_nth_word("The quick brown fox jumped over the lazy dog", 2) , "quick" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(3)",           string_nth_word("The quick brown fox jumped over the lazy dog", 3) , "brown" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(4)",           string_nth_word("The quick brown fox jumped over the lazy dog", 4) , "fox" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(5)",           string_nth_word("The quick brown fox jumped over the lazy dog", 5) , "jumped" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(6)",           string_nth_word("The quick brown fox jumped over the lazy dog", 6) , "over" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(7)",           string_nth_word("The quick brown fox jumped over the lazy dog", 7) , "the" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(8)",           string_nth_word("The quick brown fox jumped over the lazy dog", 8) , "lazy" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(9)",           string_nth_word("The quick brown fox jumped over the lazy dog", 9) , "dog" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(10)",          string_nth_word("The quick brown fox jumped over the lazy dog", 10) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(11)",          string_nth_word("The quick brown fox jumped over the lazy dog", 11) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(1)",           string_nth_word("", 1) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(2)",           string_nth_word("", 2) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(3)",           string_nth_word("", 3) , "" );
    totalPassed += test_string(        totalNumTests,  "Testing string_nth_word(10)",          string_nth_word("", 10) , "" );
    cout << endl;

    vector<string> tokens1 = {"The", "quick", "brown", "fox", "jumped", "over", "the", "lazy", "dog"};
    totalPassed += test_vector_string( totalNumTests,  "Testing string_tokenize()",            string_tokenize("The quick brown fox jumped over the lazy dog", ' '), tokens1 );
    totalPassed += test_vector_string( totalNumTests,  "Testing string_tokenize()",            string_tokenize("The@quick@brown@fox@jumped@over@the@lazy@dog", '@'), tokens1 );

    vector<string> tokens2 = {"The quick brown fox jumped over the lazy dog"};
    totalPassed += test_vector_string( totalNumTests,  "Testing string_tokenize()",            string_tokenize("The quick brown fox jumped over the lazy dog", '*'), tokens2 );
    
    vector<string> tokens3 = {""};
    totalPassed += test_vector_string( totalNumTests,  "Testing string_tokenize()",            string_tokenize("", '*'), tokens3 );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_substitute()",          string_substitute("The Gxxgle", 'x', 'o') , "The Google" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substitute()",          string_substitute("$chool of Mine$", '$', 's') , "school of Mines" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substitute()",          string_substitute("$chool of Mine$", '+', '*') , "$chool of Mine$" );
    totalPassed += test_string(        totalNumTests,  "Testing string_substitute() twice",    string_substitute(string_substitute("D--", '-', '+'), 'D', 'C') , "C++" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_to_lower()",            string_to_lower("This SHOULD be LOWER case") , "this should be lower case" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_lower()",            string_to_lower("MNASDF874792L[]//.;[\t],") , "mnasdf874792l[]//.;[\t]," );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_lower()",            string_to_lower("C++") , "c++" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_lower()",            string_to_lower("this is already lower case") , "this is already lower case" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_lower()",            string_to_lower("1234567890,./;'[]") , "1234567890,./;'[]" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_lower()",            string_to_lower("") , "" );
    cout << endl;

    totalPassed += test_string(        totalNumTests,  "Testing string_to_upper()",            string_to_upper("This SHOULD be upper case") , "THIS SHOULD BE UPPER CASE" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_upper()",            string_to_upper("mnasdf874792l[]//.;[\t],") , "MNASDF874792L[]//.;[\t]," );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_upper()",            string_to_upper("c++") , "C++" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_upper()",            string_to_upper("THIS IS ALREADY UPPER CASE") , "THIS IS ALREADY UPPER CASE" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_upper()",            string_to_upper("1234567890,./;'[]") , "1234567890,./;'[]" );
    totalPassed += test_string(        totalNumTests,  "Testing string_to_upper()",            string_to_upper("") , "" );
    cout << endl;

    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("C", "C") , 0 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("Cat", "Cat") , 0 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("Cat", "cat") , -1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("cat", "Cat") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("cat", "category") , -1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("category", "cat") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("C++", "c++") , -1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("C++", "C++") , 0 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("c++", "c++") , 0 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("c++", "C++") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("short", "shorter") , -1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("longer", "long") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("after", "later") , -1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("later", "after") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("G", "g") , -1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("g", "G") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("GoOse", "Bye") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("Equal", "Equal") , 0 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("Not Empty", "") , 1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("", "Not Empty") , -1 );
    totalPassed += test_int(           totalNumTests,  "Testing string_compare()",             string_compare("", "") , 0 );
    cout << endl;

    cout << "Tests Passed: " << setw(3) << right << totalPassed << " / " << setw(3) << totalNumTests << " (" << setprecision(0) << fixed << totalPassed * 100.0f / totalNumTests << "%)" << endl << endl;
    
    return (totalPassed == totalNumTests);
}
