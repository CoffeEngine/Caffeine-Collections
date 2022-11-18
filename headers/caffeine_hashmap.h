#ifndef CAFFEINE_HASH_MAP_H
#define CAFFEINE_HASH_MAP_H

#include "caffeine_core.h"
#include "caffeine_types.h"
#include "caffeine_bitmap.h"
#include <stdint.h>

typedef uint64_t(*cff_hash_key_func)(uintptr_t data_ptr, uint32_t data_size);
typedef int8_t(*cff_cmp_key_func)(uintptr_t key_a, uintptr_t key_b,uint32_t data_size);
typedef void(*cff_cpy_key_func)(uintptr_t from, uintptr_t to, uint32_t data_size);

struct caffeine_hashmap_s {
	uintptr_t buffer;
	uint32_t key_size;
	uint32_t data_size;
	uint64_t lenght;
	uint64_t count;
	uint64_t prime_value;
	uint64_t collision_count_max;
	cff_hash_key_func hash_func;
	cff_cmp_key_func cmp_func;
	cff_cpy_key_func cpy_func;
	cff_bitmap bitmap;
};

typedef struct caffeine_hashmap_s cff_hashmap;

cff_err_e cff_hashmap_create(cff_hashmap* hashmap, uint32_t key_size, uint32_t data_size,uint64_t lenght, cff_hash_key_func hash_func, cff_cmp_key_func cmp_func, cff_cpy_key_func cpy_func, AllocatorInterface* allocator);
cff_err_e cff_hashmap_create_default(cff_hashmap* hashmap, uint32_t key_size, uint32_t data_size, AllocatorInterface* allocator);

uint8_t cff_hashmap_add(cff_hashmap* hashmap, uintptr_t key, uintptr_t value, AllocatorInterface* allocator);
uint8_t cff_hashmap_get(cff_hashmap* hashmap, uintptr_t key, uintptr_t value);
uint8_t cff_hashmap_remove(cff_hashmap* hashmap, uintptr_t key);

uint8_t cff_hashmap_exist_key(cff_hashmap* hashmap, uintptr_t key);

void cff_hashmap_free(cff_hashmap* hashmap, AllocatorInterface* allocator);
void cff_hashmap_clear(cff_hashmap* hashmap);
#endif // !CAFFEINE_HASH_MAP_H
