#include "parser.h"
#include "builtin.h"
#include "shell.h"
#include "lib/dbg.h"

#include <sys/wait.h>
#include <sys/types.h>
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
        // create a child process for the command to be executed.
        pid = fork();
        check(pid != -1, "Failed to create child process.");

        if (pid == 0) {
            status = execute_ext_command(args[0], args);
        } else if (pid < 0) {
            status = -1;
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
error:
    return -1;
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

    error_code = execvp(file, args);
    check(error_code == 0, "Failed to execute command.");

    return EXIT_SUCCESS;
error:
    return EXIT_FAILURE;
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

void print_prompt(char *cwd_buf, size_t buf_siz)
{
    printf("\n%s%s%s\n> ", ANSI_COLOR_BLUE, getcwd(cwd_buf, buf_siz), ANSI_COLOR_RESET);
    return;
}

void main_loop(void)
{
    char *input;
    char cwd[1024];
    size_t cwd_buf = sizeof(cwd);
    char **tokenized_input;
    int status;
    do {
        print_prompt(cwd, cwd_buf);
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
