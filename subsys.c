#include "subsystem.h"
#include <string.h>

/*
    This file should contain the implementations for Subsystem specific functionality.
    Initialization, printing, setting and getting data and statuses.
*/


/* Function explanation */
int subsys_init(Subsystem *subsystem, const char *name, char status){
    return ERR_NO_DATA;
}

/* Function explanation */
int subsys_print(Subsystem *subsystem){
    return ERR_NO_DATA;
}

/* Function explanation */
int subsys_status_set(Subsystem *subsystem, unsigned char status, unsigned char value){
    return ERR_NO_DATA;
}

/* Function explanation */
int subsys_status_print(const Subsystem *subsystem){
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