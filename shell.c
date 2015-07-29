#include "parser.h"
#include "lib/dbg.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int get_array_len(char **array)
{
    /*
     * Get the length of the given array 'array'.
     * Returns the length of the array as an int.
     */

    int i = 0;
    while (array[i] != '\0') {
        i++;
    }

    return i;
}

char **get_subset(int offset, char **array)
{
    /*
     * Get the subset of the given array 'array'.
     * The subset is inclusive and begins at the specified offset 'offset'.
     */

    int i;
    int array_size = get_array_len(array);

    char **args = malloc(sizeof(char*) * array_size);
    check(args != NULL, "Memory allocation failed.");

    for (i = 0; (i + offset) < array_size; i++) {
        args[i] = array[i+offset];
     }

     return args;

 error:
     exit(-1);
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

int main(int argc, char **argv)
{
    char *input;
    char **args;
    char **tokenized_input;
    do {
        input = get_user_input();
        if (strcmp(input, "") != 0) {
            char **tokenized_input = tokenize_str(input, " ");

            char *file = tokenized_input[0];
            args = get_subset(1, tokenized_input);
            tokenized_input = tokenize_str(input);

            free(tokenized_input);
        }
    } while(input);

    return 0;
}
