#include "shell.h"

/**
* execute_command - Execute the command using execve
* @command: The command to execute
* @environment: Environmental variables
* @command_number: The nth user command (used in error message)
* Return: 0 on success, 127 if command not found or not executable
*/
int execute_command(char **command, list_t *environment, int command_number)
{
char *path;
int status = 0, is_absolute_path = 0;
pid_t pid;

if (access(command[0], F_OK) == 0)
{
path = command[0];
is_absolute_path = 1;
}
else
{
path = _which(command[0], environment);
}

if (access(path, X_OK) != 0)
{
not_found(command[0], command_number, environment);
free_double_ptr(command);
return (127);
}

pid = fork();
if (pid == 0)
{
if (execve(path, command, NULL) == -1)
{
not_found(command[0], command_number, environment);
c_exit(command, environment);
}
}
else
{
wait(&status);
free_double_ptr(command);
if (!is_absolute_path)
{
free(path);
}
}

return (0);
}

/**
* c_exit - Free memory and exit the shell
* @command: The user's typed command
* @environment: The linked list of environment variables
*/
void c_exit(char **command, list_t *environment)
{
free_double_ptr(command);
free_linked_list(environment);
_exit(0);
}

/**
* _execve - Execute the command user typed into the shell
* @command: The command user typed
* @environment: Environmental variables
* @command_number: The nth user command (used in error message)
* Return: 0 on success
*/
int _execve(char **command, list_t *environment, int command_number)
{
return (execute_command(command, environment, command_number));
}
