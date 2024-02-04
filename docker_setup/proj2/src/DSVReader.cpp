#include "DSVReader.h"

struct CDSVReader::SImplementation {
    std::shared_ptr< CDataSource > DDatasource;
    char Delimiter;
    
    SImplementation(std::shared_ptr< CDataSource > src, char delimiter) {
        DDatasource = src;
        Delimiter = delimiter;
    }
    
    bool End() const {
        char info;
        if (!DDatasource->Peek(info)) {
        return true;
    }   else {
        return false;
    }
}

    bool ReadRow(std::vector<std::string> &row) {
        std::string line;
        char info;
        // Read characters until a newline is encountered
        while (DDatasource->Get(info) && info != '\n') { 
            line += info;
        }

        std::string data;
        size_t i = 0;
        size_t j = line.length();
        // Look through string until delimiter is found
        while ((j = line.find(Delimiter, i)) != std::string::npos) {
            data = line.substr(i, j - i); // Store all index before delimiter
            row.push_back(data); // Add stored index to row
            i = j + 1; // Move to the next character after the delimiter
        }
        row.push_back(line.substr(i)); // Add the last data
        return true;
    }
};
// Constructor
CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter) {
    DImplementation = std::make_unique<SImplementation>(src, delimiter);
}
// Destructor
CDSVReader::~CDSVReader(){ 
}
// Method
bool CDSVReader::End() const {
    return DImplementation->End();
}
// Method
bool CDSVReader::ReadRow(std::vector<std::string> &row) {
    return DImplementation->ReadRow(row);
}