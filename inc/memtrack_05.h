#ifndef MEMTRACK_05_H
#define MEMTRACK_05_H
#include <stdio.h>
#include <stdlib.h>
#include<stddef.h>


#define malloc(size) my_malloc(__FILE__,__func__,__LINE__,size)
#define free(ptr) my_free(__FILE__,__func__,__LINE__,ptr)
#define realloc(ptr, size_type) my_realloc(__FILE__,__func__,__LINE__,ptr,size_type)
#define calloc(size,size_type) my_calloc(__FILE__,__func__,__LINE__,size,size_type)

/* Prototypes des fonctions de memtrack_05.c */
void *my_malloc(const char* file,const char* func, int line,size_t size_type);
void my_free(const char* file,const char* func, int line,void* ptr);
void *my_calloc(const char* file,const char* func, int line,int size, size_t size_type);
void *my_realloc(const char* file,const char* func, int line,void* ptr, size_t size_type);
#endif //MEMTRACK_05_H

