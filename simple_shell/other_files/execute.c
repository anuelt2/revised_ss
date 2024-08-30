#include "shell.h"

/**
 * exec_builtin - Executes built-in commands
 * @args: Array of command-line arguments
 * @envp: Pointer to environment variables
 *
 * Return: Void
 */

int exec_builtin(char *args[], char **envp)
{
	if (args[0] != NULL)
	{
		if (strcmp(args[0], "exit") == 0)
			exit_function(args);
		if (strcmp(args[0], "cd") == 0)
		{
			cd_exec(args, envp);
			return (1);
		}
	}
	return (0);
}

/**
 * exec_external - Executes external commands
 * @pathname: Program to execute
 * @args: Array of commandline arguments
 * @envp: Pointer to array of environment variables
 * @cmd_count: Count of commands entered in each shell session
 *
 * Return: Void
 */

void exec_external(char *pathname, char *args[], char *envp[], int cmd_count)
{
	pid_t child_pid;
	int status;
	char *full_path;

	full_path = find_ext_file(pathname, envp, cmd_count);
	if (is_executable(full_path))
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Fork Error");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if ((execve(full_path, args, envp)) == -1)
			{
				perror("./shell");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}
}
