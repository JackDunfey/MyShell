#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "utils.h"

#define PROMPT "user@machine:pwd$ "

bool loop = true;

// TODO: read from config file ._rc

int execute_command(int argc, char **argv){
    for (int i = 0; i < argc; i++) {
        printf("%d: %s\n", i+1, argv[i]);
    }
    return 0;
}

int parse_command(char *command){
    // Parse
    int token_count;
    char **argv = split_on_substring(command, " ", &token_count);

    printf("executing command...\n");

    for (int i = 0; i < token_count; i++) {
        printf("%d: %s\n", i+1, argv[i]);
    }

    return 0;
}

// Start the shell
int main(int argc, char **argv){
    int opt;
    int number_of_args;
    char **command = NULL;
    bool do_prompt = false;
    while ((opt = getopt(argc, argv, "i:p:c:")) != -1) {
        switch (opt) {
            case 'c':
                printf("c flag found: %s, %d\n", optarg, optind);
                int number_of_args = argc-optind+1;
                *command = optarg;
                for(int i = optind, j = 1; i < argc; i++, j++){
                    command[j] = argv[i];
                }
                break;
            case 'i':
                do_prompt = true;
                break;
            case 'p':
                // keep privilege, implement later
                fprintf(stderr, "Not yet implemented\n");
                break;
            default:
                break;
        }
    }

    if (command) {
        execute_command(number_of_args, command);
        return 0;
    }

    // Temporary
    char *prompt = PROMPT;

    while (loop) {
        if (do_prompt)
            printf("%s", prompt);
        
        char command_buffer[256];
        if(fgets(command_buffer, sizeof(command_buffer), stdin)) {
            if(trim_newline(command_buffer)){
                printf("%s\n", command_buffer);
            } else {
                fprintf(stderr, "Bad trim\n");
            }
        }
    }
}