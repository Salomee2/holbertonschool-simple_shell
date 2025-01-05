#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command)
{
	pid_t pid = fork();
	
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		char *args[2];
		args[0] = command;
		args[1] = NULL;
		if (execve(args[0], args, NULL) == -1)
		{
			perror("./hsh");
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

