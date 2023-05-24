#include "shell.h"

/**
* _copy_memory - Copies memory from source to destination
* @src: Pointer to the source memory
* @dest: Pointer to the destination memory
* @size: Number of bytes to copy
*/
static void _copy_memory(void *src, void *dest, unsigned int size)
{
unsigned int i;
char *csrc = src;
char *cdest = dest;

for (i = 0; i < size; i++)
cdest[i] = csrc[i];
}

/**
* _realloc - Reallocates memory block
* @ptr: Pointer to the memory block to reallocate
* @old_size: Old size of the memory block
* @new_size: New size of the memory block
* Return: Pointer to the reallocated memory block
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *new_ptr;

/* If new_size is 0 and ptr is not NULL, free memory */
if (new_size == 0 && ptr != NULL)
{
free(ptr);
return (NULL);
}

/* If new_size is the same as old_size, return ptr */
if (new_size == old_size)
return (ptr);

/* If ptr is NULL, malloc new size and return it */
if (ptr == NULL)
{
new_ptr = malloc(new_size);
if (new_ptr == NULL)
return (NULL);
return (new_ptr);
}

/* Malloc new size and check for error */
new_ptr = malloc(new_size);
if (new_ptr == NULL)
return (NULL);

/* Copy memory from old pointer to new pointer */
_copy_memory(ptr, new_ptr, MIN(old_size, new_size));

/* Free old ptr */
free(ptr);

/* Return new ptr */
return (new_ptr);
}
