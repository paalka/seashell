#include "dbg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **tokenize_str(char command[], char delimiter[]) {
    /*
     * Divides the string 'command' into several strings.
     * The string is divided on each position where the char 'delimiter' is
     * found.
     * Returns a array of strings.
     */

    char **strings = NULL;
    char *token = strtok(command, delimiter);
    int n_spaces = 0;
    int i = 0;

    // Use strtok to obtain the tokens from the string.
    while (token) {
        n_spaces++;
        strings = realloc(strings, sizeof(char*) *n_spaces);
        check(strings != NULL, "Mem allocation failed!");
        
        strings[n_spaces-1] = token;
        
        // Pass NULL to obtain the next token.
        token = strtok (NULL, " "); 
    }
    
    // Increase the size of the array, so that the NULL char can be added.
    strings = realloc(strings, sizeof(char*) *(n_spaces+1));
    strings[n_spaces] = NULL;

    return strings;

error:
    if(strings) free(strings);
    exit(-1);
}

int main(int argc, char **argv) {
    char *cmd = strdup("hi");
    tokenize_str(cmd, " ");
}
