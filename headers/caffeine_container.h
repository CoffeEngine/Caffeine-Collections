#ifndef CAFFEINE_CONTAINER_H
#define CAFFEINE_CONTAINER_H

#include "caffeine_core.h"

typedef struct caffeine_containter_s cff_container;

void caffeine_container_desloc(cff_container* container, uint64_t from, int64_t steps, uint64_t lenght);
void caffeine_container_get(cff_container* container, uint64_t index, uintptr_t ptr_out, uint64_t lenght);
void caffeine_container_set(cff_container* container, uint64_t index, uintptr_t ptr_in, uint64_t lenght);
void caffeine_container_insert(cff_container* container, uint64_t index, uintptr_t ptr_in, uint64_t lenght);
uint8_t caffeine_container_remove(cff_container* container, uint64_t index, uint64_t lenght);
void caffeine_container_fill(cff_container* container, uintptr_t ptr_in, uint64_t lenght);
void caffeine_container_foreach(cff_container* container, foreach_fn foreach_function, uint64_t lenght);
void caffeine_container_free(cff_container* container, AllocatorInterface* allocator);

cff_err_e caffeine_container_create(cff_container* container, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_container_map(cff_container* container, map_fn map_function, cff_container* ptr_out, uint64_t out_data_size, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_container_sort(cff_container* container, comparer_fn comparer_function, uint64_t lenght);
cff_err_e caffeine_container_reverse(cff_container* container, uint64_t lenght);
cff_err_e caffeine_container_resize(cff_container* container, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_container_copy(cff_container* container, cff_container* ptr_out, uint64_t start, uint64_t end, uint64_t out_lenght, uint64_t* copied_count, AllocatorInterface* allocator);
cff_err_e caffeine_container_clone(cff_container* container, cff_container* out_lenght, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e caffeine_container_join(cff_container* container, cff_container* other, uint64_t start, uint64_t container_lenght, uint64_t other_lenght, AllocatorInterface* allocator);
cff_err_e caffeine_container_filter(cff_container* container, filter_fn filter_function, cff_container* ptr_out, uint64_t lenght, uint64_t* out_lenght, AllocatorInterface* allocator);

uint8_t caffeine_container_equal(cff_container* container, cff_container* other, uint64_t lenght);
uint8_t caffeine_container_find(cff_container* container, uintptr_t ptr_in, uint64_t* out_index, uint64_t lenght);
uint8_t caffeine_container_find_cmp(cff_container* container, uintptr_t ptr_in, uint64_t* out_index, comparer_fn comparer_function, uint64_t lenght);
uint64_t caffeine_container_count(cff_container* container, uintptr_t ptr_in, uint64_t lenght);
uint64_t caffeine_container_count_cmp(cff_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght);
uint8_t caffeine_container_any(cff_container* container, uintptr_t ptr_in, uint64_t lenght);
uint8_t caffeine_container_any_cmp(cff_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght);
uint8_t caffeine_container_all(cff_container* container, uintptr_t ptr_in, uint64_t lenght);
uint8_t caffeine_container_all_cmp(cff_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght);



#endif // !CAFFEINE_CONTAINER_H
