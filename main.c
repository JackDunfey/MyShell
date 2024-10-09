#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "utils.c"

#define PROMPT "user@machine:pwd$ "

bool loop = true;

// TODO: read from config file ._rc

// Start the shell
int main(int argc, char **argv){
    int opt;
    char *command;
    bool do_prompt = false;
    while ((opt = getopt(argc, argv, "i:p:c")) != -1) {
        switch (opt) {
            case 'c':
                command = optarg;
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

    // Temporary
    char *prompt = PROMPT;

    while (loop) {
        if (do_prompt)
            printf("%s", prompt);
        
        char command_buffer[256];
        if(fgets(command_buffer, sizeof(command_buffer), stdin)) {
            
            strlen
        }
    }
}