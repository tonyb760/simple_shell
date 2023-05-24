#include "shell.h"

/**
* t_strlen - returns token's string length for mallocing
* @str: a token
* @pos: index position in user's command typed into shell
* @delm: delimiter (e.g. " ");
* Return: token length
*/
int t_strlen(char *str, int pos, char delm)
{
int len = 0;

while ((str[pos] != delm) && (str[pos] != '\0'))
{
pos++;
len++;
}
return (len);
}

/**
* t_size - returns number of delimiters ignoring continuous delimiters
* @str: user's command typed into shell
* @delm: delimiter (e.g. " ");
* Return: number of delimiters so that (num token = delimiters + 1)
*/
int t_size(char *str, char delm)
{
int i = 0, num_delm = 0;

while (str[i] != '\0')
{
if ((str[i] == delm) && (str[i + 1] != delm))
{
/* handle continuous delimiters */
num_delm++;
}
i++;
}
return (num_delm);
}

/**
* ignore_delm - returns a version of string without preceding delimiters
* @str: string
* @delm: delimiter (e.g. " ")
* Return: new string (e.g. "    ls -l" --> "ls -l")
*/
char *ignore_delm(char *str, char delm)
{
while (*str == delm)
{
str++;
}
return (str);
}

/**
* create_token - creates and returns a token from the input string
* @str: input string
* @si: starting index of the token in the string
* @len: length of the token
* Return: newly created token
*/
char *create_token(char *str, int si, int len)
{
char *token = malloc(sizeof(char) * (len + 1));
if (token == NULL)
{
return (NULL);
}
int i = 0;
while ((str[si] != '\0') && (i < len))
{
token[i] = str[si];
i++;
si++;
}
token[i] = '\0'; /* null terminate at the end */
return (token);
}

/**
* free_tokens - frees the memory allocated for an array of tokens
* @tokens: array of tokens
*/
void free_tokens(char **tokens)
{
if (tokens == NULL)
{
return;
}
int i = 0;
while (tokens[i] != NULL)
{
free(tokens[i]);
i++;
}
free(tokens);
}

/**
* _str_tok - tokenizes a string and returns an array of tokens
* @str: user's command typed into shell
* @delm: delimiter (e.g. " ");
* Return: an array of tokens (e.g. {"ls", "-l", "/tmp"}
*/
char **_str_tok(char *str, char *delm)
{
int buffsize = 0, p = 0, si = 0, se = 0, t = 0;
char **toks = NULL, d_ch;

d_ch = delm[0];
str = ignore_delm(str, d_ch);
buffsize = t_size(str, d_ch);
toks = malloc(sizeof(char *) * (buffsize + 2));
if (toks == NULL)
{
return (NULL);
}
while (str[se] != '\0')
{
se++;
}
while (si < se)
{
if (str[si] != d_ch)
{
int len = t_strlen(str, si, d_ch);
toks[p] = create_token(str, si, len);
if (toks[p] == NULL)
{
free_tokens(toks);
return (NULL);
}
t++;
}
if (si < se && (str[si + 1] != d_ch && str[si + 1] != '\0'))
{
p++;
}
si++;
}
p++;
toks[p] = NULL;
return (toks);
}
