#ifndef MEMTRACK_05_H
#define MEMTRACK_05_H
#include <stdio.h>
#include <stdlib.h>
#include<stddef.h>

#define malloc(size) my_malloc(__FILE__,__func__,__LINE__,size)
#define free(ptr) my_free(__FILE__,__func__,__LINE__,ptr)
#define realloc(ptr, size_type) my_realloc(__FILE__,__func__,__LINE__,ptr,size_type)
#define calloc(size,size_type) my_calloc(__FILE__,__func__,__LINE__,size,size_type)
/**
 * @author Christophe TARATIBU
 */

/**
 * @brief Adapated malloc function used for tracking
 * 
 * This clone of malloc, allocates the memory with a specified size.
 * After this, a cell is created and added in a linked list. (with data of cell)
 * The statistics of allocated memory is displayed at the end of tracer with number of executed malloc. 
 * 
 * @param size : size of the allocated memory
 * 
 */
void *my_malloc(const char* file,const char* func, int line,size_t size_type);


/**
 * @brief Adapated free function used for tracking
 * 
 * This clone of free, frees the memory with a specified pointer.
 * After this, the cell already created is modified in the linked list. 
 * The statistics of freed memory is displayed at the end of tracer with number of executed free. 
 * 
 * @param ptr : declared pointer
 * 
 */
void my_free(const char* file,const char* func, int line,void* ptr);

/**
 * @brief Adapated calloc function used for tracking
 * 
 * This clone of calloc, allocates the memory with a specified size and type size.
 * After this, a cell is created and added in a linked list. (with data of cell)
 * The statistics of allocated memory is displayed at the end of tracer with number of executed calloc. 
 * 
 * @param size:  size of allocated memory
 * @param size_type size of the type 
 */
void *my_calloc(const char* file,const char* func, int line,int size, size_t size_type);

/**
 * @brief Adapated realloc function used for tracking
 * 
 * This clone of realloc, reallocates the memory with a specified pointer and type size.
 * After this,the cell already created is modified in the linked list with new memory data
 * The statistics of allocated memory is displayed at the end of tracer with number of executed realloc. 
 * 
 * @param ptr:  declared pointer
 * @param size_type size of the type 
 */
void *my_realloc(const char* file,const char* func, int line,void* ptr, size_t size_type);
#endif //MEMTRACK_05_H

