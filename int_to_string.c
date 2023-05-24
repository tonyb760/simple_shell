#include "shell.h"

/**
* numlen - counts number of digits in an integer
* @n: number
* Return: number of digits
*/
int numlen(int n)
{
int count = 0;
while (n != 0)
{
n /= 10;
count++;
}
return (count);
}

/**
* int_to_string - converts an integer to a string
* @number: integer
* Return: the integer as a string, NULL if failed
*/
char *int_to_string(int number)
{
int digits = number;
int is_negative = 0;
int len, i, x;
char *res;

if (number < 0)
{
is_negative = 1;
digits = -digits;
}

len = numlen(digits);
res = malloc(sizeof(char) * (len + 2 + is_negative));
if (res == NULL)
{
return (NULL);
}

i = 0;
if (is_negative)
{
res[i] = '-';
i++;
}

for (x = len - 1; x >= 0; x--)
{
res[i] = (digits / power_of_10(x)) + '0';
i++;
digits %= power_of_10(x);
}

res[i] = '\0';
return (res);
}
