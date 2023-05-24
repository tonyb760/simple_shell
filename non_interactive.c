#include "shell.h"

/**
* c_ignore - custom ignores spaces and newlines
* (e.g. echo "ls\n ls" | ./a.out)
* @str: envrionmental variables
* Return: new string
*/
char *c_ignore(char *str)
{
while (*str == ' ' || *str == '\n')
{
str++;
}
return (str);
}

/**
* non_interactive - handles when user pipes commands into shell via pipeline
* (e.g. echo "ls/nls -al/n" | ./a.out)
* @env: envrionmental variables
*/
void non_interactive(list_t *env)
{
size_t i = 0, n = 0;
int command_line_no = 0, exit_stat = 0;
char *command = NULL, *n_command = NULL, **n_line, **token;

i = get_line(&command);
if (i == 0)
{
free(command);
exit(0);
}

command = c_ignore(command);

n_line = _str_tok(command, "\n");

for (n = 0; n_line[n] != NULL; n++)
{
command_line_no++;

n_line[n] = c_ignore(n_line[n]);

if (built_in(n_line[n], env, command_line_no, n_line))
{
continue;
}

exit_stat = _execve(n_line[n], env, command_line_no);
}

free_double_ptr(n_line);

free_linked_list(env);

exit(exit_stat);
}
