# Simple_PL1-Scanner
A hand-written lexical analyzer for the Simple_PL1 language built in C. The program reads a source file and outputs the sequence of tokens recognized by the scanner.

# About the Project

This project implements the first phase of a compiler — lexical analysis.
The scanner reads a Simple_PL1 program character by character and identifies tokens such as identifiers, numbers, reserved words, operators, and delimiters.

For identifiers and numeric values, the corresponding lexeme is also displayed.

# Features

- Recognizes:
  - Identifiers (ID)
  - Numbers (NUMBER)
  - Reserved words: read, write
  - Operators: +, -, *, /, :=
  - Delimiters: ( ) , ;

- Outputs each token on a separate line

- Displays lexemes for identifiers and numbers

- Command-line file input

- End-of-file detection (SCAN_EOF)

# Tech Stack

- C

- Visual Studio 2022

- Standard C libraries (stdio.h, ctype.h, stdlib.h)

# How to Run

1. Compile the project in Visual Studio or using a C compiler.

2. Run from the command line:

3. CS435P01YourLastName.exe source.txt

# Example

Input
```
x := 3;
read(x);
```

Output
```
ID, x
ASSIGN
NUMBER, 3
SEMICOLON
READ
LPAREN
ID, x
RPAREN
SEMICOLON
```
# What I Learned

- Built a lexical scanner from scratch

- Implemented token recognition using character classification

- Worked with file I/O and command-line arguments

- Gained hands-on experience with compiler front-end concepts

# Author

Samantha Roldan
Computer Science Graduate | Front-End & Full-Stack Developer |
LinkedIn: https://linkedin.com/in/your-link
