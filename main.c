#include "main.h"

/**
 * main - A shell-like function
 *
 * @ac: the number of arguments.
 * @av: array of the aruments provided, if any.
 * *
 * if (check_buffer(buffer, buffer_size, chars_count) == 1)
 * if (check_buffer(&buffer, &chars_count) == 1)
 * if (chars_count == 1 && buffer[0] == '\n')
 * Return: always 0.
*/
int main(int ac, char **av)
{
	char **argv, *buffer;
	int chars_count, words_count, function_num, status = 0;
	int run_return, check_return;
	size_t buffer_size = 0;

	(void) ac;
	while (1)
	{
		buffer = NULL;
		if (isatty(STDIN_FILENO) != 0)
			display_prompt();
		words_count = 0;
		chars_count = getline(&buffer, &buffer_size, stdin);
		if (feof(stdin))
			handle_exit(status, argv, buffer, words_count);
		check_return = check_buffer(&buffer, &chars_count);
		if (check_return == 1)
		{
			if (buffer != NULL)
				free(buffer);
			continue;
		}
		argv = get_argv(buffer, &words_count);
		function_num = is_implemented(argv[0]);
		run_return = run_num(function_num, argv, buffer, words_count, status);
		if (run_return != 0)
			printf("%s: No such file or directory.\n", av[0]);
		if (words_count != 0)
			custom_free(argv, words_count);
		free(buffer);
	}
}
