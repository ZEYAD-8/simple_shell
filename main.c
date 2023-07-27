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
	char **argv, **env, *file_path, *buffer;
	int chars_count, words_count, function_num, status, check_return;
	size_t buffer_size = 0;
	(void)ac;

	while (1)
	{
		env = environ;
		buffer = NULL;
		display_prompt();
		words_count = status = 0;
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
		if (function_num == -1)
		{
			file_path = search_system(argv[0]);
			if (file_path != NULL)
				execute_command(file_path, argv, env);
			else
				printf("%s: No such file or directory.\n", av[0]);
		}
		else if (function_num == 0)
			handle_exit(status, argv, buffer, words_count);
		else
			run_function(function_num, argv);
		if (words_count != 0)
			custom_free(argv, words_count);
		free(buffer);
	}
}
