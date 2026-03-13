#include "OutputProcessor.h"

#include <iomanip>

OutputProcessor::OutputProcessor()
    : uniqueWords(),
      uniqueWordCounts(),
      letterCounts(26, 0) {
}

long OutputProcessor::findWordIndex(const std::string& w) const {
    for (std::size_t i = 0; i < uniqueWords.size(); ++i) {
        if (uniqueWords[i] == w) {
            return static_cast<long>(i);
        }
    }
    return -1;
}

std::size_t OutputProcessor::countDigits(unsigned long x) const {
    if (x == 0) return 1;
    std::size_t c = 0;
    while (x > 0) {
        ++c;
        x /= 10;
    }
    return c;
}

void OutputProcessor::computeWordStats(unsigned long& totalWords,
                                       std::size_t& maxIdx,
                                       std::size_t& minIdx) const {
    totalWords = 0;
    maxIdx = 0;
    minIdx = 0;
    if (uniqueWordCounts.empty()) {
        return;
    }

    for (std::size_t i = 0; i < uniqueWordCounts.size(); ++i) {
        totalWords += uniqueWordCounts[i];
        if (uniqueWordCounts[i] > uniqueWordCounts[maxIdx]) {
            maxIdx = i;
        }
        if (uniqueWordCounts[i] < uniqueWordCounts[minIdx]) {
            minIdx = i;
        }
        // ties -> keep first
    }
}

void OutputProcessor::computeLetterStats(unsigned long& totalLetters,
                                         std::size_t& maxIdx,
                                         std::size_t& minIdx) const {
    totalLetters = 0;
    maxIdx = 0;
    minIdx = 0;

    for (std::size_t i = 0; i < letterCounts.size(); ++i) {
        totalLetters += letterCounts[i];
        if (letterCounts[i] > letterCounts[maxIdx]) {
            maxIdx = i;
        }
        if (letterCounts[i] < letterCounts[minIdx]) {
            minIdx = i;
        }
        // ties -> keep lower index (earlier alphabet)
    }
}

void OutputProcessor::analyzeWords(const std::vector<std::string>& allWords) {
    uniqueWords.clear();
    uniqueWordCounts.clear();
    for (std::size_t i = 0; i < letterCounts.size(); ++i) {
        letterCounts[i] = 0;
    }

    for (std::size_t i = 0; i < allWords.size(); ++i) {
        const std::string& w = allWords[i];
        if (w.empty()) {
            continue;
        }

        long idx = findWordIndex(w);
        if (idx == -1) {
            uniqueWords.push_back(w);
            uniqueWordCounts.push_back(1);
        } else {
            uniqueWordCounts[static_cast<std::size_t>(idx)]++;
        }

        for (std::size_t j = 0; j < w.size(); ++j) {
            char ch = w[j];
            if (ch >= 'A' && ch <= 'Z') {
                letterCounts[static_cast<std::size_t>(ch - 'A')]++;
            } else if (ch >= 'a' && ch <= 'z') {
                letterCounts[static_cast<std::size_t>(ch - 'a')]++;
            }
        }
    }

    maybeSortWords();
}

