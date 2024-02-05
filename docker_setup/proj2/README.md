# Proj2_ECS34
Student 1: Keanu Chau (920727641)

Student 2: Christopher Lee (920724149)

## Project Status
* Add StringUtils files from previous work
* Add /teststrdatasource and /teststrdatasink to my makefile
* Create XML files, DSV files, and docs directory with documentation files
* Create skeleton functions for XML and DSV files
* Fix EditDistance() in StringUtils.cpp
* Write tests for DSV and XML classes
* Edit makefile to include /testdsv and /testxml processes
* Fix makefile to include StringDataSource.o and StringDataSink.o to link with the /testxml and /testdsv
* Fix XML test by deleting whitespace in test names
* Implement CDSVWriter class, Used Christopher Lee's StringUtils::Replace()
* Implement CDSVReader class
* Implement CXMLWriter class
* Implement CXMLReader class
* Write documentation for all classes

## Known Issues
1. Makefile issue
Multiple undefined references when trying to run "make" in the terminal. Probably an issue with not linking the files or libraries correctly so that the test cpp files know where some classes are. 
- Fixed : I included StringDataSource and StringDataSink .o directories into the tests.

2. CDSVWriter class: prepending newline if there's a row
I don't know how to tell if DataSink already has a row/string so that I can prepend a newline when I add the next string/row.
- Fixed: added a bool ContainsRow to struct SImplementation that returns true if a row has been written.

3. CXMLWriter class: Flush() implementation
Couldn't figure out a way to store when a StartElement had it's amtching EndElement or not.
- Fixed: Used ChatGPT

