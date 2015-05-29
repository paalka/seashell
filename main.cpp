#include <stdio.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    pid_t pid = fork();
    cout << pid;
    char *const parmList[] = {"/bin/ls", "-l", "/Users/naiad/", NULL};
    execvp("ls", parmList);
    return 0;
}
