#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    char *args[2];

    while (1)
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (feof(stdin))
            {
                printf("\n");
                free(line);
                exit(0);
            }
            perror("getline");
            free(line);
            exit(1);
        }

        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
            continue;

        args[0] = line;
        args[1] = NULL;

        pid = fork();
        if (pid == 0)
        {
            if (execve(line, args, NULL) == -1)
            {
                perror("./hsh");
                exit(EXIT_FAILURE);
            }
        }
        else if (pid > 0)
        {
            wait(NULL);
        }
        else
        {
            perror("fork");
        }
    }

    free(line);
    return (0);
}

