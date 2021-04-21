#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>
// define buffer size to be 80 for this program
#define BUFFER_SIZE 80

// Globals
char* built_in_command[] = {"cd", "help", "exit", "game"};
int num_built_in = 4;
char* command;
char** tokens;
char** tokens2;
/**
 * sigint_handler - the kernel sends a SIGINT to the shell whenever the user types
 * ctrl-c at the keybaord. Catch it and sent it along to the foreground job.
 */
void sigint_handler(int sig) {
    // ignore last '\n' char
    write(1, "Terminating through singal handler\n", 35);
    free(command);
    free(tokens);
    free(tokens2);
    exit(0);
}
// wrapper class to exit a program in our shell
int Exit() {
    printf("exiting...\n");
    free(command);
    free(tokens);
    free(tokens2);
    exit(0);
}

// help method to print out all built-in commands
int help() {
    printf("===================\n");
    printf("build-in commands: \n");
    int i;
    for (i = 0; i < num_built_in; i++){
        printf("%s\n", built_in_command[i]);
    }
    printf("====================\n");
    return 1;
}
// method to get present working directory
int pwd() {
    char pwd[BUFFER_SIZE];
    if (getcwd(pwd, sizeof(pwd)) != NULL) {
        fprintf(stdout, "%s\n", pwd);
    } else {
        printf("pwd error.\n");
    }
    return 1;
}
// implement cd in our shell
int changeDir(char** args) {
    char* dir = (args[1]);
    if (dir == NULL) {
        chdir("/home");
        return 1;
    }
    if (chdir(dir) == -1) {
        printf("No such directory: %s \n", args[1]);
    }
    return -1;
}
// implement a game for our shell
// user need to guess correctly 3 times in order to exit
int game() {
    int randomNum;
    int arr[3];
    int i;
    for (i = 0; i < 3; i++) {
        int guess = 0;
        int try = 0;
        randomNum = rand() % 10 + 1;
        printf("Pick a number between 1-10: \n");
        while (guess != randomNum) {
            printf("Make a guess:");
            scanf("%d", &guess);
            try++;
            if (guess > randomNum) {
                printf("guess a lower number :)\n");
            } else if (guess < randomNum) {
                printf("guess a larger number :)\n");
            } else {
                printf("You are right!");
                arr[i] = try;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        printf("Game %d took you %d times to succeed\n", i + 1, arr[i]);
    }
    return 0;
}

/**
 * check if a command user entered is included in built_in command
 * return 0 if not included or entered command is NULL
 * return 1 if it is include
 */
int checkCommand(char** args) {
    if (args == NULL) {
        return 0;
    }
    int i;
    for (i = 0; i < num_built_in; i++) {
        if (strcmp(args[0], built_in_command[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// execute built_in command
int execute(char** args) {
    int flag;
    if (strcmp(args[0], built_in_command[0]) == 0) {
        flag = changeDir(args);
    } else if (strcmp(args[0], built_in_command[1]) == 0) {
        flag = help();
    } else if (strcmp(args[0], built_in_command[2]) == 0) {
        flag = Exit();
    } else if (strcmp(args[0], built_in_command[3]) == 0) {
        flag = game();
    } else {
        printf("Command not found -- Type 'help' to see all command\n");
    }
    return flag;
}
// Execute one command
int execute_one(char** args) {
    if (args == NULL) {
        return -1;
    }
    if ((checkCommand(args))) {
        execute(args);
    } else {
        pid_t child_pid = fork();
        if (child_pid < 0) {
            printf("\nAn error occurred with creating fork\n");
            return -1;
        }
        if (child_pid == 0) {
            execvp(args[0], args);
        }
        wait(NULL);
    }
    return 0;
}

/** 
 * read user input
 * return args array
 */
char* read_command() {
    command = malloc(sizeof(char)*BUFFER_SIZE);
    if (!command) {
        printf("\nAllocation error. Unable to read. \n");
        free(command);
        exit(1);
    }
    int i = 0;
    int c;
    while (c != '\n') {
        c = getchar();
        command[i] = c;
        i++;
    }
    return command;
}

/** 
 * check if command contains a pipe
 */
int checkPipe(char* args) {
    char* p;
    p = strstr(args, "|");
    if (p != NULL) {
        return 1;
    }
    return 0;
}

/** 
 * parse a command with pipe
 */

char** parse_pipe(char* args) {
    if (args == NULL) {
        return NULL;
    }
    int i = 0;
    tokens = (char **)malloc(sizeof(char *)*BUFFER_SIZE);
    if (!tokens) {
        free(tokens);
        printf("\nBuffer allocation failed.\n");
        exit(1);
    }
    char const delimiter[] = "|";
    char* token = strtok(args, delimiter);
    while (token != NULL) {
        tokens[i] = token;
        i++;
        token = strtok(NULL, delimiter);
    }
    tokens[i] = NULL;
    return tokens;
}

// parse command line
char** parse_command(char* args) {
    if (args == NULL) {
        return NULL;
    }
    int i = 0;
    tokens2 = (char **)malloc(sizeof(char *)*BUFFER_SIZE);
    if (!tokens2) {
        free(tokens2);
        printf("\nBuffer allocation failed.\n");
        exit(1);
    }
    // split between empty spaces new line 
    char* token = strtok(args, " \t\n()<>&;");
    while (token != NULL) {
        tokens2[i] = token;
        i++;
        token = strtok(NULL, " \t\n()<>&;"); 
    }
    tokens2[i] = NULL;
    return tokens2;
}

int execute_pipe(char** first, char** last) {
    int fd[2];
    if (pipe(fd) == -1) {
        printf("pipe error\n");
        return -1;
    }
    pid_t pid1 = fork();
    if (pid1 < 0) {
        printf("fork error\n");
        return -1;
    }
    if (pid1 == 0) {
        dup2(fd[1], STDOUT_FILENO);
        execvp(first[0], first);
    }
    
    pid_t pid2 = fork();
    
    if (pid2 < 0) {
        printf("fork error\n");
        return -1;
    }
    if (pid2 == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execvp(last[0], last);
    } else {
        close(fd[0]);
        close(fd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }
    return 0;
}

/** 
 * check if a input command is valid
 */
int isValid(char* args) {
    if (args == NULL || args[0] == '\n' || args[0] == '\t' || args[0] == '\r' 
        || args[0] == '\a' || args[0] == ' ') {
            return 0;
        }
    return 1;
}

int main() {
    alarm(200);
    signal(SIGINT, sigint_handler);
    printf("Welcome to our mini shell!\n");
    printf("You can terminate anytime by pressing Ctrl+C\n");
    printf("You can also terminate at prompt line by returning exit\n");

    while (1) {
        printf("wilbur-shell>");
        char* readline = read_command();
        if (readline != NULL && isValid(readline)) {
            if (checkPipe(readline) > 0) {
                char** pipe_command = parse_pipe(readline);
                char** first = parse_command(pipe_command[0]);
                char** last = parse_command(pipe_command[1]); 
                execute_pipe(first, last);
            } else {
                char** command = parse_command(readline);
                execute_one(command);
            }
        }
    }
    return 0;
    
}
