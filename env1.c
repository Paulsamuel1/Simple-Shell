#include "main.h"

/**
 * cmp_env_name - Compares env variables names
 * with the name passed.
 * @nenv: Name of the environment variable
 * @name: Name passed
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int j;

	for (j = 0; nenv[j] != '='; j++)
	{
		if (nenv[j] != name[j])
		{
			return (0);
		}
	}

	return (j + 1);
}

/**
 * _getenv - get the environment variable
 * @name: Name of the environment variable
 * @_environ: environment variable
 * Return: Value of environment variable if is found.
 * In other case, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int j, mov;

	ptr_env = NULL;
	mov = 0;
	/* Compare all the environment variables */
	/* environ are declared in the header file */
	for (j = 0; _environ[j]; j++)
	{
		mov = cmp_env_name(_environ[j], name);
		if (mov)
		{
			ptr_env = _environ[j];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the evironment variables
 * @datash: data relevant.
 * Return: 1 on success.
 */
int _env(data_shell *datash)
{
	int j, e;

	for (j = 0; datash->_environ[j]; j++)
	{

		for (e = 0; datash->_environ[j][e]; e++)
			;

		write(STDOUT_FILENO, datash->_environ[j], e);
		write(STDOUT_FILENO, "\n", 1);
	}
	datash->status = 0;

	return (1);
}
