#include "main.h"

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

/**
 * run_function - runs the requested built in function
 *
 * @function_number: the number of the requested function
 * @argv: array of arguments
 *
 * Return: always 0.
*/
int run_function(int function_number, char **argv)
{
	switch (function_number)
	{
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
			/* cd */
		case 5:
			/* alias */
		default:
			printf("%s: No such file or directory.\n", argv[0]);
	}
	return (0);
}
