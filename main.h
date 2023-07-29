#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) (void)(x)

extern char **environ;

int display_prompt(void);
char **get_argv(const char *line, int *count);
int is_implemented(char *command);
char *search_system(const char *filename);
int execute_command(char *pathname, char *argv[], char *envp[], int *child_status);
int run_function(int function_number, char **argv);
int print_env(void);
void custom_free(char **argv, int words_count);
void handle_exit(int status, char **argv, char *buffer, int words_count);
int check_buffer(char **buffer, int *chars_count);
char *substring(char *str, int *char_count, char *character);
void change_dir(char **argv);
#endif
