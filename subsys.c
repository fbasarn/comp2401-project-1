#include "subsystem.h"
#include <string.h>

/*
    This file should contain the implementations for Subsystem specific functionality.
    Initialization, printing, setting and getting data and statuses.
*/


/* 
    Initialization of the memory pointed by the subsystem,
    initializes the name and status with provided values and 
    sets the data to 0.

    Returns:
    - ERR_NULL_POINTER If the pointer parameter(s) is/are null
    - ERR_SUCCESS if there is no error
*/
int subsys_init(Subsystem *subsystem, const char *name, char status){
    if (subsystem == NULL || name == NULL){
        return ERR_NULL_POINTER;
    }

    strncpy(subsystem->name, name, MAX_STR-1);
    subsystem->name[MAX_STR-1] = '\0';
    subsystem->status = status;
    subsystem->data = 0;

    return ERR_SUCCESS;
}

/* 
    Prints the name, status and the data of the subsystem provided,
    calls subsys_status_print() function to print the status

    Returns:
    - ERR_NULL_POINTER If the pointer parameter(s) is/are null
    - ERR_SUCCESS if there is no error
*/
int subsys_print(Subsystem *subsystem){
    if(subsystem == NULL){
        return ERR_NULL_POINTER;
    }

    printf("Name: %16s,", subsystem->name);
    subsys_status_print(subsystem);
    return ERR_SUCCESS;
}

/* 
    Sets any of the 5 status of the subsystem to the provided value. 
    Takes a status code that must be one of the defined codes in subsystem.h,
    and a char value that must be between 0 - 3.
    
    Returns:
    - ERR_INVALID_STATUS If the status doesn't match in any defined status codes
    in subsystem.h or the value provided is out of range for that status
    - ERR_SUCCESS if there is no error
*/
int subsys_status_set(Subsystem *subsystem, unsigned char status, unsigned char value){

    if(status == STATUS_PERFORMANCE || status == STATUS_RESOURCE){
        
        if(value < 0 || value > 3) return ERR_INVALID_STATUS;
        subsystem->status = subsystem->status & ~(3 << status);  //clear the bits
        if(value != 0) subsystem->status = subsystem->status | (value << status); //set the bits other than 0

    }
    if(status == STATUS_DATA || status == STATUS_POWER || status == STATUS_ERROR || status == STATUS_ACTIVITY){
        
        if(value < 0 || value > 1) return ERR_INVALID_STATUS;
        subsystem->status = subsystem->status & ~(1 << status); // clear the bits
        if(value == 1) subsystem->status = subsystem->status | (1 << status); //set the bits other than 0
    }
    else return ERR_INVALID_STATUS;  // status code doesn't exist

    return ERR_SUCCESS;
}

/* 
    Prints all 5 status fields of the subsystem individually. Takes a subsystem as a parameter,
    loops over the individual bits in the status field, and prints them to the terminal.
    
    Returns:
    - ERR_NULL_POINTER If the pointer parameter(s) is/are null
    - ERR_SUCCESS if there is no error

*/
int subsys_status_print(const Subsystem *subsystem) {
    if (subsystem == NULL) {
        return ERR_NULL_POINTER;
    }

    char stat[6][6] = {"PWR", "|DATA", "|ACT", "|ERR", "|PERF", "|RES"};
    printf(" Status: (");
    int x = 0;
    
    for (int i = 7; i >= 4; i--) {
        int bit_value = (subsystem->status & (1 << i)) >> i;
        printf("%s: %d ", stat[x], bit_value);
        x++;
    }
    for(int i = 2; i >= 0; i-=2){
        int bit_value = (subsystem->status & (3 << i)) >> i;
        printf("%s: %d ", stat[x], bit_value);
        x++;
    }
    
    printf(")");
    
    int data;
    if(subsys_data_get(subsystem, &data) != ERR_NO_DATA){
        printf(", Data: %08X", data);
    }

    return ERR_SUCCESS;
}


/* 
    Sets the data value of the subsystem. Takes an integer data, and an integer pointer(optional).
    If pointer exists, stores old data in that memmory. 
    Sets the new data to the data field, and updates the corresponding status.

    Returns:
    - ERR_SUCCESS after the new data is set.

*/
int subsys_data_set(Subsystem *subsystem, unsigned int new_data, unsigned int *old_data){
    if(old_data != NULL){
        *(old_data) = subsystem->data;
    }
    subsystem->data = new_data;
    subsys_status_set(subsystem, STATUS_DATA, 1);
    return ERR_SUCCESS;
}

/* 
    Reads the data value from the subsystem if exists. 
    Clears the data, and clears the corresponding status field after read.

    Returns:
    - ERR_NO_DATA if there is no data to read.
    - ERR_SUCCESS if there is no error

*/
int subsys_data_get(Subsystem *subsystem, unsigned int *dest){
    if(subsystem->status & (1 << STATUS_DATA)){
        *(dest) = subsystem->data;
        subsystem->data = 0;
        subsys_status_set(subsystem, STATUS_DATA, 0); // clear the data field
        return ERR_SUCCESS;
    }

    *(dest) = 0;
    return ERR_NO_DATA;
}