#ifndef CAFFEINE_LIST_H
#define CAFFEINE_LIST_H

#include "caffeine_core.h"
#include "caffeine_types.h"
#include "caffeine_assertions.h"

struct caffeine_list_bucket_t {
	struct caffeine_list_bucket_t* next_bucket;
	uintptr_t data_ptr;
};

typedef struct caffeine_list_bucket_t caffeine_list_bucket;

struct caffeine_list_t
{
	uint64_t data_size;
	uint64_t count;
	caffeine_list_bucket* list_start;
	caffeine_list_bucket* list_end;
};

typedef struct caffeine_list_t cff_list;

void cff_list_create(cff_list* list, uint64_t data_size);
void cff_list_set(cff_list* list, uint64_t index, uintptr_t data);
void cff_list_get(cff_list* list, uint64_t index, uintptr_t data_out);
void cff_list_first(cff_list* list, uintptr_t data_out);
void cff_list_last(cff_list* list, uintptr_t data_out);
void cff_list_remove(cff_list* list, uint64_t index, AllocatorInterface* allocator);
void cff_list_reverse(cff_list* list);
void cff_list_clear(cff_list* list, AllocatorInterface* allocator);
void cff_list_join(cff_list* list, cff_list* other);
void cff_list_sort(cff_list* list, comparer_fn comparer_function);
void cff_list_foreach(cff_list* list, foreach_fn foreach_function);

cff_err_e cff_list_add(cff_list* list, uintptr_t data, AllocatorInterface* allocator);
cff_err_e cff_list_insert(cff_list* list, uint64_t index, uintptr_t data, AllocatorInterface* allocator);
cff_err_e cff_list_clone(cff_list* list, cff_list* other, AllocatorInterface* allocator);
cff_err_e cff_list_copy(cff_list* list, cff_list* other, uint64_t start, uint64_t count, AllocatorInterface* allocator);
cff_err_e cff_list_filter(cff_list* list, filter_fn filter_function, cff_list* ptr_out, AllocatorInterface* allocator);
cff_err_e cff_list_map(cff_list* list, map_fn map_function, cff_list* ptr_out, uint64_t out_data_size, AllocatorInterface* allocator);

uint8_t cff_list_equal(cff_list* list, cff_list* other);
uint8_t cff_list_equal_cmp(cff_list* list, cff_list* other, comparer_fn comparer_function);
uint8_t cff_list_find(cff_list* list, uintptr_t data_f,uint64_t* out_index, uintptr_t data_out);
uint8_t cff_list_find_cmp(cff_list* list, uintptr_t data_f, uint64_t* out_index, uintptr_t data_out, comparer_fn comparer_function);
uint8_t cff_list_any(cff_list* list, uintptr_t data_f);
uint8_t cff_list_any_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function);
uint8_t cff_list_all(cff_list* list, uintptr_t data_f);
uint8_t cff_list_all_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function);
uint64_t cff_list_count(cff_list* list, uintptr_t data_f);
uint64_t cff_list_count_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function);

#endif