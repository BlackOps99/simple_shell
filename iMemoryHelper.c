#include "shell.h"
/**
 * _memset - method that fills memory with a constant byte
 * @__s: type char pointer
 * @__c: type char pointer
 * @__n: type char bytes of mem pointed by s with constant byte b
 * Return: always s
 */
void *_memset(void *__s, int __c, size_t __n)
{
	return (memset(__s, __c, __n));
}
