#include "shell.h"

/**
 * _strchr - searches for the first occurrence of the character
 * @str: char pointer
 * @c: char pointer
 * Return: This returns a pointer
 * to the first occurrence of the character c in the string str,
 * or NULL if the character is not found
 */
char *_strchr(const char *str, int c)
{
	return (strchr(str, c));
}

/**
 * _strncpy - parameter name dest and src as pointer and int n
 * @dest: char pointer
 * @src: char pointer
 * @n: int var
 * Return: 0
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}

/**
 * _strcmp - parameter name dest and src as pointer
 * @s1: char pointer
 * @s2: char pointer
 * Return: 0
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strlen - parameter s as pointer char
 * @s: char pointer
 * Return: len of char
 */
int _strlen(char *s)
{
	int a = 0;

	for (; *s++;)
		a++;

	return (a);
}

/**
 * mkcopy - make a copy of the characters in the input buffer,
 * starting from s through es.
 * @s: char pointer
 * @es: char pointer
 * Return: characters else NULL
 */
char *mkcopy(char *s, char *es)
{
	int n = es - s;
	char *c = malloc(n + 1);

	assert(c);

	_strncpy(c, s, n);

	c[n] = 0;

	return (c);
}
