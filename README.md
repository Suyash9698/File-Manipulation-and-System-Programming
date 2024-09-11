# **Assignment 1**
---
## **Question 1**
### ***Overview***
- This code will reverse the input file content of input file.

- The output will be stored in a 1_input_filename.txt output file under directory called 'Assignment1_1'.

- On console, the writing progress percentage will also be there which state the ongoing writing progress to the output file.
### ***Execution***
- Open terminal or command line and pass input_filename as an arguent to the code

- The commands to run the code are (For MacOS users):-       
   ```
   $ clang++ Q1.cpp.

   $ ./a.out input_filename.txt 
   
   ```
### **Assumption**
- User provides the input in the form of inputFile.txt

- User don't press enter inside input text file as it would give the empty first line extra as first line of output.


---
## **Question 2**
### ***Overview***

- This code will reverse the input file content from index 0 to startIndex-1 and then printing same from startIndex to endIndex and again reversing the content from endIndex+1 to file_size.

- The output will be stored in a 2_input_filename.txt output file under directory called 'Assignment1_2'.

- On console, the writing progress percentage will also be there which state the ongoing writing progress to the output file.

### ***Execution***
- Open terminal or command line and pass input_filename, starting index ,and end index as an arguents to the code.

- The commands are (For MacOS users):-: 
```    
   $ clang++ Q2.cpp.

   $ ./a.out input_filename.txt startIndex endIndex
```

### ***Assumption***
- User provides the input in the form of inputFile.txt start end. Otherwise it will give error as "Insufficient number of arguments" in case of less number of arguments.

- The starting index and ending index are in the range of [0, input_file_size-1]. Otherwise it will display the error as "Invalid indexing provided".

---
## **Question 3**
### ***Overview***
-  This code will check :
   > Whether the directory names as argument[3] is present or not.

   > Whether the newfile which passed as an argument is reversed of oldfile or not.

   > The permissions of user, group and others to read, write ,and execute the newFile, oldFile and directory
### ***Execution*** 
- Open terminal or command line and pass 3 arguments ie. new_filename, old_filename and directory name to the code.

- The commands to be executed are (For MacOS users):-:  
```     
   $ clang++ Q2.cpp.

   $ ./a.out new_filename.txt old_filename
     directoryName

```
### ***Assumption*** 
- User provides the input in the form of newFile.txt 
  oldFile.txt directory_name. Otherwise it will give error as "Insufficient number of arguments" in case of less number of arguments.