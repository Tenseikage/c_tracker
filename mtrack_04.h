#ifndef MTRACK_04_H
#define MTRACK_04_H

#include <stdio.h>
#include <stdlib.h>

#define malloc(size) my_malloc(size)
#define free(ptr) my_free(ptr)

/* Prototypes des fonctions de mtrack_04.c */
void *my_malloc(size_t size_type);
void my_free(void* ptr);

#endif // MTRACK_04_H

