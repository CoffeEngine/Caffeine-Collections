#ifndef CAFFEINE_QUEUE_H
#define CAFFEINE_QUEUE_H

#include "caffeine_vector.h"

typedef cff_vector cff_queue;

cff_err_e caffeine_queue_create(cff_queue* queue, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_queue_resize(cff_queue* queue, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_queue_enqueue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator);
cff_err_e caffeine_queue_reverse(cff_queue* queue);
void caffeine_queue_free(cff_queue* queue, AllocatorInterface* allocator);
void caffeine_queue_clear(cff_queue* queue);
cff_err_e caffeine_queue_copy(cff_queue* queue, cff_queue* to, uint64_t start, uint64_t end, AllocatorInterface* allocator);
cff_err_e caffeine_queue_clone(cff_queue* queue, cff_queue* to, AllocatorInterface* allocator);
cff_err_e caffeine_queue_dequeue(cff_queue* queue, uintptr_t data_ptr, uint8_t* is_empty, AllocatorInterface* allocator);


#endif