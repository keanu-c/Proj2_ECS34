# CDSVWriter

## Description:
CDSVWriter is an abstract C++ class that generates DSV file strings using a character delimiter.

- Uses PIPML idiom (hides implementation details in the struct "SImplementation").
- Uses a output stream class "CDataSink" that abstracts data ouput from the "CDSVWriter" class.
- Creates pointer DImplementation of struct SImplementation in the class to abstract details.

### Properties

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

In struct Simplementation:

```cpp
struct CDSVWriter::SImplementation {
    std::shared_ptr< CDataSink > DDataSink; // stores sink to abstract output
    char Delimiter; // stores delimiter
    bool Quoteall; // stores true or false
    bool ContainsRow; // false if row has not been written to sink, true if it has been written to sink
    
    SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
        DDataSink = sink;
        if (delimiter == '"')
            Delimiter = ',';
        else
            Delimiter = delimiter;
        Quoteall = quoteall;
        ContainsRow = false; // initialize to false when constructing class
    }

    // Used AI
    // Turns string into vector of characters
    std::vector<char> StringToVectOfChar (const std::string &string) {
        return std::vector<char>(string.begin(), string.end());
    }

    bool WriteRow(const std::vector<std::string> &row) {
        // CDataSink object not created
        if (!DDataSink) return false;
        // Prepend newline if there's already a string
        if (ContainsRow) {
            DDataSink->Put('\n');
        }
        // Input row is empty
        if (row.empty()) {
            std::vector<char> EmptyString;
            DDataSink->Write(EmptyString);
        }
        // Iterate through vector of strings
        for (size_t i = 0; i < row.size(); i++) {
            // Append delimiter if it's not the first string and the last string
            if ((i != 0) && (i != row.size())) {
                DDataSink->Put(Delimiter);
            }
            // Create new string to edit
            std::string currentString = row[i];
            // Find every double quote, newline, or delimiter in string and quote it with double quotes
            currentString = StringUtils::Replace(currentString, "\"", "\"\"");
            currentString = StringUtils::Replace(currentString, "\n", "\"\n\"");
            currentString = StringUtils::Replace(currentString, std::string(1,Delimiter), '\"' + std::string(1, Delimiter) + '\"');
            
            // Quote all strings and then write to DataSink
            if (Quoteall) {
                std::vector<char> String = StringToVectOfChar(currentString);
                String.insert(String.begin(), '\"'); // prepend double quote
                String.push_back('\"'); // append a double quote
                DDataSink->Write(String);
            }
            // Write string to DataSink if it doesn't need to be quoted
            else {
                DDataSink->Write(StringToVectOfChar(currentString));
            }
            ContainsRow = true; // DataSink now contains a row
        }
        return true;
    }
};

// Constructor
CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) { 
    DImplementation = std::make_unique<SImplementation>(sink,delimiter,quoteall);
}
// Destructor
CDSVWriter::~CDSVWriter() {
}
// Method
bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
    return DImplementation->WriteRow(row);
}
```
### Methods
`bool CDSVWriter::WriteRow(const std::vector<std::string> &row)`: combines a vector of strings using a delimiter and then writes a std::vector<char> to CDataSink::Write() which turns it into a string, returns true if successful.

## Example Usage

