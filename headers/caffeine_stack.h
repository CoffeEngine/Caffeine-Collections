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
 * @param stack 
 * @param data_size 
 * @param lenght 
 * @param allocator 
 */
void cff_stack_create(cff_stack* stack, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 * @param lenght 
 * @param allocator 
 */
void cff_stack_resize(cff_stack* stack, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 * @param data_ptr 
 * @param allocator 
 */
void cff_stack_push(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 */
void cff_stack_reverse(cff_stack* stack);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 * @param allocator 
 */
void cff_stack_free(cff_stack* stack, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 */
void cff_stack_clear(cff_stack* stack);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 * @param to 
 * @param start 
 * @param count 
 * @param allocator 
 */
void cff_stack_copy(cff_stack* stack, cff_stack* to, uint64_t start, uint64_t count, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 * @param to 
 * @param allocator 
 */
void cff_stack_clone(cff_stack* stack, cff_stack* to, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 * @param data_ptr 
 * @param allocator 
 * @return uint8_t 
 */
uint8_t cff_stack_pop(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Stack
 * @brief 
 * 
 * @param stack 
 * @param data_ptr 
 * @return uint8_t 
 */
uint8_t cff_stack_top(cff_stack* stack, uintptr_t data_ptr);
 
#endif