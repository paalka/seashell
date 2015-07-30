#include "builtin.h"
#include "lib/dbg.h"
#include <string.h>
#include <unistd.h>

char *builtin_cmds[] = {
    "cd",
    "help",
    "exit"
};

int sea_num_builtins()
{
    return sizeof(builtin_cmds) / sizeof(char *);
}

int is_builtin(char *arg)
{
    for (int i = 0; i < sea_num_builtins(); i++) {
        if (strcmp(arg, builtin_cmds[i]) == 0) {
            return i;
        }
    }    

    return -1;
}

int sea_cd(char **args)
{
    check(args[1] != NULL, "Missing argument");

    int status = chdir(args[1]);
    check(status == 0, "Could not change dir.");

    return 1;

error:
    return -1;
}

int sea_help(char **args)
{
    printf("Hah, nope.");
    return 0;
}

int sea_exit(char **args)
{
    return 0;
}


