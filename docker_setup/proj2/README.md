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


## Known Issues
1. Makefile issue
Multiple undefined references when trying to run "make" in the terminal. Probably an issue with not linking the files or libraries correctly so that the test cpp files know where some classes are. 
- Fixed : I included StringDataSource and StringDataSink .o directories into the tests.

2. CDSVWriter class: prepending newline if there's a row
I don't know how to tell if DataSink already has a row/string so that I can prepend a newline when I add the next string/row.
- Fixed: added a bool ContainsRow to struct SImplementation that returns true if a row has been written.

## Code References
* 

## Generative AI Use
I used ChatGPT for all my prompts.

### Prompt 1
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
I addded a function to the CDSVWriter class: 
```
std::vector<char> StringToVectOfChar (const std::string &string) {
    return std::vector<char>(string.begin(), string.end());
}
```
I needed this since Write() takes in a std::vector<char> as a parameter and not std::string.

### Prompt 2
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

### Prompt 3
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

### Prompt 4

### Response 4

### Changes 4