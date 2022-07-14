#ifndef CAFFEINE_CONTAINER_H
#define CAFFEINE_CONTAINER_H

#include "caffeine_core.h"

typedef struct caffeine_containter_s cff_container;

void caffeine_container_create(cff_container* container,uint64_t data_size,uint64_t lenght);
void caffeine_container_desloc(cff_container* container, uint64_t from, int64_t steps, uint64_t lenght);
void caffeine_container_resize(cff_container* container, uint64_t lenght);
void caffeine_container_get(cff_container* container, uint64_t index, uintptr_t out);
void caffeine_container_set(cff_container* container, uintptr_t data_ptr, uint64_t index);
void caffeine_container_insert(cff_container* container, uintptr_t data_ptr, uint64_t index, uint64_t lenght);
void caffeine_container_remove(cff_container* container, uint64_t index, uint64_t lenght);
uint64_t caffeine_container_copy(cff_container* container, cff_container* to, uint64_t start, uint64_t end, uint64_t lenght);
void caffeine_container_clone(cff_container* container, cff_container* to, uint64_t lenght);
void caffeine_container_fill(cff_container* container, uintptr_t data_ptr, uint64_t lenght);
void caffeine_container_join(cff_container* container, cff_container* from, uint64_t c_lenght, uint64_t f_lenght);
void caffeine_container_reverse(cff_container* container, uint64_t lenght);
uint64_t caffeine_container_filter(cff_container* container, filter_fn func, cff_container* filter_result, uint64_t lenght);
void caffeine_container_use_filters(cff_container* container, filter_fn* funcs, uint64_t filters_len, cff_container* filter_result, uint64_t lenght);
void caffeine_container_map(cff_container* container, map_fn func, cff_container* map_result, uint64_t result_data_size, uint64_t lenght);
void caffeine_container_foreach(cff_container* container, foreach_fn func, uint64_t lenght);
void caffeine_container_sort(cff_container* container, comparer_fn predicate, uint64_t lenght);
void caffeine_container_free(cff_container* container);

uint8_t caffeine_container_equal(cff_container* container, cff_container* other, uint64_t lenght);
uint8_t caffeine_container_find(cff_container* container, uintptr_t data_ptr, uint64_t* found, uint64_t lenght);
uint8_t caffeine_container_find_cmp(cff_container* container, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate, uint64_t lenght);
uint64_t caffeine_container_count(cff_container* container, uintptr_t data_ptr, uint64_t lenght);
uint64_t caffeine_container_count_cmp(cff_container* container, uintptr_t data_ptr, comparer_fn predicate, uint64_t lenght);
uint8_t caffeine_container_any(cff_container* container, uintptr_t data_ptr, uint64_t lenght);
uint8_t caffeine_container_any_cmp(cff_container* container, uintptr_t data_ptr, comparer_fn predicate, uint64_t lenght);
uint8_t caffeine_container_all(cff_container* container, uintptr_t data_ptr, uint64_t lenght);
uint8_t caffeine_container_all_cmp(cff_container* container, uintptr_t data_ptr, comparer_fn predicate, uint64_t lenght);



#endif // !CAFFEINE_CONTAINER_H
