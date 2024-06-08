# Mini Operating System

This project is a simulation of an operating system (OS) environment implemented in C++. It aims to mimic the functionality of a basic OS, including process management, file operations, memory allocation, and user interaction.

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Dependencies](#dependencies)
4. [Installation](#installation)
6. [Contributing](#contributing)

## Introduction

This operating system simulation project is designed to provide a learning platform for understanding the basic concepts of operating systems. It includes various modules for task management, file operations, resource allocation, and user interaction. The codebase is written in a mix of C and C++ and utilizes different libraries for graphical user interface (GUI) development, threading, and file handling.

## Features

- **Task Management**: Allows users to manage tasks, view active processes, and terminate tasks if necessary.
- **File Operations**: Includes utilities for creating, editing, moving, and retrieving file information.
- **Resource Allocation**: Displays available system resources such as RAM and hard disk space.
- **Graphical User Interface**: Uses libraries like SFML and GTK for creating graphical interfaces for certain functionalities like file operations and games.

## Dependencies

- [SFML](https://www.sfml-dev.org/) - Simple and Fast Multimedia Library for GUI in C++.
- [GTK](https://www.gtk.org/) - Library for creating graphical user interfaces in C.
- Other standard C/C++ libraries for threading, file handling, and input-output operations.

## Installation

1. **Clone the repository**:

   ```bash
   git clone https://github.com/hasnaatmalik/MiniOperatingSystem-OS.git
Install dependencies as per your system requirements and specifications. Ensure SFML and GTK are properly configured.

## Contribution

Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

**Fork the repository.**
Create a new branch (git checkout -b feature/your_feature_name).
Make your changes.
Commit your changes (git commit -am 'Add new feature').
Push to the branch (git push origin feature/your_feature_name).
**Create a new Pull Request.**

## Run Script (run.sh)
The `run.sh` file contains all the compilation commands needed to compile the project. To run it, first ensure it has executable permissions:

**chmod +x run.sh**

Then, simply execute the script:

**./run.sh**

This will compile the project using the specified commands and generate the executable file.

Then execute:

**./main**

and it will start running the Operating System!

