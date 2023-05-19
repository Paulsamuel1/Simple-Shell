#include "main.h"

/**
 * free_data - free the data structure
 * @datash: data structure
 * Return: no return
 */
void free_data(data_shell *datash)
{
	unsigned int j;

	for (j = 0; datash->_environ[j]; j++)
	{
		free(datash->_environ[j]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_data - Initialize the data structure
 * @datash: data structure
 * @av: argument vector
 * Return: No return
 */
void set_data(data_shell *datash, char **av)
{
	unsigned int j;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (j = 0; environ[j]; j++)
		;

	datash->_environ = malloc(sizeof(char *) * (j + 1));

	for (j = 0; environ[j]; j++)
	{
		datash->_environ[j] = _strdup(environ[j]);
	}

	datash->_environ[j] = NULL;
	datash->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 * Return: 0 on (success).
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&datash, av);
	shell_loop(&datash);
	free_data(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
