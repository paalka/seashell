#include "lib/dbg.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

char **tokenize_str(char line[])
{
    /*
     * Divides the string 'string' into several strings.
     * The string is divided on each position where the char 'delimiter' is
     * found.
     * Returns a array of strings.
     */

    int bufsize = TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(sizeof(char*) * bufsize);
    check(tokens != NULL, "Memory allocation failed.");

    char *token = strtok(line, TOK_DELIMITERS);

    while (token) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, sizeof(char*) * bufsize);
            check(tokens != NULL, "Memory allocation failed.");
        } 
        
        // Pass NULL to obtain the next token.
        token = strtok(NULL, TOK_DELIMITERS); 
    }
    
    // Descrease the size of the array to avoid using unnecessary space.
    tokens = realloc(tokens, sizeof(char*) * (position+1));
    check(tokens != NULL, "Memory reallocation failed.");
    tokens[position] = NULL;

    return tokens;

error:
    if(tokens) free(tokens);
    exit(-1);
}

char *readline(void)
{
  int bufsize = RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  check(buffer != NULL, "Allocation error.");

  while (1) {
    c = getchar();

    // If we hit EOF or a new line, replace it with a null character and
    // return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize += RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      check(buffer != NULL, "Allocation error.");
    }
  }

  return buffer;

error:
  exit(EXIT_FAILURE);
}
