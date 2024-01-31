#include "DSVWriter.h"

struct CDSVWriter::SImplementation {
    SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
        // details here
        // 
    }

    bool WriteRow(const std::vector<std::string> &row) {
        // majority of code here
        // taking in the row string from the test and put it into the right format in the buffer.
        // 
    }
};


CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall = false) {
    DImplementation = std::make_unique<SImplementation>(sink,delimiter,quoteall);
}

CDSVWriter::~CDSVWriter() {
    // maybe dont write anything
}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
    return DImplementation->WriteRow(row);
}
