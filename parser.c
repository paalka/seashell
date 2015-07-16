#include "dbg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **tokenize_str(char string[], char delimiter[])
{
    /*
     * Divides the string 'string' into several strings.
     * The string is divided on each position where the char 'delimiter' is
     * found.
     * Returns a array of strings.
     */

    char **strings = malloc(sizeof(char*) * strlen(string));
    char *token = strtok(string, delimiter);

    int delimiter_count = 0;

    // Use strtok to obtain the tokens from the string.
    while (token) {
        delimiter_count++;

        strings[delimiter_count-1] = token;
        
        // Pass NULL to obtain the next token.
        token = strtok(NULL, delimiter); 
    }
    
    strings[delimiter_count] = 0;

    // Descrease the size of the array to avoid using nesesecary space.
    strings = realloc(strings, sizeof(char*) * (delimiter_count));

    return strings;

error:
    if(strings) free(strings);
    exit(-1);
}

int main(int argc, char **argv)
{
    char *cmd = strdup("hi");
    tokenize_str(cmd, " ");
}
