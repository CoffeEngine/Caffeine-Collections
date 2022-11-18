#ifndef CAFFEINE_STACK_H
#define CAFFEINE_STACK_H

#include "caffeine_vector.h"

typedef cff_vector cff_stack;

void cff_stack_create(cff_stack* stack, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);
void cff_stack_resize(cff_stack* stack, uint64_t lenght, AllocatorInterface* allocator);
void cff_stack_push(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator);
void cff_stack_reverse(cff_stack* stack);
void cff_stack_free(cff_stack* stack, AllocatorInterface* allocator);
void cff_stack_clear(cff_stack* stack);
void cff_stack_copy(cff_stack* stack, cff_stack* to, uint64_t start, uint64_t count, AllocatorInterface* allocator);
void cff_stack_clone(cff_stack* stack, cff_stack* to, AllocatorInterface* allocator);
uint8_t cff_stack_pop(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator);
uint8_t cff_stack_top(cff_stack* stack, uintptr_t data_ptr);
 
#endif