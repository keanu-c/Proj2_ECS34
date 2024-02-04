#include "DSVWriter.h"
#include "StringUtils.h"

struct CDSVWriter::SImplementation {
    std::shared_ptr< CDataSink > DDataSink;
    char Delimiter;
    bool Quoteall;
    bool ContainsRow;
    
    SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
        DDataSink = sink;
        if (delimiter == '"')
            Delimiter = ',';
        else
            Delimiter = delimiter;
        Quoteall = quoteall;
        ContainsRow = false; // initialize to false when constructing class
    }

    // Used AI
    // Turns string into vector of characters
    std::vector<char> StringToVectOfChar (const std::string &string) {
        return std::vector<char>(string.begin(), string.end());
    }

    bool WriteRow(const std::vector<std::string> &row) {
        // CDataSink object not created
        if (!DDataSink) return false;
        // Prepend newline if there's already a string
        if (ContainsRow) {
            DDataSink->Put('\n');
        }
        // Input row is empty
        if (row.empty()) {
            std::vector<char> EmptyString;
            DDataSink->Write(EmptyString);
        }
        // Iterate through vector of strings
        for (size_t i = 0; i < row.size(); i++) {
            // Append delimiter if it's not the first string and the last string
            if ((i != 0) && (i != row.size())) {
                DDataSink->Put(Delimiter);
            }
            // Create new string to edit
            std::string currentString = row[i];
            // Find every double quote, newline, or delimiter in string and quote it with double quotes
            currentString = StringUtils::Replace(currentString, "\"", "\"\"");
            currentString = StringUtils::Replace(currentString, "\n", "\"\n\"");
            currentString = StringUtils::Replace(currentString, std::string(1,Delimiter), '\"' + std::string(1, Delimiter) + '\"');
            
            // Quote all strings and then write to DataSink
            if (Quoteall) {
                std::vector<char> String = StringToVectOfChar(currentString);
                String.insert(String.begin(), '\"'); // prepend double quote
                String.push_back('\"'); // append a double quote
                DDataSink->Write(String);
            }
            // Write string to DataSink if it doesn't need to be quoted
            else {
                DDataSink->Write(StringToVectOfChar(currentString));
            }
            ContainsRow = true; // DataSink now contains a row
        }
        return true;
    }
};


CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
    DImplementation = std::make_unique<SImplementation>(sink,delimiter,quoteall);
}

CDSVWriter::~CDSVWriter() {
}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
    return DImplementation->WriteRow(row);
}