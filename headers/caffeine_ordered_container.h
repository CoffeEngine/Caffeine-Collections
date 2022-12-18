#ifndef CAFFEINE_ORDERED_CONTAINER_H
#define CAFFEINE_ORDERED_CONTAINER_H

#include "caffeine_core.h"

struct caffeine_ordered_containter_s {
    uintptr_t buffer;
    uint64_t data_size;
    comparer_fn comparer_function;
};

typedef struct caffeine_ordered_containter_s cff_ordered_container;


void cff_ordered_container_add(cff_ordered_container* container, uintptr_t ptr_in, uint64_t count, uint64_t lenght);
void cff_ordered_container_free(cff_ordered_container* container, AllocatorInterface* allocator);
void cff_ordered_container_get(cff_ordered_container* container, uint64_t index, uintptr_t ptr_out, uint64_t lenght);
void cff_ordered_container_fill(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght);
void cff_ordered_container_foreach(cff_ordered_container* container, foreach_fn foreach_function, uint64_t lenght);

cff_err_e cff_ordered_container_create(cff_ordered_container* container, uint64_t data_size, comparer_fn comparer_function, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e cff_ordered_container_join(cff_ordered_container* container, cff_ordered_container* other, uint64_t start, uint64_t container_lenght, uint64_t other_lenght, AllocatorInterface* allocator);
cff_err_e cff_ordered_container_sort(cff_ordered_container* container, comparer_fn comparer_function, uint64_t lenght);
cff_err_e cff_ordered_container_map(cff_ordered_container* container, map_fn map_function, cff_ordered_container* ptr_out, comparer_fn out_comparer_function, uint64_t out_data_size, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e cff_ordered_container_resize(cff_ordered_container* container, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e cff_ordered_container_copy(cff_ordered_container* container, cff_ordered_container* ptr_out, uint64_t start, uint64_t count, uint64_t out_lenght, uint64_t* copied_count, AllocatorInterface* allocator);
cff_err_e cff_ordered_container_clone(cff_ordered_container* container, cff_ordered_container* out, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e cff_ordered_container_filter(cff_ordered_container* container, filter_fn filter_function, cff_ordered_container* ptr_out, uint64_t lenght, uint64_t* out_lenght, AllocatorInterface* allocator);

uint8_t cff_ordered_container_remove(cff_ordered_container* container, uint64_t index, uint64_t lenght);
uint8_t cff_ordered_container_equal(cff_ordered_container* container, cff_ordered_container* other, uint64_t lenght);
uint8_t cff_ordered_container_find(cff_ordered_container* container, uintptr_t ptr_in, uint64_t* out_index, uint64_t lenght);
uint8_t cff_ordered_container_find_cmp(cff_ordered_container* container, uintptr_t ptr_in, uint64_t* out_index, comparer_fn comparer_function, uint64_t lenght);
uint64_t cff_ordered_container_count(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght);
uint64_t cff_ordered_container_count_cmp(cff_ordered_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght);
uint8_t cff_ordered_container_any(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght);
uint8_t cff_ordered_container_any_cmp(cff_ordered_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght);
uint8_t cff_ordered_container_all(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght);
uint8_t cff_ordered_container_all_cmp(cff_ordered_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght);

#endif