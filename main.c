#include "shell.h"
/**
 * main - entry point for simple shell
 * Return: 0on succes or 1 if fail
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		execute_command(line);
	}
	free(line);
	return (0);
}
