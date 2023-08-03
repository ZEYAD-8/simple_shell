#include "main.h"

/**
 * display_prompt - prints a $ sign function pn the screen
 *
 * Return: 0 on succes. 1 on failure.
*/
int display_prompt(void)
{
	int flush_return, print_return;

	print_return = printf("$ ");
	flush_return = fflush(stdout);
	if (flush_return == 0 && print_return == 2)
		return (0);
	else
		return (1);
}

/**
 * print_env - prints the environment
 *
 * Return: always 0.
*/
int print_env(void)
{
	unsigned int i;

	i = 0;
	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}

/**
 * change_dir - Change the current working directory.
 * @argv: The array of command-line arguments.
 */
void change_dir(char **argv)
{
	char *home_dir = getenv("HOME");
	char *prev_dir = getenv("OLDPWD");
	char *current_dir = getenv("PWD");
	char new_dir[4096];

	if (argv[1] == NULL)
	{
		if (home_dir != NULL)
		{
			if (chdir(home_dir) != 0)
				perror("cd - 53");
		}

	}
	else if (strcmp(argv[1], "-") == 0)
	{
		if (prev_dir != NULL)
		{
			if (chdir(prev_dir) != 0)
				perror("cd - 63");
			printf("%s\n", prev_dir);
		}
		else
			printf("%s\n", current_dir);
	}
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("cd - 74");
		}
	}

	if (getcwd(new_dir, sizeof(new_dir)) != NULL)
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", new_dir, 1);
	}
	else
		perror("getcwd");
}

/**
 * handle_exit - frees the memory and exit with status, if any was provided.
 *
 * @status: the status to exit with
 * @argv: array of arguments
 * @buffer: the buffer to free
 * @words_count: number of words in the buffer
 *
 * Return: nothing.
*/
void handle_exit(int status, char **argv, char *buffer, int words_count)
{
	if (words_count > 0)
	{
		if (argv[1] != NULL)
			status = atoi(argv[1]);
		custom_free(argv, words_count);
	}
	if (buffer != NULL)
		free(buffer);
	if (status == 512)
		exit((status / 256));
	exit(status);
}

/**
 * custom_free - frees each string, then the array.
 *
 * @argv: the array of strings
 * @words_count: number of strings in the array
 *
 * Return: nothing.
*/
void custom_free(char **argv, int words_count)
{
	int i;

	if (argv == NULL)
		return;
	i = 0;
	while (i <= words_count)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
