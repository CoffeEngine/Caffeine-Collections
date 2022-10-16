#ifndef CAFFEINE_QUEUE_H
#define CAFFEINE_QUEUE_H

#include "caffeine_vector.h"

typedef cff_vector cff_queue;

void caffeine_queue_create(cff_queue* queue, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);
void caffeine_queue_resize(cff_queue* queue, uint64_t lenght, AllocatorInterface* allocator);
void caffeine_queue_enqueue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator);
void caffeine_queue_reverse(cff_queue* queue);
void caffeine_queue_free(cff_queue* queue, AllocatorInterface* allocator);
void caffeine_queue_clear(cff_queue* queue);
void caffeine_queue_copy(cff_queue* queue, cff_queue* to, uint64_t start, uint64_t end, AllocatorInterface* allocator);
void caffeine_queue_clone(cff_queue* queue, cff_queue* to, AllocatorInterface* allocator);
uint8_t caffeine_queue_dequeue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator);


#endif