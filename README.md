# Address Book Application in C

## Problem Statement
Managing contact information manually is inefficient and error-prone. This project implements a menu-driven Address Book application in C to store, search, update, and delete contact details efficiently.

## Objective
To design and develop a simple and reliable address book system using core C programming concepts such as structures, pointers, file handling, and modular programming.

## Features
- Add new contacts
- View all saved contacts
- Search contacts by name or phone number
- Edit existing contact details
- Delete contacts
- Persistent storage using files

## Implementation Details
- Used structures to store contact information
- Implemented file handling for data persistence
- Designed a menu-driven interface similar to embedded system dashboards
- Modularized code using header and source files

## Challenges Faced
Managing file updates during edit and delete operations was challenging. Proper pointer handling and structured file access were required to prevent data corruption.

## Key Learnings
- Practical understanding of structures and pointers
- Hands-on experience with file handling in C
- Improved debugging and problem-solving skills
- Experience in building real-world menu-driven applications

 ## How to Compile and Run
gcc src/*.c -o address_book
./address_book


## Future Enhancements
- Password-protected access
- Sorting contacts
- Porting the application to an embedded system using LCD and keypad
