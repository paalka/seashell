#include "dbg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **tokenize_str(char command[], char delimiter[]) {
    char **res = NULL;
    char *p = strtok(command, delimiter);
    int n_spaces = 0;
    int i = 0;

    while (p) {
        n_spaces++;
        res = realloc(res, sizeof(char*) *n_spaces);
        check(res != NULL, "Mem allocation failed!");
        
        res[n_spaces-1] = p;
        p = strtok (NULL, " ");
    }

    /* realloc one extra element for the last NULL */
    res = realloc(res, sizeof(char*) *(n_spaces+1));
    res[n_spaces] = 0;

    return res;

error:
    if(res) free(res);
    exit(-1);
}

int main(int argc, char **argv) {
    char *cmd = strdup("hi");
    tokenize_str(cmd, " ");
}
