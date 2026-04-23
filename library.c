/*
    Implementation of the string transformation functions defined in library.h.
    See header file for documentation on each of the following functions.
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "library.h"


char* f_reverse(const char* input) {
    size_t len = strlen(input);
    char* reversed = (char*)malloc((len + 1) * sizeof(char));
    if (!reversed) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        reversed[i] = input[len - 1 - i];
    }
    reversed[len] = '\0';
    return reversed;
}

char* f_uppercase(const char* input) {
    size_t len = strlen(input);
    char* uppercased = (char*)malloc((len + 1) * sizeof(char));
    if (!uppercased) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        uppercased[i] = toupper((unsigned char)input[i]);
    }
    uppercased[len] = '\0';
    return uppercased;
}   

char* f_lowercase(const char* input) {
    size_t len = strlen(input);
    char* lowercased = (char*)malloc((len + 1) * sizeof(char));
    if (!lowercased) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        lowercased[i] = tolower((unsigned char)input[i]);
    }
    lowercased[len] = '\0';
    return lowercased;
}   

char* f_togglecase(const char* input) {
    size_t len = strlen(input);
    char* toggled = (char*)malloc((len + 1) * sizeof(char));
    if (!toggled) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)input[i])) {
            toggled[i] = toupper((unsigned char)input[i]);
        } else if (isupper((unsigned char)input[i])) {
            toggled[i] = tolower((unsigned char)input[i]);
        } else {
            toggled[i] = input[i];
        }
    }
    toggled[len] = '\0';
    return toggled;
}

char* f_shuffle(const char* input) {
    size_t len = strlen(input);
    char* shuffled = (char*)malloc((len + 1) * sizeof(char));
    if (!shuffled) {
        return NULL;
    }
    strcpy(shuffled, input);
    for (size_t i = 0; i < len - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (len - i) + 1);
        char temp = shuffled[i];
        shuffled[i] = shuffled[j];
        shuffled[j] = temp;
    }
    return shuffled;
}


char* f_same(const char* input) {
    size_t len = strlen(input);
    char* same = (char*)malloc((len + 1) * sizeof(char));
    if (!same) {
        return NULL;
    }
    strcpy(same, input);
    return same;
}



