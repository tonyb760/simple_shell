#include "shell.h"

/**
 * count_tokens - returns number of tokens in a string based on delimiter
 * @str: string to count tokens from
 * @delim: delimiter character
 * Return: number of tokens
 */
int count_tokens(const char *str, char delim)
{
	int count = 0;
	int is_token = 0;

	while (*str != '\0')
	{
		if (*str == delim)
			is_token = 0;
		else if (is_token == 0)
		{
			is_token = 1;
			count++;
		}
		str++;
	}

	return (count);
}

/**
 * tokenize_string - tokenizes a string using a delimiter
 * @str: string to tokenize
 * @delim: delimiter string
 * Return: array of tokens
 */
char **tokenize_string(const char *str, const char *delim)
{
	int token_count = count_tokens(str, delim[0]);
	char **tokens = malloc((token_count + 1) * sizeof(char *));
	char *token;
	char *copy;
	char *save_ptr;
	int i = 0;

	if (tokens == NULL)
		return (NULL);

	copy = strdup(str);
	if (copy == NULL)
	{
		free(tokens);
		return (NULL);
	}

	token = strtok_r(copy, delim, &save_ptr);
	while (token != NULL)
	{
		tokens[i] = strdup(token);
		if (tokens[i] == NULL)
		{
			free(tokens);
			free(copy);
			return (NULL);
		}
		token = strtok_r(NULL, delim, &save_ptr);
		i++;
	}

	tokens[i] = NULL;
	free(copy);

	return (tokens);
}

