#ifndef MTRACK_04_H
#define MTRACK_04_H

#include <stdio.h>
#include <stdlib.h>

#define malloc(size) my_malloc(size)
#define free(ptr) my_free(ptr)
#define calloc(size,size_type) my_calloc(size,size_type);
#define realloc(ptr, size_type) my_realloc(ptr,size_type);

/* Prototypes des fonctions de mtrack_04.c */
void *my_malloc(size_t size_type);
void my_free(void* ptr);
void *my_calloc(int size, size_t size_type);
void *my_realloc(void* ptr, size_t size_type);
#endif // MTRACK_04_H

