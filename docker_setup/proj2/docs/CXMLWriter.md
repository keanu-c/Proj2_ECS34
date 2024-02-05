# CXMLWriter

## Description:
CXMLWriter is an abstract C++ class that generates XML file strings using an XMLEntity class.

- Uses PIPML idiom (hides implementation details in the struct "SImplementation").
- Uses a output stream class "CDataSink" that abstracts data ouput from the "CXMLWriter" class.
- Creates pointer DImplementation of struct SImplementation in the class to abstract details.

## Properties

CXMLWriter class:

```cpp
class CXMLWriter{
    private:
        struct SImplementation; // hides implementation with this struct
        std::unique_ptr<SImplementation> DImplementation; // constructor of the class will create this pointer
        
    public:
        CXMLWriter(std::shared_ptr< CDataSink > sink); // Constructor
        ~CXMLWriter(); // Destructor
        
        bool Flush(); // Method
        bool WriteEntity(const SXMLEntity &entity); // Method
};
```

## Method
`bool Flush()`: matches an EndElement to all StartElements that havent been "ended". 

`bool WriteEntity(const SXMLEntity &entity)`: turns an XMLEntity into a string equivalent. 

### Parameters
`bool Flush()`: None.

`bool WriteEntity(const SXMLEntity &entity)`: an XMLEntity.

### Return value
`bool Flush()`:
`True` if all StartElements are successfully matched with their EndElements.
`False` otherwise.

`bool WriteEntity(const SXMLEntity &entity)`: 
`True` if successfully able to write out XMLEntity to output stream.
`False` otherwise.

## Example Usage

```cpp
// CXMLWriter Flush()
#include "XMLWriter.h"
#include "StringDataSink.h"
#include <iostream>

int main ()
{
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {}});
    Writer.WriteEntity({SXMLEntity::EType::CharData, "world", {}});
    Writer.WriteEntity({SXMLEntity::EType::StartElement, "bye", {}});
    Writer.WriteEntity({SXMLEntity::EType::StartElement, "yes", {}});
    Writer.WriteEntity({SXMLEntity::EType::CharData, "no", {}});
    Writer.Flush();

    std::cout << OutputStream->String() << std::endl; // "<hello>world<bye><yes>no</yes></bye></hello>"
}


// CXMLWriter WriteEntity(const SXMLEntity &entity)
#include "XMLWriter.h"
#include "StringDataSink.h"
#include <iostream>

int main ()
{
    auto OutputStream = std::make_shared<CStringDataSink>();
    CXMLWriter Writer(OutputStream);

    Writer.WriteEntity({SXMLEntity::EType::StartElement, "hello", {}});
    Writer.WriteEntity({SXMLEntity::EType::EndElement, "hello", {}});

    std::cout << OutputStream->String() << std::endl; // "<hello></hello>"
}
```