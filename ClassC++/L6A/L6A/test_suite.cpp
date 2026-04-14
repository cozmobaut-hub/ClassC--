#include "test_suite.h"

#include "Array.hpp"
#include "LinkedList.hpp"
\
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

const int MESSAGE_WIDTH = 40;

const std::string PASSED_MESSAGE = "    PASSED   \n";

void print_test_row(
	const int TEST_NUM,
	const std::string MESSAGE,
	const std::string RESULT
) {
    std::cout << "Test #" << std::setw(3) << std::right << TEST_NUM;
    std::cout << std::setw(MESSAGE_WIDTH) << std::right;
    std::cout << MESSAGE << ": ";
    std::cout << std::left;
    std::cout << RESULT;
}

int test_int(
	int &testNum,
	const std::string MESSAGE,
	const int LHS,
	const int RHS
)  {
    std::string result;
    if (LHS == RHS) {
        result = PASSED_MESSAGE;
    } else {
        result = " !!>FAILED<!! Returned: \"";
        result += std::to_string(LHS);
        result += "\" != Expected: \"";
        result += std::to_string(RHS);
        result += "\"\n";
    }
    print_test_row(++testNum, MESSAGE, result);
    return LHS == RHS ? 1 : 0;
}

int test_not_null(
	int &testNum,
	const std::string MESSAGE,
	const void* LHS
)  {
    std::string result;
    if (LHS != nullptr) {
        result = PASSED_MESSAGE;
    } else {
        result = " !!>FAILED<!! Returned: \"";
        result += std::to_string((unsigned long long)LHS);
        result += "\" != Expected: \"0x0\"\n";
    }
    print_test_row(++testNum, MESSAGE, result);
    return LHS != nullptr ? 1 : 0;
}

int test_exception(
	int& testNum,
	const std::string MESSAGE,
	const bool EXCEPTION_THROWN
) {
    std::string result;
    if (EXCEPTION_THROWN)
        result = PASSED_MESSAGE;
    else
        result = " !!>FAILED<!! Exception thrown when it shouldn't\n";
    print_test_row(++testNum, MESSAGE, result);
    return EXCEPTION_THROWN ? 1 : 0;
}

int test_exception_not(
	int& testNum,
	const std::string MESSAGE,
	const bool EXCEPTION_NOT_THROWN
) {
    std::string result;
    if (EXCEPTION_NOT_THROWN)
        result = " !!>FAILED<!! This should not occur, function was used incorrectly\n";
    else
        result = " !!>FAILED<!! Exception not thrown when it should\n";
    print_test_row(++testNum, MESSAGE, result);
    return 0;
}

void print_header_top() {
    std::cout << std::endl;
    std::cout << "/" << std::setw(MESSAGE_WIDTH*2) << std::setfill('-') << std::right << "\\" << std::endl;
    std::cout << std::setfill(' ');
}

void print_header_row(
	const std::string MESSAGE
) {
    const int MSG_LEN = static_cast<int>( MESSAGE.length() );
    const int BOX_WIDTH = MESSAGE_WIDTH*2 + 2;
    const int PADDING_LEFT = (BOX_WIDTH - MSG_LEN) / 2 ;
    const int PADDING_RIGHT = (BOX_WIDTH - MSG_LEN) / 2 + (MSG_LEN % 2 ? 1 : 0);
    std::cout << std::setw(PADDING_LEFT) << std::left << "|" << MESSAGE << std::setw(PADDING_RIGHT) << std::right << "|\n";

}

void print_header_bottom() {
    std::cout << "\\" << std::setw(MESSAGE_WIDTH*2) << std::setfill('-') << std::right << "/" << std::endl;
    std::cout << std::setfill(' ');
}

void print_header(
	const std::string SECTION_HEADER
) {
    print_header_top();
    print_header_row(SECTION_HEADER);
    print_header_bottom();
}

