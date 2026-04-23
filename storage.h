#pragma once

/*
    Definition of a data structure called "Storage" that can hold 
    an arbitrary number of function pointers, and function prototypes 
    for the functions that operate on this data structure.
    The functions defined here will allow us to create a storage instance, 
    add functions to it, retrieve functions from it, and execute all the 
    functions in the storage with a given input string.             
*/

#include <stdlib.h>

/*  
    We define a new type that represents a pointer to a function 
    that takes a const char* as input and returns a char* as output.
    This will make it easier to write the following code.
*/
typedef char *(*function_pointer_t)(const char *);

/*  
    Our "Storage" is a struct containing a dynamical array of elements 
    of the above-defined function pointer type, and a variable to keep 
    track of the size of the array.
*/
struct storage_s {
    function_pointer_t* functions_array;
    size_t functions_array_size;
};

/*
    We also define a type "Storage" (for convenience) that is an alias 
    for "struct storage_s".
*/
typedef struct storage_s Storage;

/*
    Creates dynamically and returns a new storage instance.
    Initializes its functions_array field to NULL and its 
    functions_array_size field 0.
    Takes no parameters.
    Returns a pointer to the new storage instance, or NULL if 
    malloc failed to allocated memory.
*/
Storage* storage_create(void);

/*
    Destroys a storage instance.
    This function takes a pointer on the storage data structure to free.
    Free all memory that was dynamically allocated for the structure
    or any of its components.
    This function returns nothing.
*/
void storage_destroy(Storage *storage);

/*
    Adds a function to the storage.
    This function takes a pointer to the storage instance and a pointer to the
    function we want to add inside of it. If it finds that the array of pointer
    on functions inside the storage parameter is NULL, it uses malloc to allocate
    one just big enough to contain the function passed as 2nd parameter. 
    If this array is not NULL, it uses instead realloc to reallocate a bigger
    array of functions (one more element than the current size).
    The function passed as parameter is then added at the last index of our new
    array and its size variable updated accordingly.
    Returns 0 on success, or -1 if any of the parameters is NULL, or if realloc
    or malloc fail to allocate memory for us.
*/
int storage_add_function(Storage *storage, function_pointer_t function);

/*
    Retrieves a function from the storage at the specified index.
    Takes a pointer to the storage instance and the index of the function to retrieve.
    Returns a pointer to the function, or NULL if the index is out of bounds.
*/
char *(*storage_get_function(Storage *storage, size_t index))(const char *);

/*
    Retrieves the size of the storage.
    Takes a pointer to the storage instance.
    Returns the number of functions in the storage.
*/
size_t storage_get_size(Storage *storage);

/*
    Executes all functions in the storage. The input parameter is passed
    as argument to the function stored at index 0. More generally, the string 
    resulting from step #n will be used as input for step #(n+1).
    
    This function takes a pointer to the storage instance and the initial 
    input string.

    This function returns a dynamically allocated array of strings that 
    contains each of the string resulting from the execution of one of the
    functions.

    This function returns NULL if either parameter is NULL, if you were not
    able to allocate memory for the array of strings that you need to return.
*/
char **storage_execute_all(Storage *storage, const char *input);



