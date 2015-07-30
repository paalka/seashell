#include "parser.h"
#include "builtin.h"
#include "shell.h"
#include "lib/dbg.h"

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int (*builtin_func[]) (char **) = {
    &sea_cd,
    &sea_help,
    &sea_exit,
};

int execute_command(char **args)
{

    int builtin = is_builtin(args[0]);
    int status;
    if (builtin == -1) {
        pid_t pid, wpid;

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
    } else {
        status = (*builtin_func[builtin])(args);
    }

    return 1;
}

int execute_ext_command(char *file, char **args)
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

    error_code = execvp(file, args);
    check(error_code == 0, "Failed to execute command.");

    return EXIT_SUCCESS;

error:
    exit(EXIT_FAILURE);
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
