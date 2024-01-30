#include "StringUtils.h"
#include <cctype>
#include <cmath>
#include <algorithm> // for min();

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    if (start < 0) {
        start = str.length() + start;
    } else if (end < 0) {
        end = str.length() + end;
    } else if (start > str.length()) {
        return "";
    }
    return str.substr(start, str.length()-start);
}
std::string Capitalize(const std::string &str) noexcept{

    auto copy = str;
    copy[0] = toupper(copy[0]);
    for (size_t index = 1; index < copy.length(); index++) {
        copy[index] = tolower(copy[index]);
    }
    return copy;
}
std::string Upper(const std::string &str) noexcept{

    auto copy = str;
    for (size_t index = 0; index < copy.length(); index++) {
        copy[index] = toupper(copy[index]);
    }
    return copy;
}

std::string Lower(const std::string &str) noexcept{

    auto copy = str;
    for (size_t index = 0; index < copy.length(); index++) {
        copy[index] = tolower(copy[index]);
    }
    return copy;
}

std::string LStrip(const std::string &str) noexcept{

    auto copy = str;
    // Used: [C++ Remove leading or trailing characters](https://raymii.org/s/snippets/Cpp_Remove_leading_or_trailing_characters_from_string.html)
    for (size_t index = 0; index < copy.length(); index++) {
        if (copy[index] != ' ') {
            copy.erase(0, std::min(index, copy.length() - index));
            break;
        }
    }
    return copy;
}

std::string RStrip(const std::string &str) noexcept{

    auto copy = str;
    // Used: [C++ Remove leading or trailing characters](https://raymii.org/s/snippets/Cpp_Remove_leading_or_trailing_characters_from_string.html)
    for (size_t index = copy.length(); index > 0; index--) {
        if (copy[index - 1] != ' ') {
            copy.erase(index, std::string::npos);
            break;
        }
    }
    return copy;
}

std::string Strip(const std::string &str) noexcept{

    auto copy = str;
    // Combined both LStrip() and RStrip() 
    for (size_t index = 0; index < copy.length(); index++) {
        if (copy[index] != ' ') {
            copy.erase(0, std::min(index, copy.length() - index));
            break;
        }
    }
    for (size_t index = copy.length(); index > 0; index--) {
        if (copy[index - 1] != ' ') {
            copy.erase(index, std::string::npos);
            break;
        }
    }
    return copy;
}

// Used .insert method for all centering functions: [How to prepend in C++](https://stackoverflow.com/questions/8468597/prepend-stdstring)
std::string Center(const std::string &str, int width, char fill) noexcept{

    auto copy = str;
    int char_needed = width - copy.length();
    if (char_needed % 2 == 0) {
        copy.append(char_needed/2, fill);
        copy.insert(0, char_needed/2, fill);
    } else {
        copy.append((floor(char_needed/2) + 1), fill);
        copy.insert(0, floor(char_needed/2), fill);
    }
    return copy;
}

std::string LJust(const std::string &str, int width, char fill) noexcept{
    
    auto copy = str;
    int char_needed = width - copy.length();
    copy.append(char_needed, fill);
    return copy;
}

std::string RJust(const std::string &str, int width, char fill) noexcept{
    
    auto copy = str;
    int char_needed = width - copy.length();
    copy.insert(0, char_needed, fill);
    return copy;
}

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{

    auto copy = str;
    size_t found = copy.find(old); 
    while (found != std::string::npos) {
        copy.erase(found, old.length());
        copy.insert(found, rep);
        found = copy.find(old);
    }
    return copy;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    

    auto char_to_splt = splt;
    if (char_to_splt == "") {
        char_to_splt = ' ';
    }
    auto copy = str;
    std::string temp = "";
    std::vector< std::string > split_str;
    for (size_t index = 0; index < copy.length(); index++) {
        if (copy.substr(index, char_to_splt.length()) != char_to_splt) {
            temp = temp + copy[index];
            if (index + 1 == copy.length() || copy.substr(index + 1, char_to_splt.length()) == char_to_splt) {
                split_str.push_back(temp);
                temp = "";
            }
        }
    }
    return split_str;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::string joinString;
    for (size_t index = 0; index < vect.size(); index++) {
        joinString.append(vect[index]);
        if (index != vect.size() - 1) {
            joinString.append(str);
        }
    }
    return joinString;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    auto copy = str;
    std::string spaced_str;
    int align = 0;
    for (size_t index = 0; index < copy.length(); index++) {
        if (copy[index] == '\t') {
            int spaces_tabstop = tabsize - (align % tabsize);
            for (int i = 0; i < spaces_tabstop; i++) {
                spaced_str = spaced_str + ' ';
                align++;
            }
        } else {
            spaced_str = spaced_str + copy[index];
            align++;

        }
    }
    return spaced_str;
}

//[Wagner-Fischer algorithm](https://en.wikipedia.org/wiki/Wagner%E2%80%93Fischer_algorithm)
//[guilhermeagostinelli Levenshtein implementation](https://github.com/guilhermeagostinelli/levenshtein/blob/master/levenshtein.cpp)
int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    // Deals with case-insensitive
    std::string copy1, copy2;
    if (ignorecase == true) {
        copy1 = Lower(left);
        copy2 = Lower(right);
    } else {
        copy1 = left;
        copy2 = right;
    }

    int size1 = copy1.size();
    int size2 = copy2.size();
    int matrix[size1 + 1][size2 + 1];
    // If string is empty then distance is the other string 
    if (size1 == 0)
        return size2;
    if (size2 == 0)
        return size1;
    // Fill matrix with indices of each string
    for (int i = 0; i <= size1; i++) {
        matrix[i][0] = i;
    }
    for (int j = 0; j <= size2; j++) {
        matrix[0][j] = j;
    }
    int substitutionCost;
    // Calculate cost by comparing each character substring and filling the matrix with cost numbers
    for (int i = 1; i <= size1; i++) {
        for (int j = 1; j <= size2; j++) {
            if (copy1[i - 1] == copy2[j - 1]) {
                substitutionCost = 0;
            } else {
                substitutionCost = 1;
            }
            matrix[i][j] = std::min((matrix[i - 1][j] + 1, matrix[i][j - 1] + 1), matrix[i - 1][j - 1] + substitutionCost);
        }
    }
    // return last position of matrix that contains the 'distance'
    return matrix[size1][size2];
}

};