bool run_all_tests(
	const int NUM_TESTS_TO_RUN = 9999,
	const int LIST_TYPE = 1
)  {
    int totalPassed = 0, totalNumTests = 0;

	IList<int>* pList = nullptr;

	// testing constructor
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) print_header("Testing construction of empty list - List is {}");

		if( LIST_TYPE == 1 ) {
			try {
				totalPassed += test_not_null(       totalNumTests, "Testing Array()", pList = new Array<int>() );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing Array()", false );
			}
		} else {
			try {
				totalPassed += test_not_null(       totalNumTests, "Testing LinkedList()", pList = new LinkedList<int>() );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing LinkedList()", false );
			}
		}
	}

    // testing empty list
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) print_header("Testing new empty list - List is {}");

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(0)", pList->get(0) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(0,0);
                totalPassed += test_exception_not(totalNumTests, "Testing set(0,0)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(0,0)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(-1,-1);
                totalPassed += test_exception_not(totalNumTests, "Testing set(-1,-1)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(-1,-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(1,1);
                totalPassed += test_exception_not(totalNumTests, "Testing set(1,1)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(1,1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(0);
                totalPassed += test_exception_not(totalNumTests, "Testing remove(0)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(0)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing min()", pList->min() && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing max()", pList->max() && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
    }

    // testing insert value 3 at position 0
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {}");
            print_header_row("Inserting value 3 at position 0");
            print_header_row("List is now {3}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(0, 3);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(0, 3)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(0, 3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
    }

    // testing set position 0 to 5
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {3}");
            print_header_row("Setting position 0 to 5");
            print_header_row("List is now {5}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(0,5);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing set(0, 5)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(0,5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
    }

    // testing set position -1 to 7
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {5}");
            print_header_row("Setting position -1 to 7");
            print_header_row("List is now {5}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(-1,7);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing set(-1, 7)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(-1,7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
    }

    // testing set position 1 to 9
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {5}");
            print_header_row("Setting position 1 to 9");
            print_header_row("List is now {5}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(1,9);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing set(1, 9)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(1,1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
    }

    // testing remove position 0
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {5}");
            print_header_row("Removing position 0");
            print_header_row("List is now {}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(0);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(0)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(0)", pList->get(0) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(0,0);
                totalPassed += test_exception_not(totalNumTests, "Testing set(0,0)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(0,0)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(-1,-1);
                totalPassed += test_exception_not(totalNumTests, "Testing set(-1,-1)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(-1,-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(1,1);
                totalPassed += test_exception_not(totalNumTests, "Testing set(1,1)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(1,1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(0);
                totalPassed += test_exception_not(totalNumTests, "Testing remove(0)", false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(0)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing min()", pList->min() && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing max()", pList->max() && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
    }

    // testing insert at head
    // testing insert at head
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {}");
            print_header_row("Inserting value 5 at position 0");
            print_header_row("Inserting value 1 at position 0");
            print_header_row("List is now {1,5}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(0, 5);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(0, 5)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(0, 5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(0, 1);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(0, 1)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(0, 1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(2)", pList->get(2) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
    }

    // testing insert at tail
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {1,5}");
            print_header_row("Inserting value 9 at position 2");
            print_header_row("List is now {1,5,9}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(2, 9);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(2, 9)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(2, 9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(3)", pList->get(3) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
    }

    // testing insert after head
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {1,5,9}");
            print_header_row("Inserting value 3 at position 1");
            print_header_row("List is now {1,3,5,9}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(1, 3);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(1, 3)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(1, 3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(4)", pList->get(4) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
    }

    // testing insert before tail
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {1,3,5,9}");
            print_header_row("Inserting value 7 at position 3");
            print_header_row("List is now {1,3,5,7,9}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(3, 7);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(3, 7)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(3, 7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 7);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(4)", pList->get(4), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(5)", pList->get(5) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
    }

    // testing insert before head
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {1,3,5,7,9}");
            print_header_row("Inserting value 9 at position -10");
            print_header_row("List is now {9,1,3,5,7,9}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(-10, 9);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(-10, 9)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(-10, 9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 6);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(4)", pList->get(4), 7);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(5)", pList->get(5), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
    }

    // testing insert after tail
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {9,1,3,5,7,9}");
            print_header_row("Inserting value 1 at position 10");
            print_header_row("List is now {9,1,3,5,7,9,1}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->insert(10, 1);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing insert(10, 1)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing insert(10, 1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 7);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(4)", pList->get(4), 7);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(5)", pList->get(5), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(6)", pList->get(6), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 6);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
    }

    // testing min in middle
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {9,1,3,5,7,9,1}");
            print_header_row("Setting position 2 to -100");
            print_header_row("List is now {9,1,-100,5,7,9,1}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(2, -100);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing set(2, -100)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(2, -100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 7);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), -100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(4)", pList->get(4), 7);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(5)", pList->get(5), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(6)", pList->get(6), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), -100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 6);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
    }

    // testing max in middle
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {9,1,-100,5,7,9,1}");
            print_header_row("Setting position 4 to 100");
            print_header_row("List is now {9,1,-100,5,100,9,1}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->set(4, 100);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing set(4, 100)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing set(4, 100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 7);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), -100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(4)", pList->get(4), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(5)", pList->get(5), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(6)", pList->get(6), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), -100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 6);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

    // testing remove from middle
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {9,1,-100,5,100,9,1}");
            print_header_row("Removing position 2");
            print_header_row("List is now {9,1,5,100,9,1}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(2);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(2)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(2)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 6);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(4)", pList->get(4), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(5)", pList->get(5), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing frind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

    // testing remove from middle
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {9,1,5,100,9,1}");
            print_header_row("Removing position 2");
            print_header_row("List is now {9,1,100,9,1}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(2);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(2)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(2)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 5);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(4)", pList->get(4), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(5)", pList->get(5) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

    // testing remove from middle
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {9,1,100,9,1}");
            print_header_row("Removing position 1");
            print_header_row("List is now {9,100,9,1}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(1);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(1)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 4);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(3)", pList->get(3), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(4)", pList->get(4) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(5)", pList->get(5) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

    // testing remove from before head
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {9,100,9,1}");
            print_header_row("Removing position -1");
            print_header_row("List is now {100,9,1}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(-1);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(-1)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(-1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 3);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(2)", pList->get(2), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(3)", pList->get(3) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(4)", pList->get(4) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(5)", pList->get(5) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

    // testing remove from after tail
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {100,9,1}");
            print_header_row("Removing position 3");
            print_header_row("List is now {100,9}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(3);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(3)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 2);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(1)", pList->get(1), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(2)", pList->get(2) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(3)", pList->get(3) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(4)", pList->get(4) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(5)", pList->get(5) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 9);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

    // testing remove tail
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {100,9}");
            print_header_row("Removing position 1");
            print_header_row("List is now {100}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(1);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(1)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing get(0)", pList->get(0), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(2)", pList->get(2) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(3)", pList->get(3) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(4)", pList->get(4) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(5)", pList->get(5) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing min()", pList->min(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing max()", pList->max(), 100);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

    // testing remove head
    if(NUM_TESTS_TO_RUN > totalNumTests) {
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("List was {100}");
            print_header_row("Removing position 0");
            print_header_row("List is now {}");
            print_header_bottom();
        }

        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                pList->remove(0);
                totalPassed++;
                print_test_row(++totalNumTests, "Testing remove(0)", PASSED_MESSAGE);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing remove(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing size()", pList->size(), 0);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing size()", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(0)", pList->get(0) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(0)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(1)", pList->get(1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(2)", pList->get(2) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(2)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(3)", pList->get(3) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(3)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(4)", pList->get(4) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(4)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(5)", pList->get(5) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(5)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(6)", pList->get(6) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(6)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(-1)", pList->get(-1) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(-1)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing get(7)", pList->get(7) && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing get(7)", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing min()", pList->min() && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing min()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_exception_not(totalNumTests, "Testing max()", pList->max() && false);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing max()", true );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(0)", pList->find(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(3)", pList->find(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(1)", pList->find(1), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(5)", pList->find(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(7)", pList->find(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(9)", pList->find(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(-100)", pList->find(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing find(100)", pList->find(100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing find(100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(0)", pList->rfind(0), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(0)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(3)", pList->rfind(3), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(3)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(1)", pList->rfind(1), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(1)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(5)", pList->rfind(5), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(5)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(7)", pList->rfind(7), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(7)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(9)", pList->rfind(9), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(9)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(-100)", pList->rfind(-100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(-100)", false );
            }
        }
        if(totalNumTests < NUM_TESTS_TO_RUN) {
            try {
                totalPassed += test_int(          totalNumTests, "Testing rfind(100)", pList->rfind(100), -1);
            } catch (...) {
                totalPassed += test_exception(    totalNumTests, "Testing rfind(100)", false );
            }
        }
    }

	// testing destructor on empty list
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) print_header("Testing destructor of empty list - List is {}");

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 1
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {5}");
            print_header_row("Testing destructor on list of size 1");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 5);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 2
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {5}");
            print_header_row("Inserting element at start {1, 5}");
            print_header_row("Testing destructor on list of size 2");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 5);
		pList->insert(-1, 1);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 2
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {5}");
            print_header_row("Inserting element at end {5, 10}");
            print_header_row("Testing destructor on list of size 2");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 5);
		pList->insert(5, 10);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {5}");
            print_header_row("Inserting element at beginning {1, 5}");
            print_header_row("Inserting element at end {1, 5, 10}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 5);
		pList->insert(-1, 1);
		pList->insert(5, 10);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {5}");
            print_header_row("Inserting element at end {5, 10}");
            print_header_row("Inserting element at beginning {1, 5, 10}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 5);
		pList->insert(5, 10);
		pList->insert(-1, 1);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {1}");
            print_header_row("Inserting element at end {1, 10}");
            print_header_row("Inserting element in middle {1, 5, 10}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 1);
		pList->insert(5, 10);
		pList->insert(1, 5);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 5, 10}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 5);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 4
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Testing destructor on list of size 4");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element in middle {1, 6, 10}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(1);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element in middle {1, 3, 10}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(2);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element at beginning {3, 6, 10}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(0);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 3
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element at end {1, 3, 6}");
            print_header_row("Testing destructor on list of size 3");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(4);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 2
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element at end {1, 3, 6}");
            print_header_row("Removing element at end {1, 3}");
            print_header_row("Testing destructor on list of size 2");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(4);
		pList->remove(4);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 2
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element at end {1, 3, 6}");
            print_header_row("Removing element at beginning {3, 6}");
            print_header_row("Testing destructor on list of size 2");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(4);
		pList->remove(-1);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 2
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element in middle {1, 3, 10}");
            print_header_row("Removing element at beginning {3, 10}");
            print_header_row("Testing destructor on list of size 2");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(2);
		pList->remove(-1);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 2
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element in middle {1, 3, 10}");
            print_header_row("Removing element in middle {1, 10}");
            print_header_row("Testing destructor on list of size 2");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(2);
		pList->remove(1);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 1
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element in middle {1, 3, 10}");
            print_header_row("Removing element in middle {1, 10}");
            print_header_row("Removing element at beginning {10}");
            print_header_row("Testing destructor on list of size 1");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(2);
		pList->remove(1);
		pList->remove(0);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

	// testing destructor on list of size 0
	if(NUM_TESTS_TO_RUN > totalNumTests ) {
		if(totalNumTests < NUM_TESTS_TO_RUN) {
            print_header_top();
            print_header_row("Constructing empty list {}");
            print_header_row("Inserting element into empty list {10}");
            print_header_row("Inserting element at beginning {1, 10}");
            print_header_row("Inserting element in middle {1, 3, 10}");
            print_header_row("Inserting element in middle {1, 3, 6, 10}");
            print_header_row("Removing element in middle {1, 3, 10}");
            print_header_row("Removing element in middle {1, 10}");
            print_header_row("Removing element at beginning {10}");
            print_header_row("Removing element at beginning {}");
            print_header_row("Testing destructor on list of size 0");
            print_header_bottom();
        }

		if( LIST_TYPE == 1 ) {
			pList = new Array<int>();
		} else {
			pList = new LinkedList<int>();
		}

		pList->insert(0, 10);
		pList->insert(-1, 1);
		pList->insert(1, 3);
		pList->insert(2, 6);
		pList->remove(2);
		pList->remove(1);
		pList->remove(0);
		pList->remove(0);

		if( LIST_TYPE == 1 ) {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~Array()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~Array()", false );
			}
		} else {
			try {
				delete pList;
				++totalPassed;
				++totalNumTests;
				print_test_row( totalNumTests, "Testing ~LinkedList()", "PASSED\n" );
			} catch (...) {
				totalPassed += test_exception(      totalNumTests, "Testing ~LinkedList()", false );
			}
		}
	}

    print_header("Sanity Check");

    std::cout << std::endl;
    std::cout << "Tests Passed: " << std::setw(3) << std::right << totalPassed << " / " << std::setw(3) << totalNumTests
			  << " (" << std::setprecision(0) << std::fixed << totalPassed * 100.0f / totalNumTests << "%)"
			  << std::endl << std::endl;

    return (totalPassed == totalNumTests);
}

class Timer {
public:
    Timer() { _clockState = CLOCK_UNSTARTED; }
    void startClock() { _startTime = std::chrono::high_resolution_clock::now(); _clockState = CLOCK_RUNNING; }
    void stopClock() { _endTime = std::chrono::high_resolution_clock::now(); _clockState = CLOCK_STOPPED; }
    double elapsedTime() {
        if(_clockState == CLOCK_UNSTARTED) { return 0.0; }
        if(_clockState == CLOCK_RUNNING) {
            _endTime = std::chrono::high_resolution_clock::now();
        }
        return std::chrono::duration<double>(_endTime - _startTime).count();
    }
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> _startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> _endTime;
    unsigned short _clockState;
    const unsigned short CLOCK_UNSTARTED = 0;
    const unsigned short CLOCK_RUNNING = 1;
    const unsigned short CLOCK_STOPPED = 2;
};

template<typename T>
void run_timed_tests(
	IList<T>* const pList,
	const int SIZE,
	const std::string LABEL,
	const T VALUE,
	const int MANIPULATE_POS,
	const std::string COST_1,
	const std::string COST_2,
	const std::string COST_3,
	const std::string COST_4
) {
    std::cout << std::setw(21) << std::left << LABEL << std::flush;

    //-------------------------------------------------------------------------------------
    // INSERT TEST
    Timer insertTimer;
    insertTimer.startClock();
    for(int i = 0; i <= SIZE; i++) {
        try {
            pList->insert(i+MANIPULATE_POS, VALUE);
        } catch (std::out_of_range& oore) {
            std::cerr << "Caught std::out_of_range \"" << oore.what() << "\" on insert() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (std::exception &e) {
            std::cerr << "Caught std::exception \"" << e.what() << "\" on insert() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (...) {
            std::cerr << "Caught unknown exception on insert() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        }
        if( i % (SIZE / 10) == 0 ) {
            std::cout << "\r" << std::setw(21) << std::left << LABEL << "[";
            std::string progressBar = "";
            for(int j = 0; j < i*10 / SIZE; j++ ) {
                progressBar += "x";
            }
            std::cout << std::setw(10) << std::left << progressBar << "]" << std::setw(10) << std::right << insertTimer.elapsedTime() << "s " << COST_1 << std::flush;
        }
    }
    insertTimer.stopClock();

    //-------------------------------------------------------------------------------------
    //  READ  TEST
    Timer readTimer;
    readTimer.startClock();
    for(int i = 0; i <= SIZE; i++) {
        try {
            pList->get(i);
        } catch (std::out_of_range& oore) {
            std::cerr << "Caught std::out_of_range \"" << oore.what() << "\" on get() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (std::exception &e) {
            std::cerr << "Caught std::exception \"" << e.what() << "\" on get() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (...) {
            std::cerr << "Caught unknown exception on get() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        }
        if( i % (SIZE / 10) == 0 ) {
            std::cout << "\r" << std::setw(21) << std::left << LABEL
                 << "[xxxxxxxxxx]" << std::setw(10) << std::right << insertTimer.elapsedTime() << "s " << COST_1 << " [";
            std::string progressBar = "";
            for(int j = 0; j < i*10 / SIZE; j++ ) {
                progressBar += "x";
            }
            std::cout << std::setw(10) << std::left << progressBar << "]" << std::setw(10) << std::right << readTimer.elapsedTime() << "s " << COST_2 << std::flush;
        }
    }
    readTimer.stopClock();

    //-------------------------------------------------------------------------------------
    //  WRITE TEST
    Timer writeTimer;
    writeTimer.startClock();
    for(int i = 0; i <= SIZE; i++) {
        try {
            pList->set(i, VALUE);
        } catch (std::out_of_range& oore) {
            std::cerr << "Caught std::out_of_range \"" << oore.what() << "\" on set() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (std::exception &e) {
            std::cerr << "Caught std::exception \"" << e.what() << "\" on set() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (...) {
            std::cerr << "Caught unknown exception on set() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        }
        if( i % (SIZE / 10) == 0 ) {
            std::cout << "\r" << std::setw(21) << std::left << LABEL
                 << "[xxxxxxxxxx]" << std::setw(10) << std::right << insertTimer.elapsedTime() << "s " << COST_1
                 << " [xxxxxxxxxx]"<< std::setw(10) << std::right << readTimer.elapsedTime() << "s " << COST_2 << " [";
            std::string progressBar = "";
            for(int j = 0; j < i*10 / SIZE; j++ ) {
                progressBar += "x";
            }
            std::cout << std::setw(10) << std::left << progressBar << "]" << std::setw(10) << std::right << writeTimer.elapsedTime() << "s " << COST_3 << std::flush;
        }
    }
    writeTimer.stopClock();

    //-------------------------------------------------------------------------------------
    // DELETE TEST
    Timer deleteTimer;
    deleteTimer.startClock();
    for(int i = 0; i <= SIZE; i++) {
        try {
            pList->remove(pList->size() - (i+MANIPULATE_POS));
        } catch (std::out_of_range& oore) {
            std::cerr << "Caught std::out_of_range \"" << oore.what() << "\" on remove() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (std::exception &e) {
            std::cerr << "Caught std::exception \"" << e.what() << "\" on remove() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        } catch (...) {
            std::cerr << "Caught unknown exception on remove() iteration " << i << "...halting tests" << std::endl;
            std::cout << std::endl;
            return;
        }
        if( i % (SIZE / 10) == 0 ) {
            std::cout << "\r" << std::setw(21) << std::left << LABEL
                 << "[xxxxxxxxxx]" << std::setw(10) << std::right << insertTimer.elapsedTime() << "s " << COST_1
                 << " [xxxxxxxxxx]"<< std::setw(10) << std::right << readTimer.elapsedTime() << "s " << COST_2
                 << " [xxxxxxxxxx]" << std::setw(10) << std::right << writeTimer.elapsedTime() << "s " << COST_3 << " [";
            std::string progressBar = "";
            for(int j = 0; j < i*10 / SIZE; j++ ) {
                progressBar += "x";
            }
            std::cout << std::setw(10) << std::left << progressBar << "]" << std::setw(10) << std::right << deleteTimer.elapsedTime() << "s " << COST_4 << std::flush;
        }
    }
    deleteTimer.stopClock();
    std::cout << std::endl;
}

void run_stress_tests() {
    const int TEST_SIZE = 100000;

    std::cout << std::setw(17) << std::left << "\t #  List Type";
    std::cout << std::setw(19) << std::right << "Insert";
    std::cout << std::setw(29) << std::right << "Read";
    std::cout << std::setw(29) << std::right << "Write";
    std::cout << std::setw(30) << std::right << "Delete" << std::endl;

    std::cout << std::fixed << std::setprecision(6);

    IList<int> *pList = new Array<int>();
    run_timed_tests(pList, TEST_SIZE, "\t1/6 Array Head", 0, -TEST_SIZE-1, "O(n)", "O(1)", "O(1)", "O(n)");
    delete pList;

    pList = new Array<int>();
    run_timed_tests(pList, TEST_SIZE, "\t2/6 Array Mid", 0, -1, "O(n)", "O(1)", "O(1)", "O(n)");
    delete pList;

    pList = new Array<int>();
    run_timed_tests(pList, TEST_SIZE, "\t3/6 Array Tail", 0, TEST_SIZE+1, "O(n)", "O(1)", "O(1)", "O(n)");
    delete pList;

    pList = new LinkedList<int>();
    run_timed_tests(pList, TEST_SIZE, "\t4/6 LinkedList Head", 0, -TEST_SIZE-1, "O(1)", "O(n)", "O(n)", "O(1)");
    delete pList;

    pList = new LinkedList<int>();
    run_timed_tests(pList, TEST_SIZE, "\t5/6 LinkedList Mid", 0, -1, "O(n)", "O(n)", "O(n)", "O(n)");
    delete pList;

    pList = new LinkedList<int>();
    run_timed_tests(pList, TEST_SIZE, "\t6/6 LinkedList Tail", 0, TEST_SIZE+1, "O(1)", "O(n)", "O(n)", "O(1)");
    delete pList;
}
