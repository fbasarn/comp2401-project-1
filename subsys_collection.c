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

/* 
    Appends a new subsystem to the subsytems collection, inscrements the size of
    the substytems colections 
*/
int subsys_append(SubsystemCollection *subsystems, const Subsystem *subsystem){
    if(subsystems == NULL || subsystem == NULL){
        return ERR_NULL_POINTER;
    }
    if(subsystems->size >= MAX_ARR){
        return ERR_MAX_CAPACITY;
    }
    subsystems->subsystems[subsystems->size] = *(subsystem);
    subsystems->size++;
    return ERR_SUCCESS;
}

/* 
    Function explanation 
*/
int subsys_remove(SubsystemCollection *subsystems, int index){
    return ERR_NO_DATA;
}

/*  
    Finds the provided subsystem name within the subsystem collection if it exists
    and returns the index of the subsystem
*/
int subsys_find(const SubsystemCollection *subsystems, const char *name){
    if(subsystems == NULL || name == NULL){
        return ERR_NULL_POINTER;
    }

    for(int i =0; i < subsystems->size; i++){
        if(strcmp(subsystems->subsystems[i].name, name) == 0){
            return i;
        }
    }
    return ERR_SYS_NOT_FOUND;
}

/* 
    Prints all the subsystems in the collection 
*/
int subsys_collection_print(SubsystemCollection *subsystems){
    if(subsystems == NULL){
        return ERR_NULL_POINTER;
    }

    for(int i=0; i < subsystems->size; i++){
        subsys_print(&(subsystems->subsystems[i]));
    }
    return ERR_SUCCESS;
}

    /* Function explanation */
int subsys_filter(const SubsystemCollection *src, SubsystemCollection *dest, const unsigned char *filter){
    return ERR_NO_DATA;
}
