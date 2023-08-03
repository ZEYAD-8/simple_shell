#include "main.h"

/**
 * search_system - looks for the file name in the path and determine if exists
 *
 * @filename: the name of the file to look up
 *
 * Return: the full path for the file, if it exists. Otherwise, NULL.
*/
char *search_system(const char *filename)
{
	char *samefile, *path_env, **envp, *path_copy, *path_entry, *path_return;
	int i;

	if (filename == NULL)
		return (NULL);
	if (access(filename, X_OK) == 0)
	{
		samefile = malloc(sizeof(char) * (strlen(filename) + 1));
		strcpy(samefile, filename);
		return (samefile);
	}
	path_env = NULL;
	for (i = 0, envp = environ; envp[i] != NULL; i++)
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break;
		}
	if (path_env != NULL)
	{
		path_copy = malloc(sizeof(char) * (strlen(path_env) + 1));
		strcpy(path_copy, path_env);
		path_entry = strtok(path_copy, ":");
		while (path_entry != NULL)
		{
			char file_path[1024];

			snprintf(file_path, sizeof(file_path), "%s/%s", path_entry, filename);
			if (access(file_path, X_OK) == 0)
			{
				free(path_copy);
				path_return = malloc(sizeof(char) * (strlen(file_path) + 1));
				strcpy(path_return, file_path);
				return (path_return);
			}
			path_entry = strtok(NULL, ":");
		}
		free(path_copy);
	}
	return (NULL);
}


/**
 * execute_command - executes the file provided using fork and execve method
 *
 * @file_path: the path of the executable file
 * @argv: array of arguments
 * @envp: the environment
 * @ch_st: the termination status
 *
 * Return: always 0. Unless error occured.
 *
*/
int execute_command(char *file_path, char *argv[], char *envp[], int *ch_st)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(file_path, argv, envp);
		return (1);
	}
	else
	{
		int termination = wait(ch_st);

		UNUSED(termination);
		free(file_path);
		return (0);
	}
}

/**
 * is_implemented - searches for @command in the list of built_in functions
 *
 * @command: the command to search
 *
 * Return: the number of the implemented function or -1 if not implemented.
*/
int is_implemented(char *command)
{
	int command_length, current_length, str_return, functions_count, shortest, i;
	char *functions_names[5];

	if (command == NULL)
		return (-1);

	functions_names[0] = "exit";
	functions_names[1] = "env";
	functions_names[2] = "setenv";
	functions_names[3] = "unsetenv";
	functions_names[4] = "cd";
	functions_count = 5;
	command_length = strlen(command);

	for (i = 0; i < functions_count; i++)
	{
		current_length = strlen(functions_names[i]);
		shortest = command_length < current_length ? command_length : current_length;
		str_return = strncmp(command, functions_names[i], shortest);
		if (str_return == 0)
			return (i);
	}
	return (-1);
}

/**
 * run_num - runs the requested built in function
 *
 * @fn_num: the number of the requested function
 * @argv: array of arguments
 * @buffer: the original buffer, in case it will be free'd.
 * @word_count: number of words.
 * @status: the status of the last function call.
 *
 * Return: always 0.
*/
int run_num(int fn_num, char **argv, char *buffer, int word_count, int status)
{
	char *file_path;

	switch (fn_num)
	{
		case -1:
			file_path = search_system(argv[0]);
			if (file_path != NULL)
				execute_command(file_path, argv, environ, &status);
			else
				return (-1);
			break;
		case 0:
			handle_exit(status, argv, buffer, word_count);
			break;
		case 1:
			print_env();
			break;
		case 2:
			if (setenv(argv[1], argv[2], 1) != 0)
			perror("setenv");
			break;
		case 3:
			if (unsetenv(argv[1]) != 0)
			perror("unsetenv");
			break;
		case 4:
			change_dir(argv);
			break;
		case 5:
			/* alias */
		default:
			return (-1);
	}
	return (0);
}
