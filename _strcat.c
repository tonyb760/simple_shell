#include "shell.h"

/**
* _strcat - concatenate two strings
* @dest: string to be appended to
* @src: string to append
* Return: concatenated string
*/
char *_strcat(char *dest, char *src)
{
int len = strlen(dest);
int len2 = strlen(src);
int total_len = len + len2 + 1;

dest = realloc(dest, total_len);
if (dest == NULL)
{
return (NULL);
}

for (int i = 0; i < len2; i++)
{
dest[len + i] = src[i];
}
dest[len + len2] = '\0';

return (dest);
}
