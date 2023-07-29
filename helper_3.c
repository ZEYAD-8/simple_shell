#include "main.h"

/**
 * change_dir - Change the current working directory.
 * @argv: The array of command-line arguments.
 */
void change_dir(char **argv)
{
	char *home_dir = getenv("HOME");
	char *prev_dir = getenv("OLDPWD");
	char new_dir[4096];

	if (argv[1] == NULL)
	{
		if (home_dir != NULL)
		{
			if (chdir(home_dir) != 0)
				perror("cd-line-70");
		}
		else
			fprintf(stderr, "cd: HOME environment variable not set.\n");
	}
	else if (strcmp(argv[1], "-") == 0)
	{
		if (prev_dir != NULL)
		{
			if (chdir(prev_dir) != 0)
				perror("cd-line-79");
		}
		else
			fprintf(stderr, "cd: Previous directory not set.\n");
	}
	else
	{
		/* Change to the directory specified in argv[1] */
		if (chdir(argv[1]) != 0)
		{
			fprintf(stderr, "cd: %s: No such file or directory.\n", argv[1]);
			perror("cd-line-88");
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
