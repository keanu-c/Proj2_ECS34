#include "XMLWriter.h"

struct CXMLWriter::SImplementation {
    SImplementation(std::shared_ptr< CDataSink > sink) {
        // details here
    }
    bool Flush(){
        // write
    }
    bool WriteEntity(const SXMLEntity &entity) {
        // write
    }
};

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink) {
    DImplementation = std::make_unique<SImplementation>(sink);
}

CXMLWriter::~CXMLWriter() {

}
bool CXMLWriter::Flush() {
    return DImplementation->Flush();
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {
    return DImplementation->WriteEntity(entity);
}