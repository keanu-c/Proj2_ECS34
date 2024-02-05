# CDSVReader

## Description:
CDSVReader is an abstract C++ class that reads DSV file strings and separates values based on the delimiter.

- Uses PIPML idiom (hides implementation details in the struct "SImplementation").
- Uses a input stream class "CDataSource" that abstracts data input for the "CDSVReader" class.
- Creates pointer DImplementation of struct SImplementation in the class to abstract details.

## Properties

CDSVReader class:

```cpp
class CDSVReader{
    private:
        struct SImplementation; // hides implementation with this struct
        std::unique_ptr<SImplementation> DImplementation; // constructor of the class will create this pointer

    public:
        CDSVReader(std::shared_ptr< CDataSource > src, char delimiter); // Constructor
        ~CDSVReader(); // Destructor

        bool End() const; // Method
        bool ReadRow(std::vector<std::string> &row); // Method
};
```

## Methods
`bool End() const`: Peeks into next character in DataSource to see if it's the end.

`bool ReadRow(std::vector<std::string> &row)`: Looks through the Datasource string to separate values by the delimiter and one string will be put in the row per column. 

### Parameters
`bool End() const`: None.
`bool ReadRow(std::vector<std::string> &row)`: vector of strings that you want to output.

### Return value
`bool End() const`:
`True` if there's no more characters to read.
`False` otherwise.

`bool ReadRow(std::vector<std::string> &row)`:
`True` if row is successfully read.
`False` otherwise.

## Example Usage

```cpp
// CDSVReader
#include "DSVReader.h"
#include "StringDataSource.h"
#include <iostream>

int main ()
{
    auto Source = std::make_shared<CStringDataSource>("Hello&World!");
    CDSVReader Reader(Source, '&'); // delimiter is '&'
    std::vector<std::string> output;

    Reader.ReadRow(output); // True
    if (Reader.End()) { // True
    std::cout << output.size() << std::endl; // 2
    std::cout << output[0] << std::endl; // "Hello"
    std::cout << output[1] << std::endl; // "World"
    }
}
```