#include "main.h"

/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array
 * @flags:  on when flags exist
 * @width: Width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char character = va_arg(types, int);

	return (handle_write_char(character, buffer, flags, width, precision, size));
}
/* PRINT A STRING */
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array 
 * @flags:  on when flags exist
 * @width: width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, index;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (index = width - length; index > 0; index--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (index = width - length; index > 0; index--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/* PRINT PERCENT SIGN */
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array
 * @flags: on when flags exist
 * @width: width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* PRINT INT */
/**
 * print_int - Print int
 * @types: Lista of arguments
 * @buffer: Buffer array 
 * @flags:  on when flags exist
 * @width:  width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = BUFF_SIZE - 2;
	int is_negative = 0;
	long int number = va_arg(types, long int);
	unsigned long int num;

	number = convert_size_number(number, size);

	if (number == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)number;

	if (number < 0)
	{
		num = (unsigned long int)((-1) * number);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[index--] = (num % 10) + '0';
		num /= 10;
	}

	index++;

	return (write_number(is_negative, index, buffer, flags, width, precision, size));
}

/* PRINT BINARY */
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array
 * @flags: on when flags exist
 * @width: width
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int number, m, index, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	number = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = number / m;
	for (index = 1; index < 32; index++)
	{
		m /= 2;
		a[index] = (number / m) % 2;
	}
	for (index = 0, sum = 0, count = 0; index < 32; index++)
	{
		sum += a[index];
		if (sum || index == 31)
		{
			char z = '0' + a[index];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
