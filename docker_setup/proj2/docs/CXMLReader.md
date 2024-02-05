# CXMLReader

## Description:
CXMLReader is an abstract C++ class that reads XML file strings and separates data by XMLEntities (StartElement, EndElement, CharData).

- Uses PIPML idiom (hides implementation details in the struct "SImplementation").
- Uses a output stream class "CDataSource" that abstracts data ouput from the "CXMLReader" class.
- Creates pointer DImplementation of struct SImplementation in the class to abstract details.
- Uses Expat library to parse XML

## Properties

CXMLReader class:

```cpp
class CXMLReader{
    private:
        struct SImplementation; // hides implementation with this struct
        std::unique_ptr<SImplementation> DImplementation; // constructor of the class will create this pointer
        
    public:
        CXMLReader(std::shared_ptr< CDataSource > src); // Constructor
        ~CXMLReader(); // Destructor
        
        bool End() const; // Method
        bool ReadEntity(SXMLEntity &entity, bool skipcdata = false); // Method
};
```

## Method
`bool End() const`: checks if XML file string has all been read and is empty.

`bool ReadEntity(SXMLEntity &entity, bool skipcdata = false)`: reads from a source, parses XML, and separates it into XMLEntities. If skipcdata is false, chracter data in an XML is ignored.

### Parameters
`bool End() const`: None.

`bool ReadEntity(SXMLEntity &entity, bool skipcdata = false)`: an XMLEntity that stores each type of element and it's data and the boolean skipcdata.

### Return value
`bool End() const`:
`True` if XML file string has been fully read.
`False` otherwise.

`bool ReadEntity(SXMLEntity &entity, bool skipcdata = false)`: 
`True` if successfully able to read XML file string.
`False` otherwise.

## Example Usage

```cpp
// CXMLReader
#include "XMLReader.h"
#include "StringDataSource.h"
#include <iostream>

int main ()
{
    auto Source = std::make_shared<CStringDataSource>("<heading>Reminder</heading>");
    CXMLReader Reader(Source);
    SXMLEntity Entity;
    Reader.ReadEntity(Entity);
    std::cout << Entity.DNameData << std::endl; // "heading"
    auto XMLEntityType1 = Entity.DType; // SXMLEntity::EType::StartElement

    Reader.ReadEntity(Entity);
    std::cout << Entity.DNameData << std::endl; // "Reminder"
    auto XMLEntityType2 = Entity.DType; // SXMLEntity::EType::CharData

    Reader.ReadEntity(Entity);
    std::cout << Entity.DNameData << std::endl; // "heading"
    auto XMLEntityType3 = Entity.DType; // SXMLEntity::EType::EndElement
    
    if (Reader.End()) { // True
        std::cout << "No more to read" << std::endl;
    } 
}
```