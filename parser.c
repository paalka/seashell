#include "lib/dbg.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char **tokenize_str(char string[], char delimiter[])
{
    /*
     * Divides the string 'string' into several strings.
     * The string is divided on each position where the char 'delimiter' is
     * found.
     * Returns a array of strings.
     */

    char **strings = malloc(sizeof(char*) * strlen(string));
    check(strings != NULL, "Memory allocation failed.");

    char *token = strtok(string, delimiter);
    int delimiter_count = 0;

    while (token) {
        delimiter_count++;

        strings[delimiter_count-1] = token;
        
        // Pass NULL to obtain the next token.
        token = strtok(NULL, delimiter); 
    }
    
    strings[delimiter_count] = 0;

    // Descrease the size of the array to avoid using unnecessary space.
    strings = realloc(strings, sizeof(char*) * (delimiter_count));
    check(strings != NULL, "Memory reallocation failed.");

    return strings;

error:
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
