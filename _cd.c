#include "shell.h"

/**
 * c_strcat - concatenate two strings ignoring the first character ("~" in cd)
 * @dest: string to be appended to
 * @src: string to append
 * Return: concatenated string
 */
char *c_strcat(char *dest, const char *src)
{
	int len = strlen(dest);
	int len2 = strlen(src);
	int total_len = len + len2 + 1;
	char *result = malloc(total_len);

	if (result == NULL)
		return (NULL);

	strncpy(result, dest, len);
	strncpy(result + len, src + 1, len2 - 1);
	result[total_len - 1] = '\0';

	free(dest);
	return (result);
}

/**
 * c_setenv - custom _setenv by concatenating string first before setting
 * @env: environmental variable linked list
 * @name: environmental variable name (e.g. "OLDPWD")
 * @dir: directory path (e.g. "/home/vagrant/directory1")
 * Return: 0 on success (e.g. "OLDPWD=/home/vagrant/directory1")
 */
int c_setenv(list_t **env, const char *name, const char *dir)
{
	char *cat;
	list_t *holder;

	cat = malloc(strlen(name) + strlen(dir) + 2);
	if (cat == NULL)
		return (-1);

	sprintf(cat, "%s=%s", name, dir);
	holder = *env;
	while (holder != NULL)
	{
		if (strncmp(holder->var, name, strlen(name)) == 0)
		{
			free(holder->var);
			holder->var = cat;
			return (0);
		}
		holder = holder->next;
	}

	add_end_node(env, cat);
	return (0);
}

/**
 * cd_only - change directory to home
 * @env: bring in environmental linked list to update PATH and OLDPWD
 * @current: bring in current working directory
 */
void cd_only(list_t *env, char *current)
{
	char *home = get_env("HOME", env);

	if (home != NULL && access(home, F_OK) == 0)
		chdir(home);

	free(current);
	current = getcwd(NULL, 0);
	c_setenv(&env, "PWD", current);
	free(current);
	free(home);
}

/**
 * cd_execute - executes the cd
 * @env: bring in environmental linked list to update PATH and OLDPWD
 * @current: bring in current working directory
 * @dir: bring in directory path to change to
 * @str: bring in the 1st argument to write out error
 * @num: bring in the line number to write out error
 * Return: 0 if success, 2 if fail
 */
int cd_execute(list_t *env, char *current, const char *dir, const char *str, int num)
{
	if (access(dir, F_OK) == 0)
	{
		c_setenv(&env, "OLDPWD", current);
		free(current);
		chdir(dir);
		current = getcwd(NULL, 0);
		c_setenv(&env, "PWD", current);
		free(current);
		return (0);
	}
	else
	{
		cant_cd_to((char *)str, num, env);
		free(current);
		return (2);
	}
}

/**
 * _cd - change directory
 * @str: user's typed in command
 * @env: environmental linked list to retrieve HOME and OLDPWD paths
 * @num: nth user command, to be used at error message
 * Return: 0 if success, 2 if failed
 */
int _cd(char **str, list_t *env, int num)
{
	char *current = getcwd(NULL, 0);
	char *dir = NULL;
	int exit_stat = 0;

	if (str[1] != NULL)
	{
		if (str[1][0] == '~')
			dir = c_strcat(get_env("HOME", env), str[1]);
		else if (str[1][0] == '-' && str[1][1] == '\0')
			dir = get_env("OLDPWD", env);
		else if (str[1][0] != '/')
			dir = c_strcat(c_strcat(current, "/"), str[1]);
		else
			dir = strdup(str[1]);

		exit_stat = cd_execute(env, current, dir, str[1], num);
		free(dir);
	}
	else
		cd_only(env, current);

	free_double_ptr(str);
	return (exit_stat);
}

