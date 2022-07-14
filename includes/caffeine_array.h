#ifndef CAFFEINE_ARRAY_H
#define CAFFEINE_ARRAY_H

#include "caffeine_core.h"

derive_container(caffeine_array_s, uint64_t lenght;);
typedef struct caffeine_array_s cff_array;


void caffeine_array_create(cff_array* array, uint64_t data_size, uint64_t lenght);
void caffeine_array_resize(cff_array* array, uint64_t lenght);
void caffeine_array_get(cff_array* array, uint64_t index, uintptr_t out);
void caffeine_array_set(cff_array* array, uintptr_t data_ptr, uint64_t index);
void caffeine_array_insert(cff_array* array, uintptr_t data_ptr, uint64_t index);
void caffeine_array_remove(cff_array* array, uint64_t index);
void caffeine_array_copy(cff_array* array, cff_array* to, uint64_t start, uint64_t end);
void caffeine_array_clone(cff_array* array, cff_array* to);
void caffeine_array_fill(cff_array* array, uintptr_t data_ptr);
void caffeine_array_join(cff_array* array, cff_array* from);
void caffeine_array_reverse(cff_array* array);
void caffeine_array_filter(cff_array* array, filter_fn func, cff_array* filter_result);
void caffeine_array_use_filters(cff_array* array, filter_fn* funcs, uint64_t filters_len, cff_array* filter_result);
void caffeine_array_map(cff_array* array, map_fn func, cff_array* map_result, uint64_t result_data_size);
void caffeine_array_foreach(cff_array* array, foreach_fn func);
void caffeine_array_free(cff_array* array);


uint8_t caffeine_array_equal(cff_array* array, cff_array* other);
uint8_t caffeine_array_find(cff_array* array, uintptr_t data_ptr, uint64_t* found);
uint8_t caffeine_array_find_cmp(cff_array* array, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate);
uint64_t caffeine_array_count(cff_array* array, uintptr_t data_ptr);
uint64_t caffeine_array_count_cmp(cff_array* array, uintptr_t data_ptr, comparer_fn predicate);
uint8_t caffeine_array_any(cff_array* array, uintptr_t data_ptr);
uint8_t caffeine_array_any_cmp(cff_array* array, uintptr_t data_ptr, comparer_fn predicate);
uint8_t caffeine_array_all(cff_array* array, uintptr_t data_ptr);
uint8_t caffeine_array_all_cmp(cff_array* array, uintptr_t data_ptr, comparer_fn predicate);



#endif // !CAFFEINE_ARRAY_H
