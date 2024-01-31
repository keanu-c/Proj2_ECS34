#include "DSVReader.h"

struct CDSVReader::SImplementation {
    SImplementation(std::shared_ptr< CDataSource > src, char delimiter) {
        // details here
    }
    bool End() const {
        // write
    }
    bool ReadRow(std::vector<std::string> &row) {
        // write
    }
};

CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter) {
    DImplementation = std::make_unique<SImplementation>(src, delimiter);
}

CDSVReader::~CDSVReader(){

}
bool CDSVReader::End() const {
    return DImplementation->End();
}

bool CDSVReader::ReadRow(std::vector<std::string> &row) {
    return DImplementation->ReadRow(row);
}