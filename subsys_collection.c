#include "subsystem.h"
#include <string.h>

/*
    This file should contain your documentation and implementations for SubsystemCollection 
    specific functionality; initialization, appending, removal, printing, finding, and filtering.
*/

/* 
    Initialization of the SubsystemCollection, sets the size
    to 0.
 */
int subsys_collection_init(SubsystemCollection *subsystems){
    if(subsystems == NULL){
        return ERR_NULL_POINTER;
    }
    subsystems->size = 0;
    return ERR_SUCCESS;
}

    /* Function explanation */
int subsys_append(SubsystemCollection *subsystems, const Subsystem *subsystem){
    return ERR_NO_DATA;
}

    /* Function explanation */
int subsys_remove(SubsystemCollection *subsystems, int index){
    return ERR_NO_DATA;
}

    /* Function explanation */
int subsys_find(const SubsystemCollection *subsystems, const char *name){
    return ERR_NO_DATA;
}

    /* Function explanation */
int subsys_collection_print(SubsystemCollection *subsystems){
    return ERR_NO_DATA;
}

    /* Function explanation */
int subsys_filter(const SubsystemCollection *src, SubsystemCollection *dest, const unsigned char *filter){
    return ERR_NO_DATA;
}
