#include "shell.h"

/**
 * builtin_cd - change the current directory
 * @buf: Pointer to the buffer
 * Return: change the current dir or print error
 */
void builtin_cd(char *buf) {
    char cwd[1024];
    char *args[100];
    int i = 0;
    char *token = strtok(buf, " ");

    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        char *home = getenv("HOME");
        if (home != NULL) {
            chdir(home);
        } else {
            fprintf(stderr, "cd: No home directory found.\n");
        }
    } else if (strcmp(args[1], "-") == 0) {
        char *prevDir = getenv("OLDPWD");
        if (prevDir != NULL) {
            chdir(prevDir);
        } else {
            fprintf(stderr, "cd: No previous directory set.\n");
        }
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd");
        }
    }

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        setenv("PWD", cwd, 1);
        setenv("OLDPWD", cwd, 1);
    } else {
        perror("getcwd");
    }
}