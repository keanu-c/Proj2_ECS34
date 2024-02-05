#include "XMLReader.h"
#include <expat.h>
#include <queue>

// creating the parser
// free the parser
// to parse
// handler functions, get called when the expat parser officially parses something


struct CXMLReader::SImplementation {
    std::shared_ptr< CDataSource > DDataSource;
    XML_Parser DXMLParser;
    std::queue<SXMLEntity> DEntityQueue;

    // handles start elements during XML parsing
    void StartElementHandler(const std::string &name, const std::vector<std::string> &attrs) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name; // sets XML element name
        TempEntity.DType = SXMLEntity::EType::StartElement; // sets element type to 'StartElement'
        for(size_t index = 0; index < attrs.size(); index += 2) { // adds attributes 
            TempEntity.SetAttribute(attrs[index], attrs[index + 1]);
        }
        DEntityQueue.push(TempEntity);
    }
    void EndElementHandler(const std::string &name) {
        SXMLEntity TempEntity;
        TempEntity.DNameData = name;
        TempEntity.DType = SXMLEntity::EType::EndElement; // has no attributes so no need for a for loop
        DEntityQueue.push(TempEntity);
    }
    void CharacterElementHandler(const std::string &cdata) {
        // might want to update the back entity to see if it is a character data
        // CHATGPT
        if (!DEntityQueue.empty() && DEntityQueue.back().DType == SXMLEntity::EType::CharData) {
            // Update the back entity if needed
            DEntityQueue.back().DNameData += cdata;
        } else {
            SXMLEntity TempEntity;
            TempEntity.DNameData = cdata;
            TempEntity.DType = SXMLEntity::EType::CharData; // has no attributes so no need for a for loop
            DEntityQueue.push(TempEntity);
        }
    }
    
    
    // Event handler callback
    static void StartElementHandlerCallback(void *context, const XML_Char *name, const XML_Char **atts){
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        std::vector<std::string> Attributes;
        auto AttrPtr = atts;
        while (*AttrPtr) {
            // taking a char pointer and pushing it back to the Attributes, so it needs to convert a char pointer to a std::string which it knows how to do
            Attributes.push_back(*AttrPtr);
            AttrPtr++;
        }
        ReaderObject->StartElementHandler(name, Attributes);
    };
    static void EndElementHandlerCallback(void *context, const XML_Char *name){
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->EndElementHandler(name);
    };
    static void ChatacterDataHandlerCallback(void *context, const XML_Char *s, int len) {
        SImplementation *ReaderObject = static_cast<SImplementation *>(context);
        ReaderObject->CharacterElementHandler(std::string(s, len));
    };
    
    SImplementation(std::shared_ptr< CDataSource > src) {
        DDataSource = src;
        DXMLParser = XML_ParserCreate(NULL);
        XML_SetStartElementHandler(DXMLParser, StartElementHandlerCallback);
        XML_SetEndElementHandler(DXMLParser, EndElementHandlerCallback);
        XML_SetCharacterDataHandler(DXMLParser, ChatacterDataHandlerCallback);
        XML_SetUserData(DXMLParser, this);
    };
    bool End() const {
        if(DEntityQueue.empty() && DDataSource->End()) {
            return true;
        } else {
            return false;
        }
    };
    bool ReadEntity(SXMLEntity &entity, bool skipcdata = false) {
        // Read from the src
        // Pass to XML_Parse()
        // Return entity
        std::vector<char> DataBuffer;
        while(DEntityQueue.empty()) {
            if (DDataSource->Read(DataBuffer, 512)) {
                XML_Parse(DXMLParser, DataBuffer.data(), DataBuffer.size(), DataBuffer.size() < 512);
            }
            else {
                XML_Parse(DXMLParser, DataBuffer.data(), 0, true);
                //
                break;
            }
        }
        if(DEntityQueue.empty()) {
            return false;
        }
        // Skip CharData
        if (skipcdata) {
            if (DEntityQueue.front().DType == SXMLEntity::EType::CharData) {
                DEntityQueue.pop();
            }
        }
        entity = DEntityQueue.front();
        DEntityQueue.pop();
        return true;
    };
};

CXMLReader::CXMLReader(std::shared_ptr< CDataSource > src) {
    DImplementation = std::make_unique<SImplementation>(src);
}

CXMLReader::~CXMLReader() {

}
bool CXMLReader::End() const {
    return DImplementation->End();
}

bool CXMLReader::ReadEntity(SXMLEntity &entity, bool skipcdata) {
    return DImplementation->ReadEntity(entity, skipcdata);
}
