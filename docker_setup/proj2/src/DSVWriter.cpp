#include "DSVWriter.h"

struct CDSWriter::SImplementation {
    SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
        // details here
    }

    bool WriteRow(const std::vector<std::string> &row) {

    }
};


CDSWriter::(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall = false) {
    DImplementation = std::make_unique<Implementation>(sink,delimiter,quoteall);
}

CDSWriter::~CDSWriter() {

}

bool CDSWriter::WriteRow(const std::vector<std::string> &row) {
    return DImplementation->WriteRow(row);
}
