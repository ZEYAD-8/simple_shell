#include "main.h"

/**
 * get_argv - takes a line string and tokenizes it to smaller ones
 *
 * @line: the line string taken from the user.
 * @count: should be updated to the number of words in the line.
 *
 * Return: an array of the strings without spaces
*/
char **get_argv(const char *line, int *count)
{
	int words_count;
	char **argv, *word;
	int i;
	int length;
	char *line_dup;
	char *line_3rd;

	argv = NULL;
	words_count = *count;
	length = strlen(line);
	line_dup = malloc(sizeof(char) * (length + 1));
	line_3rd = malloc(sizeof(char) * (length + 1));
	strcpy(line_dup, line);
	strcpy(line_3rd, line);
	word = strtok(line_dup, " \n");
	for (words_count = 0; word != NULL; words_count++)
		word = strtok(NULL, " \n");

	argv = malloc(sizeof(char *) * (words_count + 1));
	word = strtok(line_3rd, " \n");
	for (i = 0; word != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * (strlen(word) + 1));
		strcpy(argv[i], word);
		word = strtok(NULL, " \n");
	}
	argv[i] = NULL;

	*count = words_count;
	free(line_3rd);
	free(line_dup);

	return (argv);
}

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
	if (access(filename, F_OK) == 0)
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
			if (access(file_path, F_OK) == 0)
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
 *
 * Return: always 0. Unless error occured.
 *
*/
int execute_command(char *file_path, char *argv[], char *envp[], int *child_status)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		execve(file_path, argv, envp);
		return (1);
	}
	else
	{
		int termination = wait(child_status);

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
	char *functions_names[2];

	if (command == NULL)
		return (-1);

	functions_names[0] = "exit";
	functions_names[1] = "env";
	functions_count = 2;
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
