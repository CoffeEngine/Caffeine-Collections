#ifndef CAFFEINE_VECTOR_H
#define CAFFEINE_VECTOR_H

#include<stdint.h>
#include "caffeine_core.h"

derive_container(caffeine_vector_s, uint64_t lenght; uint64_t count;);

typedef struct caffeine_vector_s cff_vector;

void caffeine_vector_create(cff_vector* vector, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);
void caffeine_vector_resize(cff_vector* vector, uint64_t lenght, AllocatorInterface* allocator);
void caffeine_vector_get(cff_vector* vector, uint64_t index, uintptr_t out);
void caffeine_vector_set(cff_vector* vector, uintptr_t data_ptr, uint64_t index);
void caffeine_vector_insert(cff_vector* vector, uintptr_t data_ptr, uint64_t index);
void caffeine_vector_remove(cff_vector* vector, uint64_t index, AllocatorInterface* allocator);
void caffeine_vector_copy(cff_vector* vector, cff_vector* to, uint64_t start, uint64_t end, AllocatorInterface* allocator);
void caffeine_vector_clone(cff_vector* vector, cff_vector* to, AllocatorInterface* allocator);
void caffeine_vector_fill(cff_vector* vector, uintptr_t data_ptr);
void caffeine_vector_join(cff_vector* vector, cff_vector* from, AllocatorInterface* allocator);
void caffeine_vector_reverse(cff_vector* vector);
void caffeine_vector_filter(cff_vector* vector, filter_fn func, cff_vector* filter_result, AllocatorInterface* allocator);
void caffeine_vector_map(cff_vector* vector, map_fn func, cff_vector* map_result, uint64_t result_data_size, AllocatorInterface* allocator);
void caffeine_vector_foreach(cff_vector* vector, foreach_fn func);
void caffeine_vector_sort(cff_vector* vector, comparer_fn predicate);
void caffeine_vector_free(cff_vector* vector, AllocatorInterface* allocator);
void caffeine_vector_clear(cff_vector* vector);
void caffeine_vector_push_back(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);
void caffeine_vector_push_front(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);
void caffeine_vector_pop_back(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);
void caffeine_vector_pop_front(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);

uint8_t caffeine_vector_equal(cff_vector* vector, cff_vector* other);
uint8_t caffeine_vector_find(cff_vector* vector, uintptr_t data_ptr, uint64_t* found);
uint8_t caffeine_vector_find_cmp(cff_vector* vector, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate);
uint64_t caffeine_vector_count(cff_vector* vector, uintptr_t data_ptr);
uint64_t caffeine_vector_count_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate);
uint8_t caffeine_vector_any(cff_vector* vector, uintptr_t data_ptr);
uint8_t caffeine_vector_any_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate);
uint8_t caffeine_vector_all(cff_vector* vector, uintptr_t data_ptr);
uint8_t caffeine_vector_all_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate);

#endif // !CAFFEINE_VECTOR_H
