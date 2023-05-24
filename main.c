#include "shell.h"

/**
* main - creates a simple shell
* @ac: argument count
* @av: argument vectors
* @env: environmental variables
* Return: 0 on success
*/
int main(int ac, char **av, char **env)
{
(void)ac;
(void)av;

prompt(env);

while (1)
{

char *command = read_command();

if (command == NULL)
{
break;
}

execute_command(command, env);

free(command);
}

return (0);
}
