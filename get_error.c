#include "main.h"

/**
 * get_error - Call error according to the builtin, syntax or permission
 * @datash: Data structure that contains all the arguments
 * @eval: The error value
 * Return: Error
 */
int get_error(data_shell *datash, int eval)
{
	char *error;
	/*breaking out of the loops*/

	switch (eval)
	{
	case -1:
		error = error_env(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = error_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = error_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = error_get_cd(datash);
		break;
	}
	/*end of loops*/

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
