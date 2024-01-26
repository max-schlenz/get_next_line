# Get Next Line Project

## Introduction
The Get Next Line project is a fundamental programming challenge focused on creating a function in C that reads a line from a file descriptor. This project is a part of the 42 curriculum, aimed at enhancing understanding of static variables, file descriptors, and dynamic memory allocation.

## Features
- **Line Reading**: Function to read and return one line at a time from a file descriptor.
- **Memory Management**: Efficient dynamic memory allocation and deallocation to handle variable line lengths.
- **Error Handling**: Robust error management for file reading operations.
- **Bonus Features**:
  - Handle multiple file descriptors simultaneously without losing the reading thread of each.
  - Only one static variable for the entire function.

## Installation and Usage
1. Clone the repository:
2. Compile the program: `gcc -Wall -Wextra -Werror -D BUFFER_SIZE=<buffer size> get_next_line.c get_next_line_utils.c`
3. Use the function in your program to read lines from file descriptors.

## Technologies Used
- C programming language
- Advanced memory and file descriptor management techniques
