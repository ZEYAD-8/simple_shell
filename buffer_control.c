#include "main.h"

/**
 * check_buffer - checks any wrong input in the buffer
 *
 * @buffer: the buffer to check.
 * @chars_count: number of characters in the buffer
 *
 * Return: 0 if nothing wrong with the buffer
 *         1 if all the buffer is spaces (after dealing with comments)
*/
int check_buffer(char **buffer, int *chars_count)
{
	int flag = 1;
	int j;

	if (*chars_count == 1 && (*buffer)[0] == '\n')
		return (1);

	*buffer = substring(*buffer, chars_count, " #");
	if (*buffer == NULL)
		return (1);

	for (j = 0; j < *chars_count && (*buffer)[j] != '\n'; j++)
		if ((*buffer)[j] != ' ')
			flag = 0;

	return (flag);
}

/**
 * substring - if it found a certain character, a truncated string is returned
 *
 * @str: string to check for.
 * @character: character to check for.
 * @char_count: number of characters in the string.
 *
 * Return: the string truncated if a character was found.
*/
char *substring(char *str, int *char_count, char *character)
{
	char *found, *result;
	size_t length;

	if (str[0] == character[1])
	{
		free(str);
		return (NULL);
	}

	found = NULL;
	found = strstr(str, character);
	if (found == NULL)
		return (str);

	length = found - str + 1;
	result = NULL;
	result = (char *)malloc(length + 2);

	strncpy(result, str, length);
	result[length] = '\n';
	result[length + 1] = '\0';

	*char_count = length;
	free(str);
	return (result);
}

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
