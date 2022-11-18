#ifndef CAFFEINE_ARRAY_H
#define CAFFEINE_ARRAY_H

#include "caffeine_core.h"
#include "caffeine_types.h"

derive_container(caffeine_array_s, uint64_t lenght;);
typedef struct caffeine_array_s cff_array;

void cff_array_get(cff_array* array, uint64_t index, uintptr_t ptr_out);

void cff_array_set(cff_array* array, uint64_t index, uintptr_t ptr_in);

void cff_array_insert(cff_array* array, uint64_t index, uintptr_t ptr_in);

void cff_array_remove(cff_array* array, uint64_t index);

void cff_array_fill(cff_array* array, uintptr_t ptr_in);

void cff_array_foreach(cff_array* array, foreach_fn foreach_function);

void cff_array_free(cff_array* array, AllocatorInterface* allocator);


cff_err_e cff_array_create(cff_array* array, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);

cff_err_e cff_array_resize(cff_array* array, uint64_t lenght, AllocatorInterface* allocator);

cff_err_e cff_array_copy(cff_array* array, cff_array* ptr_out, uint64_t start, uint64_t count, AllocatorInterface* allocator);

cff_err_e cff_array_clone(cff_array* array, cff_array* ptr_out, AllocatorInterface* allocator);

cff_err_e cff_array_join(cff_array* array, cff_array* other, uint64_t start_at, AllocatorInterface* allocator);

cff_err_e cff_array_reverse(cff_array* array);

cff_err_e cff_array_filter(cff_array* array, filter_fn filter_function, cff_array* ptr_out, AllocatorInterface* allocator);

cff_err_e cff_array_map(cff_array* array, map_fn map_function, cff_array* ptr_out, uint64_t out_data_size, AllocatorInterface* allocator);

cff_err_e cff_array_sort(cff_array* array, comparer_fn comparer_function);

uint8_t cff_array_equal(cff_array* array, cff_array* other);

uint8_t cff_array_find(cff_array* array, uintptr_t ptr_in, uint64_t* out_index);

uint8_t cff_array_find_cmp(cff_array* array, uintptr_t ptr_in, uint64_t* out_index, comparer_fn comparer_function);

uint64_t cff_array_count(cff_array* array, uintptr_t ptr_in);

uint64_t cff_array_count_cmp(cff_array* array, uintptr_t ptr_in, comparer_fn comparer_function);

uint8_t cff_array_any(cff_array* array, uintptr_t ptr_in);

uint8_t cff_array_any_cmp(cff_array* array, uintptr_t ptr_in, comparer_fn comparer_function);

uint8_t cff_array_all(cff_array* array, uintptr_t ptr_in);

uint8_t cff_array_all_cmp(cff_array* array, uintptr_t ptr_in, comparer_fn comparer_function);

#endif // !CAFFEINE_ARRAY_H

