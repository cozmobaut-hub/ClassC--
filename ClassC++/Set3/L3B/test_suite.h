#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <string>
#include <vector>

/** 
 * @brief Test suite. Runs all tests.
 * @return true if all tests pass, false otherwise
 */
bool run_all_tests();

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_int(int& testNum, const std::string MESSAGE, const int LHS, const int RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_unsigned_long(int& testNum, const std::string MESSAGE, const unsigned long LHS, const unsigned long RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_char(int& testNum, const std::string MESSAGE, const char LHS, const char RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_string(int& testNum, const std::string MESSAGE, const std::string LHS, const std::string RHS);

/**
 * @brief A generic test function, that simply prints "PASSED" if LHS equals RHS 
 * and otherwise prints FAILED. Do not modify this function.
 * 
 * @param testNum Number of the test.  Value will be incremented upon completion
 * @param MESSAGE description of test
 * @param LHS computed result
 * @param RHS expected result
 * @return 1 if test passed, 0 otherwise
 */
int test_vector_string(int& testNum, const std::string MESSAGE, const std::vector<std::string>& LHS, const std::vector<std::string>& RHS);

#endif