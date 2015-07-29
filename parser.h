#ifndef _parser_h
#define _parser_h

#define RL_BUFSIZE 1024
#define TOK_BUFSIZE 64
#define TOK_DELIMITERS " \t\r\n\a"

char **tokenize_str(char line[]);
char *readline(void);

#endif
