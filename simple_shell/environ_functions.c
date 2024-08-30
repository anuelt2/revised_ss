#include "shell.h"

void get_env(void)
{
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; environ[i][j] != '\0'; j++)
		{
			write(STDOUT_FILENO, &environ[i][j], 1);
		}
		write(STDOUT_FILENO, "\n", 1);
	}
}

int set_env(char *var, char *val, int overwrite)
{
	char **environ_copy = copy_environ();
	/*char **temp;*/
	int i = 0, var_len = _strlen(var);
	char *new_var = _concat(var, val);
	int environ_copy_size = get_env_size(environ_copy);

	if (!var || _strcon(var, '=') != 0)
		return (-1);

	while (environ_copy[i] != NULL)
	{
		if (_strncmp(environ_copy[i], var, var_len) == 0 && environ_copy[i][var_len] == '=')
			return (overwrite ? replace_var(environ_copy, new_var, i) : 0);
		i++;
	}

	environ_copy = realloc_env(environ_copy, new_var, environ_copy_size);
	return (environ_copy ? 0 : -1);
}

int replace_var(char **environ_copy, char *new_var, int index)
{
	free(environ_copy[index]);
	environ_copy[index] = new_var;
	return (0);
}

char **realloc_env(char **environ_copy, char *new_var, int size)
{
	char **temp = realloc(environ_copy, sizeof(char *) * (size + 2));

	if (!temp)
	{
		free(new_var);
		return (NULL);
	}
	temp[size] = new_var;
	temp[size + 1] = NULL;
	environ = temp;
	return (environ);
}

char *get_env_path(char **envp, int size)
{
	int i;

	(void)size;
	for (i = 0; envp[i]; i++)
	{
		if (_strncmp(envp[i], "PATH=", 5) == 0)
			return (strdup(&envp[i][5]));
	}
	return (NULL);
}