## Code References
* [What characters do I need to escape in XML documents?](https://stackoverflow.com/questions/1091945/what-characters-do-i-need-to-escape-in-xml-documents#:~:text=XML%20escape%20characters,the%20special%20character%20is%20used.)

## Generative AI Use
I used ChatGPT for all my prompts.

### Prompt 1 --------------------------------------------------------------------------------------------------------------------
how would i turn a std::string to a std::vector<char>?
### Response 1

To convert a std::string to a std::vector<char>, you can use the constructor of the std::vector class that takes two iterators: the beginning and the end of the range to be copied. Here's an example:

```cpp
#include <iostream>
#include <vector>
#include <string>

int main() {
    // Your std::string
    std::string myString = "Hello";

    // Convert std::string to std::vector<char>
    std::vector<char> charVector(myString.begin(), myString.end());

    // Print the elements in the vector
    for (char c : charVector) {
        std::cout << c << " ";
    }

    return 0;
}
```
In this example, myString.begin() returns an iterator pointing to the beginning of the string, and myString.end() returns an iterator pointing just past the end of the string. The std::vector<char> constructor then copies the elements in the specified range into the vector.

After this conversion, you have a std::vector<char> containing the characters from the original std::string.

### Changes 1
I addded a function to the struct SImplementations of CDSVWriter and CXMLWriter class: 
```cpp
std::vector<char> StringToVectOfChar (const std::string &string) {
    return std::vector<char>(string.begin(), string.end());
}
```
I needed this since Write() takes in a std::vector<char> as a parameter and not std::string.

### Prompt 2 --------------------------------------------------------------------------------------------------------------------
how would i turn a char into a std::string
### Response 2

To convert a single character (char) into a std::string in C++, you can use the constructor of the std::string class that takes a pointer to a null-terminated character array as an argument. Since a char is essentially a character, you can create a string with just that character.

Here's an example:

```cpp
#include <iostream>
#include <string>

int main() {
    char myChar = 'A'; // Replace 'A' with your character

    // Convert char to std::string
    std::string myString(1, myChar);

    // Output the result
    std::cout << "Character: " << myChar << std::endl;
    std::cout << "String: " << myString << std::endl;

    return 0;
}
```
In this example, std::string(1, myChar) creates a string with the character myChar. The first argument (1) specifies the length of the string, and the second argument (myChar) is the character to be repeated.

This will output:

```makefile
Character: A
String: A
```
Replace 'A' with your desired character, and the code will work for any char value.
### Changes 2
In the CDSVWriter class I needed to convert "char Delimiter" into a std::string for the Replace function. So I did: `std::string(1,Delimiter)`.

### Prompt 3 --------------------------------------------------------------------------------------------------------------------
What does peek do in this class?: (included contents of [StringDataSource.h] and [StringDataSource.cpp])
### Response 3
The Peek() function in the context of input streams, such as CDataSource, allows you to look at the next character in the stream without actually consuming it. It's like taking a sneak peek at the next character without advancing the position in the stream.

Here's how Peek() typically works:

It examines the next character in the stream.
It returns true if there is a character available to read and stores that character in the variable passed as an argument.
If there are no characters available (for example, if the end of the stream has been reached), it returns false without modifying the argument.
Peek() can be used to check if the data source has reached its end by attempting to peek the next character. If Peek() returns false, it indicates that there are no more characters left to read from the data source, implying that the end of the data source has been reached.

### Changes 3
Implemented peek() into the CDSVReader End() function:
```cpp
bool End() const {
    char info;
    if (!DDatasource->Peek(info)) {
    return true;
    }  else {
    return false;
    }   
}
```

### Prompt 4 --------------------------------------------------------------------------------------------------------------------
How would you iterate over DAttributes?:
(include contents of [XMLEntity.h])
### Response 4

In C++, you can use a range-based for loop to iterate over the elements of a std::vector. Here's how you can iterate over DAttributes in your SXMLEntity struct:

```cpp
for (const auto &attribute : DAttributes) {
    // 'attribute' is a reference to each element (TAttribute) in DAttributes
    // You can access the elements using attribute.first and attribute.second
    std::string attributeName = attribute.first;
    std::string attributeValue = attribute.second;

    // Your code here to process the attribute
    // ...
}
```
This loop iterates over each element in the DAttributes vector, and attribute is a reference to the current element (which is a std::pair<std::string, std::string>). You can access the first and second components of the pair using attribute.first and attribute.second, respectively.

For example, if DAttributes contains attribute pairs like {"attr1", "value1"} and {"attr2", "value2"}, the loop would iterate twice, and in each iteration, attribute.first would be the attribute name, and attribute.second would be the attribute value.

You can use this loop in your methods like AttributeExists, AttributeValue, and SetAttribute to traverse through the attributes and perform the necessary operations.

### Changes 4

I needed to use it for any StartElement or CompleteElement types in my XMLWriter.cpp to check for attributes:
```cpp
// CHATGPT: How would you iterate over DAttributes?
// Adds attributes to string
for (const auto &attribute : entity.DAttributes) {
    std::string attributeName = attribute.first;
    std::string attributeValue = attribute.second;
    ...
}
```
### Prompt 5 -------------------------------------------------------------------------------------------------------------------------------
how would you keep track of whether or not StartElements have been ended or not?
(include contents of [XMLWriter] at that time)

```cpp
#include "XMLWriter.h"
#include <expat.h>

struct CXMLWriter::SImplementation {
    std::shared_ptr< CDataSink > DDataSink;
    std::string StringXML;

    SImplementation(std::shared_ptr< CDataSink > sink) {
        DDataSink = sink;
    }
    // Used AI
    // Turns string into vector of characters
    std::vector<char> StringToVectOfChar (const std::string &string) {
        return std::vector<char>(string.begin(), string.end());
    }

    bool Flush(){
        // add EndElement to all StartElements that havent been "ended"
        
    }
    bool WriteEntity(const SXMLEntity &entity) {
        if (!DDataSink) return false;
        /*
        if (!entity.DNameData || !entity.DType) {
            return false;
        }
        */

        // Initialize string with NameData of XMLEntity
        StringXML = entity.DNameData;
        if (entity.DType == SXMLEntity::EType::StartElement || entity.DType == SXMLEntity::EType::CompleteElement) {
            // Add opening tag
            StringXML = '<' + StringXML;
            // CHATGPT: How would you iterate over DAttributes?
            // Adds attributes to string
            for (const auto &attribute : entity.DAttributes) {
                std::string attributeName = attribute.first;
                std::string attributeValue = attribute.second;
                StringXML = StringXML + ' ' + attributeName + ""=\"" + attributeValue + '\"';
            }
            if (entity.DType == SXMLEntity::EType::CompleteElement)
                StringXML = StringXML + "/>";
            else 
                StringXML = StringXML + '>';
        }
        else if (entity.DType == SXMLEntity::EType::EndElement) {
            StringXML = "</" + StringXML + '>';
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
```
### Response 5

To keep track of whether or not StartElement entities have been ended or not, you can maintain a stack that keeps track of the open elements. When you encounter a StartElement, push it onto the stack. When you encounter an EndElement, pop the top element from the stack and check if it matches the current EndElement. If it does, then the element has been properly closed; otherwise, it indicates an error.

Here's a modified version of your code to include a stack for tracking open elements:

```cpp
#include <stack>

// ... (other includes and declarations)

struct CXMLWriter::SImplementation {
    // ... (existing members)

    std::stack<std::string> DOpenElements;

    // ... (existing methods)

    bool Flush() {
        // Close any open elements in the stack
        while (!DOpenElements.empty()) {
            StringXML = "</" + DOpenElements.top() + '>';
            DOpenElements.pop();
            DDataSink->Write(StringToVectOfChar(StringXML));
        }
        return true;
    }

    bool WriteEntity(const SXMLEntity &entity) {
        // ... (existing code)

        if (entity.DType == SXMLEntity::EType::StartElement || entity.DType == SXMLEntity::EType::CompleteElement) {
            // Add opening tag
            StringXML = '<' + StringXML;
            // CHATGPT: How would you iterate over DAttributes?
            // Adds attributes to string
            for (const auto &attribute : entity.DAttributes) {
                std::string attributeName = attribute.first;
                std::string attributeValue = attribute.second;
                StringXML = StringXML + ' ' + attributeName + "=\"" + attributeValue + '\"';
            }
            if (entity.DType == SXMLEntity::EType::CompleteElement)
                StringXML = StringXML + "/>";
            else {
                StringXML = StringXML + '>';
                // Push the element onto the stack
                DOpenElements.push(entity.DNameData);
            }
        }
        else if (entity.DType == SXMLEntity::EType::EndElement) {
            // Pop the top element from the stack and check if it matches the current EndElement
            if (!DOpenElements.empty() && DOpenElements.top() == entity.DNameData) {
                StringXML = "</" + StringXML + '>';
                DOpenElements.pop();  // Element properly closed, remove from stack
            }
            else {
                // Handle error: mismatched EndElement
                // You may choose to log an error or take appropriate action
                // For simplicity, just close the current element without validation
                StringXML = "</" + StringXML + '>';
            }
        }

        // ... (existing code)
    }
};
```
This modification uses a stack (DOpenElements) to keep track of open elements. The Flush function is updated to close any remaining open elements in the stack. The WriteEntity function is modified to push StartElement onto the stack and pop elements from the stack when encountering EndElement. It also checks for mismatched EndElement and takes appropriate action.

### Changes 5

- I copied it's implementation of a stack in my code so that it pushes a StartElement and pops it if a matching EndElement is written.
- I copied it's Flush implementation (I couldn't find a better way to implement it) which pop's off the StartElement that hasn't been matched and writes a matching EndElement.
- Used a stack to check whether or not a StartElement has been ended (relevant parts of code):
```cpp

#include <stack>
...
std::stack <std::string> OpenElements;
...
bool Flush(){
    while(!OpenElements.empty()) {
        StringXML = "</" + OpenElements.top() + '>';
        OpenElements.pop();
        DDataSink->Write(StringToVectOfChar(StringXML));
    }
    return true;
}
... 
    if (entity.DType == SXMLEntity::EType::StartElement || entity.DType == SXMLEntity::EType::CompleteElement) {
        ...
        ...
        OpenElements.push(entity.DNameData);
    }
...
    else if (entity.DType == SXMLEntity::EType::EndElement) {
        ...
        if (!OpenElements.empty() && OpenElements.top() == entity.DNameData)
            OpenElements.pop();
    }

```
### Prompt 6
### Response 6
### Changes 6