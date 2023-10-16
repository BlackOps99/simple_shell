#include "shell.h"

/**
 * toChar - function that print char
 * @value: the value that will be work with it
 * @status: the value that write status
 * Return: length of char
 */
int toChar(int status, va_list value)
{
	int c = va_arg(value, int);

	_putchar(status, c);

	return (1);
}

/**
 * toString - function that print string
 * @value: the value that will be work with it
 * @status: the value that write status
 * Return: length of str
 */
int toString(int status, va_list value)
{
	int i, len = 0;

	char *str = va_arg(value, char *);

	if (str == NULL)
	{
		str = "(null)";
		for (i = 0; str[i] != '\0'; i++)
		{
			_putchar(status, str[i]);

			len++;
		}

		return (len);
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		_putchar(status, str[i]);

		len++;
	}

	return (len);
}

/**
 * toInt - Print an integer as a string
 * @value: The integer
 * @status: the value that write status
 * Return: The number of digits printed
 */
int toInt(int status, va_list value)
{
	int len, powten, j, digit, res, count = 0, num;

	res = va_arg(value, int);

	if (res == 0)
	{
		_putchar(status, '0');
		return (1);
	}

	if (res < 0)
	{
		_putchar(status, '-');
		count++;
	}
	num = res;
	len = 0;
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	powten = 1;
	for (j = 1; j <= len - 1; j++)
		powten *= 10;
	for (j = 1; j <= len; j++)
	{
		digit = res / powten;
		if (res < 0)
			_putchar(status, (digit * -1) + 48);
		else
			_putchar(status, digit + '0');
		count++;
		res -= digit * powten;
		powten /= 10;
	}
	return (count);
}
