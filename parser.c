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

    char **res = NULL;
    char *p = strtok(command, delimiter);
    int n_spaces = 0;
    int i = 0;

    // Use strtok to obtain the tokens from the string.
    while (p) {
        n_spaces++;
        res = realloc(res, sizeof(char*) *n_spaces);
        check(res != NULL, "Mem allocation failed!");
        
        res[n_spaces-1] = p;
        
        // Pass NULL to obtain the next token.
        p = strtok (NULL, " "); 
    }
    
    // Increase the size of the array, so that the NULL char can be added.
    res = realloc(res, sizeof(char*) *(n_spaces+1));
    res[n_spaces] = NULL;

    return res;

error:
    if(res) free(res);
    exit(-1);
}

int main(int argc, char **argv) {
    char *cmd = strdup("hi");
    tokenize_str(cmd, " ");
}
