#include "shell.h"

/**
 * cd_args - Handles cd built-in command arguments
 * @args: Pointer to the cd command arguments
 * @envp: Pointer to environment variables
 *
 * Return: 1 (success)
 */

int cd_args(char **args, char **envp)
{
	const char *path;
	char buf[1024];
	int size;

	(void)envp;
	if (strcmp(args[1], "-") == 0)
	{
		size = oldpwd_path_size(envp);
		path = get_oldpwd_path(envp, size);
		getcwd(buf, sizeof(buf));
		setenv("OLDPWD", buf, 1);
		fprintf(stdout, "%s\n", path);
		chdir(path);
		getcwd(buf, sizeof(buf));
		setenv("PWD", buf, 1);
		return (1);
	}
	else
	{
		getcwd(buf, sizeof(buf));
		setenv("OLDPWD", buf, 1);
		path = args[1];
		chdir(path);
		getcwd(buf, sizeof(buf));
		setenv("PWD", buf, 1);
		return (1);
	}

	return (0);
}
