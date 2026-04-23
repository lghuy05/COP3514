#pragma once

/*
    Function prototypes for string transformation functions.
    We provide a few to get you started but feel free to add
    your own! Just make sure to implement them in library.c and 
    add their names and pointers to the library_functions and 
    library_function_names arrays in main.c.
*/

// returns a new string that is the reverse of the input string
char* f_reverse(const char* input);     

// returns a new string that is the uppercase version of the input string
char* f_uppercase(const char* input); 

// returns a new string that is the lowercase version of the input string
char* f_lowercase(const char* input);   

// returns a new string that has the case of each character toggled
char* f_togglecase(const char* input);  

// returns a new string that is a shuffled version of the input string
char* f_shuffle(const char* input);     

// returns a new string that is identical to the input string
char* f_same(const char* input);      
