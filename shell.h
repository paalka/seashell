#ifndef _shell_h
#define _shell_h

int execute_ext_command(char *file, char **args);
int *process_input(void);
int execute_command(char **args);

#endif
