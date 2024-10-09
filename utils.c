#include <stdbool.h>
#include <string.h>
bool trim_newline(char *s){
    if (!s) return false;
    int length = strlen(s);
    if (length <= 0) return false;
    *(s+length-1) = '\0';
    return true;
}

#include <stdio.h>
#include <stdlib.h>
#define MAX_TOKENS 256
char **split_on_substring(const char *input, const char *delimiter, int *token_count) {
    char *input_copy;
    char *next_token;
    char **result;
    int count = 0;
    int delimiter_len = strlen(delimiter);

    result = calloc(MAX_TOKENS, sizeof(char *));
    if (!result){
        fprintf(stderr, "Failed to allocate memory for result\n"); 
        return NULL;
    }

    input_copy = malloc(strlen(input)+1);
    if(!input_copy) {
        fprintf(stderr, "Failed to allocate memory for input_copy\n"); 
        free(result);
        return NULL;
    }
    strcpy(input_copy, input);  // Copy the input string
    char *current_pos = input_copy;

    // Split the string into tokens using the given delimiter
    while (current_pos && count < MAX_TOKENS) {
        next_token = strstr(current_pos, delimiter);  // Find the next occurrence of the delimiter
        if (next_token) {
            *next_token = '\0';  // Null-terminate the token
        }

        // Skip empty tokens
        if (*current_pos) {
            result[count] = calloc(strlen(current_pos) + 1, sizeof(char));
            if (!result[count]) {
                fprintf(stderr, "Failed to allocate memory for token\n");
                // Free previously allocated tokens
                for (int i = 0; i < count; i++) {
                    free(result[i]);
                }
                free(input_copy);
                free(result);
                return NULL;
            }
            strcpy(result[count], current_pos);  // Copy the token to result
            count++;
        }

        if (next_token) {
            current_pos = next_token + delimiter_len;  // Move past the delimiter
        } else {
            break;  // No more delimiters found
        }
    }

    // Set the token count
    result[count] = NULL;
    *token_count = count;

    // Free the mutable copy
    free(input_copy);

    return result;  // Return the array of strings
}

void free_tokens(char **tokens, int token_count){
    for (int i = 0; i < token_count; i++) { free(tokens[i]); } // Free each token
    free(tokens);  // Free the array of tokens
}

