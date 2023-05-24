#include "shell.h"

/**
* _strdup - returns a pointer to a newly allocated space in memory,
* which contains a copy of the string given as a parameter
* @str: string to duplicate
* Return: pointer to duplicated string in allocated memory
*/
char *_strdup(char *str)
{
char *duplicate_str;
size_t len = strlen(str);

if (str == NULL)
{
return (NULL);
}

duplicate_str = malloc(len + 1);
if (duplicate_str == NULL)
{
return (NULL);
}

memcpy(duplicate_str, str, len + 1);

return (duplicate_str);
}
