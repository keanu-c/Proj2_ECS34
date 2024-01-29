Start<tag width ="34">Character data</tag>End
<tag/> Complete
- tag has an attribute of width with "34" as a value if empty, returns an empty string


- std::shared_ptr like a regular pointer except it does reference counting. It deletes when there are 0 pointers pointing at the object it’s pointing at. std::unique_ptr only one thing can point to it // GOOD FOR HIDING DETAILS
- Use CDataSource 
- Read row will fill up a vector full of strings and return true if its successfully able to parse the row
- writerow takes a vector of strings and will output the row separating it with the delimiter
- if the delimiter is in the value use double quotes to separate it, also use double quotes for a newline
- use expat library to do the parsing in XML
- cdata is the stuff in the middle (data) that arent the tags. skipcdata is skipping the stuff in the middle.

- get() to get the next character
- peek() to chepeek at the next character but not pull it // if there's a double quote after a double quote, then turn it into one literal double quote #WILL BE HELPFUL
- Read() will be helpful when doing XML reader and pass it down to expat library

- Prob start withe DSV writer #DON'T MODIFY THE HEADER FILES, 


