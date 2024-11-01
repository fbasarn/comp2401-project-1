# COMP2401 PROJECT1
## Feyza Basaran
## 101246386

## Project 1, Data Entry
This program is implemented for users to manually input information about subsystems 
of a skyrocket. Each subsystems stores a status character where each bit in positions (7, 6, 5, 4, 2 or 0)shows the following status codes:

7: (power) 0: Off, 1: On
6: (data) 0: No Data, 1: Data Queued
5: (activity) 0: Off, 1: On
4: (error) 0: No Error, 1: Error
3, 2: (performance) 00: None, 01: Low, 10: Optimal, 11: High
1, 0: (resource) 00: None, 01: Low, 10: Sufficient, 11: High

The user can perform the following operations using the corresponding menu options:
- Add a Subsystem to the collection
- Remove a Subsystem from the collection
- print all the subsystems in the collection
- set the data to a specific status area
- print an individual subsystem
- filter the subsystems based on status criteria

## Building and Running
1. Open a terminal and navigate to the folder containing the program files.
2. Type command 'gcc -o _yourfilename_ main.c subsys_collection.c subsys.c'
3. You should see the executable file named _yourfilename_.
4. From that directory, you can run './yourfilename' to execute the project
5. Once you run the program, a menu and options will be presented in the terminal. 
6. Follow the instructions, and/or helpful error messages.

## Credits
- function declarations in subsystem.h header file and print_menu(int *choice) function was provided by Prof. Connor Hillen
- All other function implementations developed individually by Me (101246386)