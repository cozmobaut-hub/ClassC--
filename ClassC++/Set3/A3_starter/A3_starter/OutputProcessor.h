#ifndef OUTPUT_PROCESSOR_H
#define OUTPUT_PROCESSOR_H

#include <iostream>
#include <vector>
#include <string>

class OutputProcessor {
private:
    std::vector<std::string>       uniqueWords;
    std::vector<unsigned long>     uniqueWordCounts;
    std::vector<unsigned long>     letterCounts; // 26 letters

    long findWordIndex(const std::string& w) const;
    std::size_t countDigits(unsigned long x) const;

    void computeWordStats(unsigned long& totalWords,
                          std::size_t& maxIdx,
                          std::size_t& minIdx) const;
    void computeLetterStats(unsigned long& totalLetters,
                            std::size_t& maxIdx,
                            std::size_t& minIdx) const;

    void maybeSortWords(); // extra credit

public:
    OutputProcessor();

    void analyzeWords(const std::vector<std::string>& allWords);
    void writeToStream(std::ostream& out) const;
};

#endif
