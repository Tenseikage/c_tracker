#ifndef MTRACK_03_H
#define MTRACK_03_H

#include <stdio.h>
#include <stdlib.h>

/* Prototypes des fonctions de mtrack_03.c */
void *my_malloc(size_t size_type);
void my_free(void* ptr);
void *my_calloc(int size, size_t size_type);
void *my_realloc(void* ptr, size_t size_type);

#endif // MTRACK_03_H

