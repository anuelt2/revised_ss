#include "shell.h"

int cd_exec(char *args[], char **envp)
{
	if (args[1] == NULL)
	{
		return (cd_to_path(get_home_path(envp, home_path_size(envp))));
	}
	return (cd_args(args, envp));
}

int cd_to_path(const char *path)
{
	if (!path)
	{
		fprintf(stderr, "cd: no home directory\n");
		return (-1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (-1);
	}
	set_oldpwd();
	set_pwd();
	return (1);
}

int cd_args(char **args, char **envp)
{
	if (strcmp(args[1], "-") == 0)
		return (cd_to_previous(envp));

	return (cd_to_path(args[1]));
}

int cd_to_previous(char **envp)
{
	char buf[1024];
	const char *path = get_oldpwd_path(envp, oldpwd_path_size(envp));

	if (!path)
		return (-1);

	fprintf(stdout, "%s\n", path);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (-1);
	}
	getcwd(buf, sizeof(buf));
	setenv("PWD", buf, 1);
	return (1);
}
