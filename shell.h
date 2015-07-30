#ifndef _shell_h
#define _shell_h

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>

int execute_ext_command(char *file, char **args);
int *process_input(void);
int execute_command(char **args);
void print_prompt(char *cwd_buf, size_t buf_siz);

#endif
