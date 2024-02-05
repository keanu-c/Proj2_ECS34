#include "XMLWriter.h"
#include <expat.h>
#include "StringUtils.h"
#include <stack>

struct CXMLWriter::SImplementation {
    std::shared_ptr< CDataSink > DDataSink;
    std::string StringXML;
    std::stack <std::string> OpenElements;

    SImplementation(std::shared_ptr< CDataSink > sink) {
        DDataSink = sink;
    }
    // Used AI
    // Turns string into vector of characters
    std::vector<char> StringToVectOfChar (const std::string &string) {
        return std::vector<char>(string.begin(), string.end());
    }
    // Replaces special characters in a string
    void ReplaceSpecialChar(std::string &String) {
        String = StringUtils::Replace(String, "&", "&amp;");
        String = StringUtils::Replace(String, "<", "&lt;");
        String = StringUtils::Replace(String, ">", "&gt;");
        String = StringUtils::Replace(String, "\"", "&quot;");
        String = StringUtils::Replace(String, "\'", "&apos;");
    }
    // add EndElement to all StartElements that havent been "ended"
    bool Flush(){
        while(!OpenElements.empty()) {
            StringXML = "</" + OpenElements.top() + '>';
            OpenElements.pop();
            DDataSink->Write(StringToVectOfChar(StringXML));
        }
        return true;
    }

    bool WriteEntity(const SXMLEntity &entity) {
        if (!DDataSink) return false;
        // Initialize string with NameData of XMLEntity
        StringXML = entity.DNameData;
        // Replace special characters in the NameData
        ReplaceSpecialChar(StringXML);

        if (entity.DType == SXMLEntity::EType::StartElement || entity.DType == SXMLEntity::EType::CompleteElement) {
            // Add opening tag
            StringXML = '<' + StringXML;
            
            // CHATGPT: How would you iterate over DAttributes?
            // Adds attributes to string
            for (const auto &attribute : entity.DAttributes) {
                std::string attributeName = attribute.first;
                std::string attributeValue = attribute.second;
                ReplaceSpecialChar(attributeName); ReplaceSpecialChar(attributeValue);
                StringXML = StringXML + ' ' + attributeName + "=\"" + attributeValue + '\"';
            }
            if (entity.DType == SXMLEntity::EType::CompleteElement)
                StringXML = StringXML + "/>";
            else 
                StringXML = StringXML + '>';
            OpenElements.push(entity.DNameData);
        }
        else if (entity.DType == SXMLEntity::EType::EndElement) {
            StringXML = "</" + StringXML + '>';
            if (!OpenElements.empty() && OpenElements.top() == entity.DNameData)
                OpenElements.pop();
        }
        // Write string to DataSink
        DDataSink->Write(StringToVectOfChar(StringXML));
        return true;
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