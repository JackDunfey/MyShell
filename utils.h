#ifndef utils_H
#define utils_H

bool trim_newline(char *s);
static char **split_on_substring(const char *input, const char *delimiter, int *token_count);
static void free_tokens(char **tokens, int token_count);

#endif