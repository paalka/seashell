#include "parser.h"
#include "lib/dbg.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int execute_command(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) {
        status = execute_ext_command(args[0], args);
    } else if (pid < 0) {
        perror("seashell");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}


int execute_ext_command(char *file, char **params)
{
    /*
     * Executes an external command by spawning an subprocess, and then
     * executing the command. The file to execute is set by the string 'file',
     * the params for this command is determined by 'params'.
     * Returns an int indicating whether the execution was successful or not. 
     */

    int error_code;

    // create a child process for the command to be executed.
    pid_t pid = fork();
    check(pid != -1, "Failed to create child process.");

    error_code = execvp(file, params);
    check(error_code == 0, "Failed to execute command.");

    return 0;

error:
    // TODO: Clean up the child process.
    return -1;
}

char *get_user_input(void)
{
    /*
     * Obtains one or multiple lines of input from the user through stdin, and
     * adds it to the history.
     * Returns the string given by the user.
     */

    char *input = readline();
    return input;
}

void main_loop(void)
{
    char *input;
    char **tokenized_input;
    int status;

    do {
        input = get_user_input();
        if (strcmp(input, "") != 0) {
            tokenized_input = tokenize_str(input);
            status = execute_command(tokenized_input);

            free(tokenized_input);
        }
    } while (status);
}

int main(int argc, char **argv)
{
    main_loop();

    return EXIT_SUCCESS;
}
