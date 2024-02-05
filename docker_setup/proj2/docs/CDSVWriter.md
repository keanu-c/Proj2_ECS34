# CDSVWriter

## Description:
CDSVWriter is an abstract C++ class that generates DSV file strings using a character delimiter.

- Uses PIPML idiom (hides implementation details in the struct "SImplementation").
- Uses a output stream class "CDataSink" that abstracts data ouput from the "CDSVWriter" class.
- Creates pointer DImplementation of struct SImplementation in the class to abstract details.

## Properties

CDSVWriter class:

```cpp
class CDSVWriter{
    private:
        struct SImplementation; // hides implementation with this struct
        std::unique_ptr<SImplementation> DImplementation; // constructor of the class will create this pointer

    public:
        CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall = false); // Constructor
        ~CDSVWriter(); // Destructor

        bool WriteRow(const std::vector<std::string> &row); // Method
};
```

## Method
`bool WriteRow(const std::vector<std::string> &row)`: combines a vector of strings using a delimiter and then writes a std::vector<char> to CDataSink::Write() which turns it into a string, returns true if successful. 

### Parameters
`(const std::vector<std::string> &row)`: vector of strings to be combined into a string separated by a delimiter.

### Return value
`True` if row has been successfully written.
`False` otherwise.

## Example Usage

```cpp
// CDSVWriter.WriteRow()
#include "DSVWriter.h"
#include "StringDataSink.h"
#include <iostream>

int main ()
{
    auto Sink = std::make_shared<CStringDataSink>();
    CDSVWriter Writer(Sink, ',');
    std::vector<std::string> input = {"Apple", "of", "my", "Eye"};

    Writer.WriteRow(input);
    std::string Row = Sink->String(); // "Apple,of,my,Eye"
    std::cout << Row << std::endl; 
    // Prints out: Apple,of,my,Eye
    return 0;
}
```

