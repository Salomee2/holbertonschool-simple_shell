#include "shell.h"
/**
 * execute_command - Executes a command xith execve
 * @command: command to execute
 */

void execute_command(char *command)
{
	char *argv[2], *path, *full_path;
	pid_t pid;
	int status;
	struct stat st;

	argv[0] = command;
	argv[1] = NULL;

	/* checking if command is an absolute path */
	if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
		path = command;
	else
		path = getenv("PATH");
	if (path)
	{
		full_path = malloc(strlen(path) + strlen(command) + 2);
		if (!full_path)
		{
			perror("malloc");
			return;
		}
		sprintf(full_path, "%s%s", path, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
			path = full_path;
		else
			path = NULL;
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Error:");
		return;
	}

	if (pid == 0)
	{
		if (execve(command, argv, environ) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}
