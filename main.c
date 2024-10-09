#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


#include "utils.h"

#define PIPE_SIZE 2024

#define PROMPT "user@machine:pwd$ "
extern char **environ;


bool loop = true;

// TODO: read from config file ._rc

int execute_command(int argc, char **argv){
    printf("executing command with %d args...\n", argc);

    // int execvp(const char *file, char *const argv[]);

    pid_t pid = fork();
    if (pid < 0){
        fprintf(stderr, "fork failed\n");
        return 1;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1) { perror("pipe"); exit(EXIT_FAILURE); }

    if(pid == 0){
        // child process (no read, write)
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        execvp(argv[0], argv);
        perror("execve failed");
        exit(EXIT_FAILURE);
    }

    // Parent process (no write, read)

    close(pipefd[1]);
    char buffer[PIPE_SIZE];
    int bytes_read;
    while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';  // Null-terminate the string
        // printf("BUFFER:\n%s\n", buffer);  // Print the captured output
    }
    wait(NULL);  // Wait for the child to complete

    int output_len = strlen(buffer);
    char *output = calloc(1, output_len+1);
    strncpy(output, buffer, output_len);

    printf("%s\n", output);

    return EXIT_SUCCESS;
}

int parse_command(char *command){
    // Parse
    int argc;
    char **argv = split_on_substring(command, " ", &argc);

    printf("parsing command...\n");
    
    for (int i = 0; i < argc; i++) {
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
    opterr = 0;
    while ((opt = getopt(argc, argv, "ipc:")) != -1) {
        switch (opt) {
            case 'c':
                printf("c flag found: %s, %d\n", optarg, optind);
                number_of_args = argc-optind+1;
                printf("Number of args: %d\n", number_of_args);
                command = calloc(number_of_args + 1, sizeof(char *));
                *command = optarg;
                for(int i = optind, j = 1; i < argc; i++, j++){
                    printf("DDS: %d, %d, %s\n", i, j, argv[i]);
                    command[j] = argv[i];
                }
                command[number_of_args] = NULL;
                break;
            case 'i':
                do_prompt = true;
                break;
            case 'p':
                // keep privilege, implement later
                fprintf(stderr, "Not yet implemented\n");
                break;
            case '?': // ignore invalid
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