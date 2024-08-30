#include "shell.h"

/**
 * main - Shell program entry point
 * @argc: Number of commandline arguments
 * @argv: Pointer to array of commandline arguments
 * @envp: Pointer to array of environment variables
 *
 * Return: Always 0 (Success)
 */

int main(int argc, char *argv[], char *envp[])
{
	char input[128];
	char *delim = DELIM;
	char *str;
	char *pathname;
	char **args;
	int cmd_count, exec;

	(void)argc;
	(void)argv;
	cmd_count = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			display_prompt();
		}
		str = get_input(input, sizeof(input));
		cmd_count++;
		args = string_tok(str, delim);
		pathname = args[0];
		if (args[0] == NULL)
		{
			free(str);
			free(args);
			continue;
		}
		if (env_func_caller(args) != 0)
		{
			exec = exec_builtin(args, envp);
			if (exec == 1)
			{
				continue;
			}
			exec_external(pathname, args, envp, cmd_count);
			free(args);
			free(str);
		}
	}

	return (0);
}
