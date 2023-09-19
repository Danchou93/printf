#include "main.h"

/**
 * check_size - get the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @index: List of arguments to  print
 * Return: Precision
 */
int check_size(const char *format, int *index)
{
	int curr_i = *index + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*index = curr_i - 1;
	else
		*index = curr_i;

	return (size);
}
