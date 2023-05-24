#include "shell.h"

/**
* c_strdup - custom string duplication; excludes beginning bytes
* @str: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
* @cs: number of bytes to exclude (e.g. excludes "PATH=")
* Return: string (e.g. /bin:/bin/ls)
*/
char *c_strdup(char *str, int cs)
{
char *duplicate_str;
int i, len;

if (str == NULL)
{ /* Validate str input */
return (NULL);
}

/* Calculate len + null terminator to malloc */
for (len = 0; str[len] != '\0'; len++)
;
len++;

/* Allocate memory but exclude environmental variable title (PATH) */
duplicate_str = malloc(sizeof(char) * (len - cs));
if (duplicate_str == NULL)
{
return (NULL);
}

i = 0;
while (i < len - cs)
{
*(duplicate_str + i) = *(str + cs + i);
i++;
}
return (duplicate_str);
}

/**
* get_env - finds and returns a copy of the requested environmental variable
* @str: string to store it in
* @env: entire set of environmental variables
* Return: copy of requested environmental variable
*/
char *get_env(char *str, list_t *env)
{
int j = 0, cs = 0;

while (env != NULL)
{
j = 0;
while ((env->var)[j] == str[j])
{ /* Find desired env variable */
j++;
}
if (str[j] == '\0' && (env->var)[j] == '=')
{
break;
}
env = env->next;
}

while (str[cs] != '\0')
{ /* Find how many bytes in env variable title */
cs++;
}
cs++; /* Counts 1 more for = sign */
return (c_strdup(env->var, cs)); /* Make a copy of variable w/o title */
}
