#ifndef CAFFEINE_STACK_H
#define CAFFEINE_STACK_H

#include "caffeine_vector.h"

typedef cff_vector cff_stack;

cff_err_e caffeine_stack_create(cff_stack* stack, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_stack_resize(cff_stack* stack, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_stack_push(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator);
cff_err_e caffeine_stack_reverse(cff_stack* stack);
void caffeine_stack_free(cff_stack* stack, AllocatorInterface* allocator);
void caffeine_stack_clear(cff_stack* stack);
cff_err_e caffeine_stack_copy(cff_stack* stack, cff_stack* to, uint64_t start, uint64_t end, AllocatorInterface* allocator);
cff_err_e caffeine_stack_clone(cff_stack* stack, cff_stack* to, AllocatorInterface* allocator);
cff_err_e caffeine_stack_pop(cff_stack* stack, uintptr_t data_ptr, uint8_t* is_empty, AllocatorInterface* allocator);
void caffeine_stack_top(cff_stack* stack, uintptr_t data_ptr, uint8_t* is_empty);
 
#endif