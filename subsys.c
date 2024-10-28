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
    printf("%-16s, %d, %d\n", subsystem->name, subsystem->status, subsystem->data);
    return ERR_SUCCESS;
}

/* Function explanation */
int subsys_status_set(Subsystem *subsystem, unsigned char status, unsigned char value){

    if(status == STATUS_PERFORMANCE || status == STATUS_RESOURCE){
        if ( 0 > value || value > 3) return ERR_INVALID_STATUS;
        subsystem->status = (subsystem->status & ~(1 << status) | (value << status));
    }
    else if(status == STATUS_ERROR || status == STATUS_ACTIVITY || status == STATUS_DATA || status == STATUS_POWER){
        if(value > 1 || value < 0) return ERR_INVALID_STATUS;
        subsystem->status = (subsystem->status & ~(3 << status)) | (value << status);
    }
    else{
        return ERR_INVALID_STATUS;
    }
}

/* Function explanation */
int subsys_status_print(const Subsystem *subsystem){
    if(subsystem == NULL){
        return ERR_NULL_POINTER;
    }
    
    return ERR_NO_DATA;
}


/* Function explanation */
int subsys_data_set(Subsystem *subsystem, unsigned int new_data, unsigned int *old_data){
    return ERR_NO_DATA;
}

/* Function explanation */
int subsys_data_get(Subsystem *subsystem, unsigned int *dest){
    return ERR_NO_DATA;
}