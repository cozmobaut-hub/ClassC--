/* CSCI 200: A3 - Green Eggs and Ham Classes
 *
 * Author: Austin Haas

 * 
 *
 */


// first include our custom headers
#include "InputProcessor.h"     // our custom InputProcessor class
#include "OutputProcessor.h"    // our custom OutputProcessor class
#include "StreamUtility.h"      // our custom StreamUtillit class

// then include standard library headers
#include <iostream>             // for cerr, cin, cout, endl, istream, ostream
#include <string>               // for string
#include <vector>               // for vector

/**
 * @brief performs data analysis of word and letter counts
 * @return int error code status
 */
int main() {
    StreamUtility util;                                 // create a stream utility object

    InputProcessor iProcessor;                          // create an input processor object
    std::istream* inputStream = util.selectInput();     // select a stream to input from
    if(inputStream == nullptr) {                        // if no stream could be opened, quit the program
        std::cerr << "Error opening input stream, shutting down" 
                  << std::endl;
        return -1;
    }
    iProcessor.readFromStream( *inputStream );          // read the data on the stream
    if(inputStream != &std::cin) delete inputStream;    // if we read from a file, delete the file stream object
    iProcessor.sanitizeWords( "?!.,;:\"()_-'&[]" );     // remove the specified punctuation

    // retrieve all the words read from the stream
    std::vector< std::string > allWords = iProcessor.getAllWords();

    OutputProcessor oProcessor;                         // create an output processor object
    oProcessor.analyzeWords( allWords );                // perform data analysis on word and letter counts
    std::ostream* outputStream = util.selectOutput();   // select a stream to output to
    if(outputStream == nullptr) {                       // if no stream could be opened, quit the program
        std::cerr << "Error opening output stream, shutting down" 
                 << std::endl;
        return -2;
    }
    oProcessor.writeToStream( *outputStream );          // write the data to the stream
    if(outputStream != &std::cout) delete outputStream; // if we wrote to a file, delete the file stream object

    std::cout << "Analysis complete, verify results"    // signal to user program has completed
              << std::endl;
    
    return 0;                                           // end our program!
}
