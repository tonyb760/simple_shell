#include "shell.h"

/**
* env_linked_list - creates a linked list from environmental variables
* @env: environmental variables
* Return: linked list
*/
list_t *env_linked_list(char **env)
{
list_t *head = NULL;
while (*env != NULL)
{
list_t *new_node = malloc(sizeof(list_t));
new_node->var = *env;
new_node->next = head;
head = new_node;
env++;
}
return (head);
}

/**
* _env - prints environmental variables
* @str: user's command into shell (i.e. "env")
* @env: environmental variables
* Return: 0 on success
*/
int _env(char **str, list_t *env)
{
free_double_ptr(str); /* frees user input */
print_list(env); /* prints env */
return (0);
}
