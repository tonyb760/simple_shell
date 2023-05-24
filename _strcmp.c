#include "shell.h"

/**
* _strcmp - compare two strings
* @s1: string 1
* @s2: string 2
* Return: int that tells num spaces in between, 0 if exactly the same string
*/

int _strcmp(char *s1, char *s2)
{
int i = 0;
int diff = 0;

while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
{
i++;
}

if (s1[i] != '\0' || s2[i] != '\0')
{
diff = s1[i] - s2[i];
}

return (diff);
}
