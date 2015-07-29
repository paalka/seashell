#ifndef _parser_h
#define _parser_h

char **tokenize_str(char string[], char delimiter[]);
#define RL_BUFSIZE 1024

char *readline(void);

#endif
