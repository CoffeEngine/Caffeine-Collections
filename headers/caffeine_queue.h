#ifndef CAFFEINE_QUEUE_H
#define CAFFEINE_QUEUE_H

/**
 * @defgroup Queue
 * @file caffeine_hashmap.h
 * @author Ruan Azevedo
 * @brief Provides an API to use cff_vector as a queue
 * @version 0.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caffeine_vector.h"

/**
 * @ingroup Queue
 * @typedef cff_vector cff_queue
 * @brief Redefines the cff_vector type to cff_queue.
 * 
 */
typedef cff_vector cff_queue;

/**
 * @ingroup Queue
 * @brief Initialize the queue struct
 * 
 * @param queue [in] Pointer to a sparse set.
 * @param data_size [in] Element size in bytes
 * @param lenght [in] How many elements will be allocated initialy.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_queue_create(cff_queue* queue, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Queue
 * @brief Reallocates the buffer owned by the queue.
 * 
 * @param queue [in] Pointer to a sparse set.
 * @param lenght [in] How many elements will be allocated.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_queue_resize(cff_queue* queue, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Queue
 * @brief Add an element at end of the queue
 * 
 * @param queue [in] Pointer to a sparse set.
 * @param data_ptr [in] Pointer to the element to be stored.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_queue_enqueue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Queue
 * @brief Reverse the order of elements.
 * 
 * @param queue [in] Pointer to a sparse set.
 */
void cff_queue_reverse(cff_queue* queue);

/**
 * @ingroup Queue
 * @brief Deallocates the buffer owned by the queue.
 * 
 * @param queue [in] Pointer to a sparse set.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_queue_free(cff_queue* queue, AllocatorInterface* allocator);

/**
 * @ingroup Queue
 * @brief Removes all elements from the queue.
 * 
 * @param queue [in] Pointer to a sparse set.
 */
void cff_queue_clear(cff_queue* queue);

/**
 * @ingroup Queue
 * @brief Copies a section of elements from one queue to other.
 * 
 * @param queue [in] Pointer to a sparse set.
 * @param to [out] Pointer to an queue that will receive the copy.
 * @param start [in] Index from where the copy process will start.
 * @param count [in] How many elements to copy from start.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_queue_copy(cff_queue* queue, cff_queue* to, uint64_t start, uint64_t count, AllocatorInterface* allocator);

/**
 * @ingroup Queue
 * @brief Copies all elements from one queue to other.
 * 
 * @param queue [in] Pointer to a sparse set.
 * @param to [out] Pointer to an queue that will receive the copy.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_queue_clone(cff_queue* queue, cff_queue* to, AllocatorInterface* allocator);

/**
 * @ingroup Queue
 * @brief Gets the first element of the queue removing it.
 * 
 * @param queue [in] Pointer to a sparse set.
 * @param data_ptr [out] Pointer to buffer that will receive the value.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return uint8_t 0 if the queue is empty else 1.
 */
uint8_t cff_queue_dequeue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator);

#endif