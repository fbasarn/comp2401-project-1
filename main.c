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
int indexExist(const SubsystemCollection *collection, const char *name, int *index);

int main() {
    int choice = -1;

    // Store a subsystem collection
    SubsystemCollection subsys_collection;
    SubsystemCollection filterCollection;

    // reserve data to store necessary variables
    char name[MAX_STR];
    unsigned char status;
    unsigned int data;
    Subsystem subsystem;
    char value;
    char filter[9];

    // store the index of the given subsystem
    int index;

    subsys_collection_init(&subsys_collection);
    // Use a while loop to print the menu for the user and call the appropriate functions.
    // The definitions above are provided to assist with this.
    do {
        print_menu(&choice);

        switch (choice)
            {
            case MENU_ADD:                
                
                printf("Enter subsystem name to add: "); // get user value
                scanf("%31s", name);
                while (getchar() != '\n');
                
                subsys_init(&subsystem, name, 0); // Initialize the subsystem with the values provided
                subsys_append(&subsys_collection, &subsystem); // Add initialized subsystem to the collection
                printf("Subsystem '%s' added successfully.\n", name); // success message
                break;
            
            case MENU_PRINT:
                printf("Enter subsystem name to print: ");
                scanf("%31s", name); 
                while (getchar() != '\n');
        
                //print the subsystem if it's found, error message if not
                if(indexExist(&subsys_collection, name, &index)) {
                    subsys_print(&subsys_collection.subsystems[index]);
                }
                break;
            
            case MENU_PRINTALL:
                if(subsys_collection.size != 0){
                    subsys_collection_print(&subsys_collection);
                }else{
                    printf("Currently there are no subsystems in the collection. Try again after adding some.\n");
                }
                break;
            
            case MENU_STATUS:
                printf("Enter: <Subsystem Name> <Status ID, 7,6,5,4,2, or 0> <New Value (0,3)>: ");
                scanf("%32s %hhd %hhd", name, &status, &value);
                while (getchar() != '\n');

                if(indexExist(&subsys_collection, name, &index)) {
                    subsys_status_set(&subsys_collection.subsystems[index], status, value);
                    printf("Status set successfully.\n");
                }
                break;
            
            case MENU_REMOVE:

                printf("Enter subsystem name to remove from collection: ");
                scanf("%31s", name);
                while (getchar() != '\n');

                if(indexExist(&subsys_collection, name, &index)) {
                    subsys_remove(&subsys_collection, index);
                    printf("Subsystem '%s' removed successfully.\n", name);
                }
                break;
            
            case MENU_FILTER:
                printf("Enter filtering string (8 characters of 1, 0, *): ");
                scanf("%8s", filter);
                while (getchar() != '\n');
                
                subsys_collection_init(&filterCollection); //initialize the filter collection
                subsys_filter(&subsys_collection, &filterCollection, filter); 
                break;
            
            case MENU_DATA:
                printf("Enter: <Subsystem Name> <Data, uppercase hex without 0x>: ");
                scanf("%32s %x", name, &data);
                while (getchar() != '\n');

                if(indexExist(&subsys_collection, name, &index)) {
                    subsys_data_set(&subsys_collection.subsystems[index], data, &subsys_collection.subsystems[index].data);
                    printf("Data updated successfully.\n");
                }
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

// If the provided index exists in the subsystem returns 1,
// otherwise returns 0 with an error message
int indexExist(const SubsystemCollection *collection, const char *name, int *index){
    *(index) = subsys_find(collection, name);
    if(*(index) != ERR_SYS_NOT_FOUND && *(index) != ERR_NULL_POINTER) {
        return 1;
    }
    printf("Subsystem was not found, try again with a different name.\n");
    return 0;
}