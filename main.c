#include <stdio.h>
#include <stdlib.h>
#include "subsystem.h"

#define MENU_ADD 1
#define MENU_PRINT 2
#define MENU_PRINTALL 3
#define MENU_STATUS 4
#define MENU_REMOVE 5
#define MENU_FILTER 6
#define MENU_DATA 7
#define MENU_EXIT 0
#define MENU_MIN 0
#define MENU_MAX 7

int print_menu(int *choice);
int indexExist(int i);

int main() {
    int choice = -1;

    // Store a subsystem collection
    SubsystemCollection subsys_collection;
    unsigned int collection_size;

    // reserve data to store necessary variables
    char name[MAX_STR];
    unsigned char status;
    unsigned int data;
    Subsystem subsystem;
    char value;

    // store the index of the given subsystem
    int index;

    // Use a while loop to print the menu for the user and call the appropriate functions.
    // The definitions above are provided to assist with this.
    do {
        print_menu(&choice);

        switch (choice)
            {
            case MENU_ADD:
                // Get the user's input and store the results in stack variables above
                printf("Enter subsystem name: ");
                scanf("%31s", name);
                while (getchar() != '\n');
                // Initialize the subsystem with the values provided
                subsys_init(&subsystem, name, 0);
                
                // Add the subsystem to the collection
                subsys_append(&subsys_collection, &subsystem);
                break;
            case MENU_PRINT:
                // Get the user's input and store
                printf("Enter subsystem name to print: ");
                scanf("%31s", name); 
                while (getchar() != '\n');
                // Find the index of the subsystem and print
                index = subsys_find(&subsys_collection, name);

                //print the subsystem if found, error message if not
                if(indexExist(index)){
                    printf("This is the status found: %d\n", subsys_collection.subsystems[index].status);
                    subsys_print(&subsys_collection.subsystems[index]);
                }
                else{
                    printf("Subsystem was not found, try again with a different name.\n");
                }
                break;
            case MENU_PRINTALL:
                subsys_collection_print(&subsys_collection);
                break;
            case MENU_STATUS:
                printf("Enter: <Subsystem Name> <Status ID, 7,6,5,4,2, or 0> <New Value (0,3)>: ");
                scanf("%32s %hhd %hhd", name, &status, &value);
                while (getchar() != '\n');
                
                index = subsys_find(&subsys_collection, name);
                
                if(indexExist(index)){
                    subsys_status_set(&subsys_collection.subsystems[index], status, value);
                }
                else{
                    printf("Subsystem was not found, try again with a different name.\n");
                }
                break;
            case MENU_REMOVE:
                /* code */
                break;
            case MENU_FILTER:
                /* code */
                break;
            case MENU_DATA:
                /* code */
                break;
            case MENU_EXIT:
                printf("Exiting...\n");
                break;
            }
    } while (choice != MENU_EXIT);
    return 0;
}

/* 
    Prints a menu to the user and prompts them until they enter a valid menu option.

    out: *choice, an integer corresponding to a MENU_ definition defining the choice made by the user.

    Returns: 
        - ERR_SUCCESS if there is no error
        - ERR_NULL_POINTER if `choice` is NULL

*/
int print_menu(int *choice) {
    if (choice == NULL) {
        return ERR_NULL_POINTER;
    }

    *choice = 0;

    do {
        printf("\n--- Subsystem Management Menu ---\n");
        printf("%d. Add Subsystem\n", MENU_ADD);
        printf("%d. Print Subsystem\n", MENU_PRINT);
        printf("%d. Print All Subsystems\n", MENU_PRINTALL);
        printf("%d. Set Subsystem Status\n", MENU_STATUS);
        printf("%d. Remove Subsystem\n", MENU_REMOVE);
        printf("%d. Filter Subsystems\n", MENU_FILTER);
        printf("%d. Set Subsystem Data\n", MENU_DATA);
        printf("%d. Exit\n", MENU_EXIT);
        printf("Select an option: ");
        scanf("%d", choice);
        while (getchar() != '\n');

        if (*choice < MENU_MIN || *choice > MENU_MAX) {
            printf("Error: Invalid choice. Please try again.\n");
        }
    } while (*choice < MENU_MIN || *choice > MENU_MAX);

    return ERR_SUCCESS;
}

int indexExist(int i){
    if(i != ERR_SYS_NOT_FOUND && i != ERR_NULL_POINTER){
        return 1;
    }
    else{
        return 0;
    }
}