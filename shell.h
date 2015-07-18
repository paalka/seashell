#ifndef _shell_h
#define _shell_h

int execute_ext_command(char *file, char **params);
int *process_input(void);
int get_array_len(char **array);
char **get_subset(int offset, char **array);

struct Config {
    char *current_directory;
    char **search_path;
};

#endif
