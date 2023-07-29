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
