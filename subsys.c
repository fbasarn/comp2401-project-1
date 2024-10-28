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
    printf("Name: %s Status: ", subsystem->name);
    subsys_status_print(subsystem);
    return ERR_SUCCESS;
}

/* Function explanation */
int subsys_status_set(Subsystem *subsystem, unsigned char status, unsigned char value){
    if(status == STATUS_PERFORMANCE || status == STATUS_RESOURCE){
        if(value < 0 || value > 3) {
            printf("The value is invalid!\n");
            return ERR_INVALID_STATUS;
        }
        printf("the status code and value is valid!\n");
        
    }
    if(status == STATUS_DATA || status == STATUS_POWER || status == STATUS_ERROR || status == STATUS_ACTIVITY){
        if(value < 0 || value > 1) {
            printf("The value is invalid!\n");
            return ERR_INVALID_STATUS;
        }
        printf("the status code and value is valid!\n");
    }
    else{
        printf("the status code is invalid!\n");
        return ERR_INVALID_STATUS;
    }
    return ERR_SUCCESS;
}

/* Function explanation */
int subsys_status_print(const Subsystem *subsystem) {
    if (subsystem == NULL) {
        return ERR_NULL_POINTER;
    }
    for (int i = 0; i < 8; i++) {
        int bit_value = (subsystem->status >> (7 - i)) & 1;
        printf("%d ", bit_value);
    }
    return ERR_SUCCESS;
}


/* Function explanation */
int subsys_data_set(Subsystem *subsystem, unsigned int new_data, unsigned int *old_data){
    return ERR_NO_DATA;
}

/* Function explanation */
int subsys_data_get(Subsystem *subsystem, unsigned int *dest){
    return ERR_NO_DATA;
}