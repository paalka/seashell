#include "parser.h"
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    pid_t pid = fork();
    //cout << pid;
    char foo[] = "/bin/ls";
    char *parmList = {"/bin"};


    execvp("ls", parmList);
    return 0;
}
