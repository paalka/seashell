#include "parser.h"
#include "lib/dbg.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int get_array_len(char **array)
{
    int i = 0;
    while (array[i] != '\0') {
        i++;
    }

    return i;
}

char **get_subset(int offset, char **array)
{
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
    char *input = readline("> ");
    add_history(input);
    return input;
}

int main(int argc, char **argv)
{
    char *input;
    char **args;
    do {
        input = get_user_input();
        if (strcmp(input, "") != 0) {
            char **tokenized_input = tokenize_str(input, " ");

            char *file = tokenized_input[0];
            args = get_subset(1, tokenized_input);

            execute_ext_command(file, args);
        }
    } while(input);

    return 0;
}
