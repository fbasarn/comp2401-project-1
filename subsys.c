#include "subsystem.h"
#include <string.h>

/*
    This file should contain the implementations for Subsystem specific functionality.
    Initialization, printing, setting and getting data and statuses.
*/


/* 
    Initialization of the memory pointed by the subsystem,
    initializes the name and status with provided values and 
    sets the data to 0
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
    Prints the name, status and the data of the subsystem provided
*/
int subsys_print(Subsystem *subsystem){
    if(subsystem == NULL){
        return ERR_NULL_POINTER;
    }
    printf("Name: %16s Status: ", subsystem->name);
    subsys_status_print(subsystem);
    return ERR_SUCCESS;
}

/* Sets any of the 5 status of the subsystem to the provided value */
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

/* Prints all 5 status fields of the subsystem */
int subsys_status_print(const Subsystem *subsystem) {
    if (subsystem == NULL) {
        return ERR_NULL_POINTER;
    }
    for (int i = 7; i >= 0; i--) {
        int bit_value = (subsystem->status & (1 << i)) >> i;
        printf("%d ", bit_value);
    }
    return ERR_SUCCESS;
}


/* Sets the data value of the subsystem */
int subsys_data_set(Subsystem *subsystem, unsigned int new_data, unsigned int *old_data){
    if(new_data == NULL){
        return ERR_NO_DATA;
    }
    if(old_data != NULL){
        *(old_data) = subsystem->data;
    }
    subsystem->data = new_data;
    subsys_status_set(subsystem, STATUS_DATA, 1);
    return ERR_SUCCESS;
}

/* Function explanation */
int subsys_data_get(Subsystem *subsystem, unsigned int *dest){
    return ERR_NO_DATA;
}