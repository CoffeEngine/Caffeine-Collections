#ifndef CAFFEINE_STACK_H
#define CAFFEINE_STACK_H

/**
 * @defgroup Stack
 * @file caffeine_stack.h
 * @author Ruan Azevedo
 * @brief Provides an API to use cff_vector as a stack
 * @version 0.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caffeine_vector.h"

/**
 * @ingroup Stack
 * @brief Redefines the cff_vector type to cff_queue.
 * 
 */
typedef cff_vector cff_stack;

/**
 * @ingroup Stack
 * @brief Initialize the Stack struct
 * 
 * @param stack [in] Pointer to a stack.
 * @param data_size [in] Element size in bytes
 * @param lenght [in] How many elements will be allocated initialy.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_stack_create(cff_stack* stack, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack [in] Pointer to a stack.
 * @param lenght [in] How many elements will be allocated.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_stack_resize(cff_stack* stack, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack [in] Pointer to a stack.
 * @param data_ptr [in] Pointer to the element to be stored.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_stack_push(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief Reverse the order of elements.
 * 
 * @param stack [in] Pointer to a stack.
 */
void cff_stack_reverse(cff_stack* stack);

/**
 * @ingroup Stack
 * @brief Deallocates the buffer owned by the stack.
 * 
 * @param stack [in] Pointer to a stack.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_stack_free(cff_stack* stack, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief Removes all elements from the stack.
 * 
 * @param stack [in] Pointer to a stack.
 */
void cff_stack_clear(cff_stack* stack);

/**
 * @ingroup Stack
 * @brief Copies a section of elements from one stack to other.
 * 
 * @param stack [in] Pointer to a stack.
 * @param to [out] Pointer to an stack that will receive the copy.
 * @param start [in] Index from where the copy process will start.
 * @param count [in] How many elements to copy from start.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_stack_copy(cff_stack* stack, cff_stack* to, uint64_t start, uint64_t count, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief Copies all elements from one stack to other.
 * 
 * @param stack [in] Pointer to a stack.
 * @param to [out] Pointer to an stack that will receive the copy.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_stack_clone(cff_stack* stack, cff_stack* to, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief Gets the last element of the stack removing it.
 * 
 * @param stack [in] Pointer to a stack.
 * @param data_ptr [out] Pointer to buffer that will receive the value.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return uint8_t 0 if the stack is empty else 1.
 */
uint8_t cff_stack_pop(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief Gets the last element of the stack without removing it.
 * 
 * @param stack [in] Pointer to a stack.
 * @param data_ptr [out] Pointer to buffer that will receive the value.
 * @return uint8_t 0 if the stack is empty else 1.
 */
uint8_t cff_stack_top(cff_stack* stack, uintptr_t data_ptr);
 
#endif