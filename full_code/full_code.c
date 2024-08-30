#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

#define TOKEN_ARRAY_SIZE 20
#define DELIM " \t\n"

void display_prompt(void);
char *get_input(char *lineptr, size_t len);
char **string_tok(char *str, char *delim);
int exec_builtin(char *args[], char **envp);
void exec_external(char *pathname, char *args[], char *envp[], int cmd_count);
char *get_env_path(char **envp, int size);
int _path_size(char **envp);
char *find_command(char *pathname, char **envp);
char *_concatenate(char *dir, char *pathname);
int is_executable(char *full_path);
char *find_ext_file(char *pathname, char **envp, int cmd_count);
char *get_home_path(char **envp, int size);
int home_path_size(char **envp);
char *get_pwd_path(char **envp, int size);
int pwd_path_size(char **envp);
char *get_oldpwd_path(char **envp, int size);
int oldpwd_path_size(char **envp);
int cd_args(char **args, char **envp);
void exit_function(char *args[]);
int set_oldpwd(void);
int set_pwd(void);
int cd_exec(char *args[], char **envp);
void _free(void **ptr);

/* str_utils.c */
int _strlen(char *str);
int _strcmp(char *str1, char *str2);
int _strncmp(char *str1, char *str2, int n);
char *_concat(char *var, char *val);
int _strcon(char *str, char c);

/* str_utils.c */
int _atoi(char *s);

/* exec_utils */
char *get_env_path(char **envp, int size);
int _path_size(char **envp);
char *find_command(char *pathname, char **envp);
char *_concatenate(char *dir, char *pathname);
int is_executable(char *full_path);

/* env_utils.c */
int env_size(void);
int get_env_size(char **env);
char **copy_environ(void);
int env_func_caller(char **args);

/* env_functions */
extern char **environ;
void get_env(void);
int set_env(char *var, char *val, int overwrite);
int unset_env(char *var);

char *shell_path_exec(char *pathname, char *full_path);

#endif

int main(int argc, char *argv[], char *envp[])
{
    (void)argc;
    (void)argv;
    int cmd_count = 0;
    char *str;
    char **args;

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

    return get_input(input, 128);
}

char **parse_input(char *str)
{
    return string_tok(str, DELIM);
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

int cd_exec(char *args[], char **envp)
{
    if (args[1] == NULL)
    {
        return cd_to_path(get_home_path(envp, home_path_size(envp)));
    }
    return cd_args(args, envp);
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
        return cd_to_previous(envp);

    return cd_to_path(args[1]);
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
    char **environ_copy = copy_environ(), **temp;
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
    for (int i = 0; envp[i]; i++)
    {
        if (_strncmp(envp[i], "PATH=", 5) == 0)
            return (_strdup(&envp[i][5]));
    }
    return (NULL);
}

char *find_command(char *pathname, char **envp)
{
    char *path_env = get_env_path(envp, _path_size(envp)), *dir, *full_path = NULL;
    if (!path_env) return (NULL);

    for (dir = strtok(path_env, ":"); dir; dir = strtok(NULL, ":"))
    {
        full_path = _concatenate(dir, pathname);
        if (is_executable(full_path))
            break;
        free(full_path);
        full_path = NULL;
    }
    free(path_env);
    return (full_path);
}

void exit_function(char *args[])
{
    int status = args[1] ? _atoi(args[1]) : 0;
    free_resources(args, NULL);
    exit(status);
}
