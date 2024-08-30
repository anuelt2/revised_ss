#include "shell.h"

int main(int argc, char *argv[], char *envp[])
{
	int cmd_count = 0;
	char *str;
	char **args;

	(void)argc;
	(void)argv;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();

		str = get_input_line();
		cmd_count++;
		args = parse_input(str);

		execute_command(args, envp, cmd_count);
		free_resources(args, str);
	}

	return (0);
}

char *get_input_line(void)
{
	char *input = malloc(128);

	if (!input)
		return (NULL);

	return (get_input(input, 128));
}

char **parse_input(char *str)
{
	return (string_tok(str, DELIM));
}

void execute_command(char **args, char **envp, int cmd_count)
{
	if (!args || !args[0])
		return;

	if (env_func_caller(args) != 0)
	{
		int exec = exec_builtin(args, envp);

		if (exec == 1)
			return;

		exec_external(args[0], args, envp, cmd_count);
	}
}

void free_resources(char **args, char *str)
{
	int i;

	if (args)
	{
		for (i = 0; args[i] != NULL; i++)
			_free((void **)&args[i]);
		_free((void **)&args);
	}

	if (str)
		free(str);
}

void _free(void **ptr)
{
	if (ptr && *ptr)
	free(*ptr), *ptr = NULL;
}
