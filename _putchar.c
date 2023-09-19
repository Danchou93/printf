#include <unistd.h>
/**
 * _putchar - write character character to the stdout
 * @character: the character
 * Return: 1 on success and -1 if not
 */
int _putchar(char character)
{
	return (write(1, &character, 1));
}