void OutputProcessor::maybeSortWords() {
    if (uniqueWords.empty()) {
        return;
    }

    char ans;
    while (true) {
        std::cout << "Do you wish to sort the words (Y|N): ";
        if (!(std::cin >> ans)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (ans == 'Y' || ans == 'y' || ans == 'N' || ans == 'n') {
            break;
        }
    }

    if (ans == 'N' || ans == 'n') {
        return;
    }

    char how;
    while (true) {
        std::cout << "Do you wish to sort by (W)ord or (C)ount? ";
        if (!(std::cin >> how)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        if (how == 'W' || how == 'w' || how == 'C' || how == 'c') {
            break;
        }
    }

    std::size_t n = uniqueWords.size();

    if (how == 'W' || how == 'w') {
        // selection sort alphabetically by word
        for (std::size_t i = 0; i + 1 < n; ++i) {
            std::size_t minPos = i;
            for (std::size_t j = i + 1; j < n; ++j) {
                if (uniqueWords[j] < uniqueWords[minPos]) {
                    minPos = j;
                }
            }
            if (minPos != i) {
                std::string tmpW = uniqueWords[i];
                uniqueWords[i] = uniqueWords[minPos];
                uniqueWords[minPos] = tmpW;

                unsigned long tmpC = uniqueWordCounts[i];
                uniqueWordCounts[i] = uniqueWordCounts[minPos];
                uniqueWordCounts[minPos] = tmpC;
            }
        }
    } else {
        // selection sort by count desc, ties alphabetically
        for (std::size_t i = 0; i + 1 < n; ++i) {
            std::size_t best = i;
            for (std::size_t j = i + 1; j < n; ++j) {
                if (uniqueWordCounts[j] > uniqueWordCounts[best]) {
                    best = j;
                } else if (uniqueWordCounts[j] == uniqueWordCounts[best] &&
                           uniqueWords[j] < uniqueWords[best]) {
                    best = j;
                }
            }
            if (best != i) {
                std::string tmpW = uniqueWords[i];
                uniqueWords[i] = uniqueWords[best];
                uniqueWords[best] = tmpW;

                unsigned long tmpC = uniqueWordCounts[i];
                uniqueWordCounts[i] = uniqueWordCounts[best];
                uniqueWordCounts[best] = tmpC;
            }
        }
    }
}

void OutputProcessor::writeToStream(std::ostream& out) const {
    unsigned long totalWords = 0;
    std::size_t maxWordIdx = 0, minWordIdx = 0;
    computeWordStats(totalWords, maxWordIdx, minWordIdx);

    out << "Analyzed " << totalWords << " total words\n";
    out << "Counted " << uniqueWords.size() << " unique words\n";

    std::size_t longestWordLen = 0;
    unsigned long maxCount = 0;
    for (std::size_t i = 0; i < uniqueWords.size(); ++i) {
        if (uniqueWords[i].size() > longestWordLen) {
            longestWordLen = uniqueWords[i].size();
        }
        if (uniqueWordCounts[i] > maxCount) {
            maxCount = uniqueWordCounts[i];
        }
    }
    std::size_t countWidth = countDigits(maxCount);

    // word/count table
    for (std::size_t i = 0; i < uniqueWords.size(); ++i) {
        out << std::left << std::setw(static_cast<int>(longestWordLen))
            << uniqueWords[i]
            << " - "
            << std::right << std::setw(static_cast<int>(countWidth))
            << uniqueWordCounts[i]
            << "\n";
    }

    if (!uniqueWords.empty()) {
        std::size_t wordFieldWidth =
            uniqueWords[maxWordIdx].size() > uniqueWords[minWordIdx].size()
                ? uniqueWords[maxWordIdx].size()
                : uniqueWords[minWordIdx].size();

        out << " Most Frequent Word: "
            << std::left << std::setw(static_cast<int>(wordFieldWidth))
            << uniqueWords[maxWordIdx] << " "
            << std::right << std::setw(static_cast<int>(countWidth))
            << uniqueWordCounts[maxWordIdx] << " ("
            << std::setw(7) << std::fixed << std::setprecision(3)
            << (totalWords == 0 ? 0.0 :
                100.0 * uniqueWordCounts[maxWordIdx] /
                static_cast<double>(totalWords))
            << "%)\n";

        out << "Least Frequent Word: "
            << std::left << std::setw(static_cast<int>(wordFieldWidth))
            << uniqueWords[minWordIdx] << " "
            << std::right << std::setw(static_cast<int>(countWidth))
            << uniqueWordCounts[minWordIdx] << " ("
            << std::setw(7) << std::fixed << std::setprecision(3)
            << (totalWords == 0 ? 0.0 :
                100.0 * uniqueWordCounts[minWordIdx] /
                static_cast<double>(totalWords))
            << "%)\n";
    }

    // letter table width matches word table width
    int totalWidth = static_cast<int>(longestWordLen + 3 + countWidth);

    unsigned long totalLetters = 0;
    std::size_t maxLetterIdx = 0, minLetterIdx = 0;
    computeLetterStats(totalLetters, maxLetterIdx, minLetterIdx);

    for (int i = 0; i < 26; ++i) {
        char letter = static_cast<char>('A' + i);
        out << letter;
        std::size_t digits = countDigits(
            letterCounts[static_cast<std::size_t>(i)]);
        int dots = totalWidth - 1 - static_cast<int>(digits);
        if (dots < 0) dots = 0;
        for (int d = 0; d < dots; ++d) {
            out << ".";
        }
        out << letterCounts[static_cast<std::size_t>(i)] << "\n";
    }

    // common width for letter counts in stats lines
    unsigned long maxLetterCount = 0;
    for (std::size_t i = 0; i < letterCounts.size(); ++i) {
        if (letterCounts[i] > maxLetterCount) {
            maxLetterCount = letterCounts[i];
        }
    }
    int letterCountWidth = static_cast<int>(countDigits(maxLetterCount));

    out << " Most Frequent Letter: "
        << static_cast<char>('A' + static_cast<int>(maxLetterIdx)) << " "
        << std::right << std::setw(letterCountWidth)
        << letterCounts[maxLetterIdx] << " ("
        << std::setw(7) << std::fixed << std::setprecision(3)
        << (totalLetters == 0 ? 0.0 :
            100.0 * letterCounts[maxLetterIdx] /
            static_cast<double>(totalLetters))
        << "%)\n";

    out << "Least Frequent Letter: "
        << static_cast<char>('A' + static_cast<int>(minLetterIdx)) << " "
        << std::right << std::setw(letterCountWidth)
        << letterCounts[minLetterIdx] << " ("
        << std::setw(7) << std::fixed << std::setprecision(3)
        << (totalLetters == 0 ? 0.0 :
            100.0 * letterCounts[minLetterIdx] /
            static_cast<double>(totalLetters))
        << "%)\n";
}
