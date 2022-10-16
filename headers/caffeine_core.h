#ifndef CAFFEINE_CORE_H
#define CAFFEINE_CORE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "caffeine_allocator_interface.h"

enum cff_comparer_value_e{
	CFF_NOT_EQUAL = -2,
	CFF_LESS = -1,
	CFF_EQUALS = 0,
	CFF_GREATER = 1,
};

enum cff_error_value_e {
	CFF_NONE_ERR = 0,
	CFF_ALLOC_ERR,
	CFF_REALLOC_ERR,
};


typedef enum cff_comparer_value_e cff_cmp_e;
typedef enum cff_error_value_e cff_err_e;

typedef cff_cmp_e (*comparer_fn)(void* a_ptr, void* b_ptr, uint64_t data_size);
typedef bool (*filter_fn)(void* data_ptr, uint64_t index, uint64_t data_size);
typedef void(*map_fn)(void* from_ptr, void* to_ptr, uint64_t index);
typedef void(*foreach_fn)(void* data_ptr, uint64_t index);

typedef void (*debug_callback)(char* str, uint64_t str_len);
typedef uint64_t(*string_parser)(uintptr_t pointer, uint64_t data_size, char** buffer,AllocatorInterface* allocator);

struct caffeine_containter_s {
	uintptr_t buffer;
	uint64_t data_size;
};

AllocatorInterface* caffeine_get_default_allocator();
void caffeine_set_default_allocator(AllocatorInterface* allocator);

#define derive_container(name,fields) struct name { struct caffeine_containter_s;  fields }

#define resolve_ptr(ptr) ((uintptr_t)(ptr))

#endif // !CAFFEINE_CORE_H
