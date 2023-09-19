#include "main.h"

/**
 * check_width - gets the width for printing
 * @format: Formatted string in which to print the arguments
 * @index: List of arguments to print
 * @list: list of arguments
 * Return: width
 */
int check_width(const char *format, int *index, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *index + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*index = curr_i - 1;

	return (width);
}
