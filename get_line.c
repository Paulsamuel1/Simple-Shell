#include "main.h"

/**
 * get_line - Read input from the stream
 * @lineptr: Buffer that stores inpt
 * @n: Size of lineptr
 * @stream: Stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	int j;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		j = read(STDIN_FILENO, &t, 1);
		if (j == -1 || (j == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (j == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(lineptr, n, buffer, input);
	retval = input;
	if (j != 0)
		input = 0;
	return (retval);
}
/**
 * bring_line - Assigns line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that called to line
 * @n: Size of line
 * @e: Size of buffer
 */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t e)
{

	if (*lineptr == NULL)
	{
		if  (e > BUFSIZE)
			*n = e;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < e)
	{
		if (e > BUFSIZE)
			*n = e;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
