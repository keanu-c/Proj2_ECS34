#include "XMLReader.h"

struct CXMLReader::SImplementation {
    SImplementation(std::shared_ptr< CDataSource > src) {
        // details
    }
    bool End() const {

    }
    bool ReadEntity(SXMLEntity &entity, bool skipcdata = false) {

    }
};

CXMLReader::CXMLReader(std::shared_ptr< CDataSource > src) {
    DImplementation = std::make_unique<SImplementation>(src);
}

CXMLReader::~CXMLReader() {

}
bool CXMLReader::End() const {
    return DImplementation->End();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata = false) {
    return DImplementation->ReadEntity(entity, skipcdata);
}
