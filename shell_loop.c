#include "main.h"

/**
 * without_comment - Deletes comments from the input
 * @in: Input string
 * Return: Input without comments
 */
char *without_comment(char *in)
{
	int j, up_to;

	up_to = 0;
	for (j = 0; in[j]; j++)
	{
		if (in[j] == '#')
		{
			if (j == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[j - 1] == ' ' || in[j - 1] == '\t' || in[j - 1] == ';')
				up_to = j;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, j, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loop - Loop of shells
 * @datash: data relevant (av, input, args)
 * Return: no return.
 */
void shell_loop(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_var(input, datash);
			loop = split_commands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
