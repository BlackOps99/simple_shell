#include "shell.h"

/**
 * _putchar - Writes a character to stdout
 * @c: The character to be written
 * @status: the value that write status
 * Return: On success 1
 * On error, -1 is returned and errno is set appropriately
 */
int _putchar(int status, char c)
{
	return (write(status, &c, 1));
}

/**
 * writeLog - function that prints all types of output
 * @format: the format that will be worked with
 * @status: the value that write status
 * Return: length of format
 */
int writeLog(int status, const char *format, ...)
{
	int len_of_str = 0;
	const char *setn;
	const char *current;

	va_list ap;

	va_start(ap, format);

	if (format == NULL || (format[0] == '%' && format[1] == '\0'))
	{
		va_end(ap);
		return (-1);
	}

	current = format;

	while (*current != '\0')
	{
		if (*current == '%' && isCharInArray(*(current + 1)) != 0)
		{
			setn = current + 1;
			len_of_str += handle_log(setn, status, ap);
			current = current + 2;
		}
		else
		{
			_putchar(status, *current);
			len_of_str++;
			current++;
		}
	}

	va_end(ap);
	return (len_of_str);
}

/**
 * isCharInArray - function that check if correct format
 * @searchValue: type char
 * Return: 1 if found else 0
 */
int isCharInArray(char searchValue)
{
	int i = 0;

	char array[4] = {
	    'c',
	    's',
	    'd',
	    'i'
	};

	for (i = 0; i < 4; i++)
	{
		if (array[i] == searchValue)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * handle_log - function that handles the type format
 * @to_type: type char pointer
 * @status: the value that write status
 * @value: type va_list that contains the value
 * Return: The number of characters printed.
 */
int handle_log(const char *to_type, int status, va_list value)
{
	switch (to_type[0])
	{
	case 'c':
		return (toChar(status, value));
	case 's':
		return (toString(status, value));
	case 'i':
	case 'd':
		return (toInt(status, value));
	default:
		return (0);
	}
}
