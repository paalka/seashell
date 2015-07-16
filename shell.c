#include "parser.h"
#include "lib/dbg.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int execute_ext_command(char *file, char **params)
{
    int error_code;

    // create a child process for the command to be executed.
    pid_t pid = fork();

    error_code = execvp(file, params);
    check(error_code == 0, "Failed to execute command.");
error:
    // TODO: Clean up the child process.
    return -1;
}


char *get_user_input(void)
{
    char *input = readline("> ");
    add_history(input);
    return input;
}

int main(int argc, char **argv)
{
    return 0;
}
