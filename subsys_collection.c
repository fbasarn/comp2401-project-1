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
    printf("Current Size: %d\n", subsystems->size);

    return ERR_SUCCESS;
}

/* 
    Removes the subsystem at the index given as parameter
*/
int subsys_remove(SubsystemCollection *subsystems, int index){
    if(subsystems == NULL) return ERR_NULL_POINTER;
    if(subsystems->size == 0) return ERR_NO_DATA;
    if(index < 0 || index >= subsystems->size) return ERR_INVALID_INDEX;

    for(int i = index; i < subsystems->size - 1; i++){
        subsystems->subsystems[i] = subsystems->subsystems[i + 1];
    }
    subsystems->size--;

    return ERR_SUCCESS;
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
        printf("- [ ");
        subsys_print(&(subsystems->subsystems[i]));
        printf(" ]");
        printf("\n");
    }
    return ERR_SUCCESS;
}

/* 
    Filter out the subsystems from the subsystem collection based on different status criteria provided
    as a parameter:
    - Accepts a string filter with 8 characters. The characters must be:
    - * if that certain status criteria doesn't matter
    - 0 or 1 otherwise
 */
int subsys_filter(const SubsystemCollection *src, SubsystemCollection *dest, const unsigned char *filter){
    if(src == NULL || filter == NULL || dest == NULL) return ERR_NULL_POINTER;
    
    unsigned char filt = 0;
    unsigned char wildcard = 0;

    for(int i = 0; i < 8; i++){
        if(*(filter+i) == '1') filt = filt | 1 << (7 - i); 
        else if (*(filter+i) == '*') wildcard = wildcard | 1 << (7 - i);
    }

    filt = ~(filt); 

    for(int i=0; i < src->size; i++){
        if(((filt ^ src->subsystems[i].status) | wildcard) != 255){
            continue;
        }
        subsys_append(dest, &src->subsystems[i]);
    }

    //print the filtered collection
    if(dest->size == 0){
        printf("0 subsystems found with the criteria given. Try again with a different criteria.\n");
    }else{
        subsys_collection_print(dest);
    }
    
    return ERR_SUCCESS;
}

