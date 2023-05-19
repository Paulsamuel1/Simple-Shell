#include "main.h"

/**
 * copy_info - Copies info to create
 * A new env or alias
 * @name: Name (env or alias)
 * @value: Value (env or alias)
 * Return: New env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - Sets an environment variable
 * @name: Name of environment variable
 * @value: Value of environment variable
 * @datash: Data structure (environ)
 * Return: No return
 */
void set_env(char *name, char *value, data_shell *datash)
{
	int j;
	char *var_env, *name_env;

	for (j = 0; datash->_environ[j]; j++)
	{
		var_env = _strdup(datash->_environ[j]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(datash->_environ[j]);
			datash->_environ[j] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datash->_environ = _reallocdp(datash->_environ, j, sizeof(char *) * (j + 2));
	datash->_environ[j] = copy_info(name, value);
	datash->_environ[j + 1] = NULL;
}

/**
 * _setenv - Compares env variables names
 * With the name passed.
 * @datash: Data relevant (env name and env value)
 * Return: 1 on success.
 */
int _setenv(data_shell *datash)
{

	if (datash->args[1] == NULL || datash->args[2] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}

	set_env(datash->args[1], datash->args[2], datash);

	return (1);
}

/**
 * _unsetenv - Deletes a environment variable
 * @datash: Data relevant (env name)
 * Return: 1 on success.
 */
int _unsetenv(data_shell *datash)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int j, e, k;

	if (datash->args[1] == NULL)
	{
		get_error(datash, -1);
		return (1);
	}
	k = -1;
	for (j = 0; datash->_environ[j]; j++)
	{
		var_env = _strdup(datash->_environ[j]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, datash->args[1]) == 0)
		{
			k = j;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datash, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (j));
	for (j = e = 0; datash->_environ[j]; j++)
	{
		if (j != k)
		{
			realloc_environ[e] = datash->_environ[j];
			e++;
		}
	}
	realloc_environ[e] = NULL;
	free(datash->_environ[k]);
	free(datash->_environ);
	datash->_environ = realloc_environ;
	return (1);
}
