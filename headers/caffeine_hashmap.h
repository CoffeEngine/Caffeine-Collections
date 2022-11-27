#ifndef CAFFEINE_HASH_MAP_H
#define CAFFEINE_HASH_MAP_H

/**
 * @defgroup Hashmap
 * @file caffeine_hashmap.h
 * @author Ruan Azevedo (you@domain.com)
 * @brief Provides a hasmap data structure
 * @version 0.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caffeine_core.h"
#include "caffeine_types.h"
#include "caffeine_bitmap.h"
#include <stdint.h>

/**
 * @ingroup Hashmap
 * @brief Callback that hashes the key data to a 64 bits integer.
 * 
 * @param data_ptr Pointer to a key.
 * @param data_size Size of key in bytes.
 * @return uint64_t The hash output, this value will be used to index the object stored.
 */
typedef uint64_t(*cff_hash_key_func)(uintptr_t data_ptr, uint32_t data_size);

/**
 * @ingroup Hashmap
 * @brief Callback that compares two keys and returns if they are equals.
 * 
 * @param key_a Pointer to a key.
 * @param key_b Pointer to a key.
 * @param data_size Size of keys in bytes.
 * @return int8_t 1 if are equals, 0 if not.
 */
typedef int8_t(*cff_cmp_key_func)(uintptr_t key_a, uintptr_t key_b,uint32_t data_size);

/**
 * @ingroup Hashmap
 * @brief Callback that copies the content of a key buffer to other.
 * 
 * @param from Pointer to a key to be copied.
 * @param to Pointer to a key to receive the copy.
 * @param data_size Size in bytes to be copied.
 */
typedef void(*cff_cpy_key_func)(uintptr_t from, uintptr_t to, uint32_t data_size);

/**
 * @ingroup Hashmap
 * @brief 
 * 
 */
struct caffeine_hashmap_s {
	/**
	 * @brief Stores the hashmap data, both key and value are stored togeter
	 * 
	 */
	uintptr_t buffer;

	/**
	 * @brief Key size in bytes
	 * 
	 */
	uint32_t key_size;

	/**
	 * @brief Value size in bytes
	 * 
	 */
	uint32_t data_size;

	/**
	 * @brief How many key-values fits in the buffer
	 * 
	 */
	uint64_t lenght;

	/**
	 * @brief How many elements the hashmap contains
	 * 
	 */
	uint64_t count;

	/**
	 * @brief Helper value used to calculates the second hash in colision case
	 * 
	 */
	uint64_t prime_value;

	/**
	 * @brief Tracks the max number of colisions ocurred in an insert attemption
	 * 
	 */
	uint64_t collision_count_max;

	/**
	 * @brief Pointer to a hash function callback
	 * 
	 */
	cff_hash_key_func hash_func;

	/**
	 * @brief Pointer to a comparer function callback
	 * 
	 */
	cff_cmp_key_func cmp_func;

	/**
	 * @brief Pointer to a copy function callback
	 * 
	 */
	cff_cpy_key_func cpy_func;

	/**
	 * @brief Auxiliar structure to keep track wich indexes are in use
	 * 
	 */
	cff_bitmap bitmap;
};

/**
 * @typedef struct caffeine_hashmap_s cff_hashmap
 * @ingroup Hashmap
 * @brief Syntax sugar for struct caffeine_hashmap_s
 * 
 */
typedef struct caffeine_hashmap_s cff_hashmap;

/**
 * @ingroup Hashmap
 * @brief Initializes the hashmap structure
 * 
 * 	This functions allows the user to improve the hashmap for his use case, possibiliting to set callbacks that better handles the key.
 * 
 * @param hashmap [in] Pointer to a hashmap.
 * @param key_size [in] Key size in bytes.
 * @param data_size [in] Value size in bytes
 * @param lenght [in] How many elements will be allocated initialy
 * @param hash_func [in] Pointer to a hash function callback
 * @param cmp_func [in] Pointer to a comparer function callback
 * @param cpy_func [in] Pointer to a copy function callback
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_hashmap_create(cff_hashmap* hashmap, uint32_t key_size, uint32_t data_size,uint64_t lenght, cff_hash_key_func hash_func, cff_cmp_key_func cmp_func, cff_cpy_key_func cpy_func, AllocatorInterface* allocator);

/**
 * @ingroup Hashmap
 * @brief Initializes the hashmap structure using generic functions to handle the key.
 * 
 * @param hashmap [in] Pointer to a hashmap. 
 * @param key_size [in] Key size in bytes.
 * @param data_size [in] Value size in bytes
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_hashmap_create_default(cff_hashmap* hashmap, uint32_t key_size, uint32_t data_size, AllocatorInterface* allocator);

/**
 * @ingroup Hashmap
 * @brief Try to add a key-value pair in the hash map, if the key already exists its content is overwrited.
 * 
 * @param hashmap [in] Pointer to a hashmap. 
 * @param key [in] Pointer to key.
 * @param value [in] Pointer to value.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_hashmap_add(cff_hashmap* hashmap, uintptr_t key, uintptr_t value, AllocatorInterface* allocator);

/**
 * @ingroup Hashmap
 * @brief Try to retrieve a value by its key, if the key dont be found, value content will not be changed and the functions returns 0.
 * 
 * @param hashmap [in] Pointer to a hashmap. 
 * @param key [in] Pointer to key.
 * @param value [out] Pointer to buffer that will receive the value.
 * @return uint8_t 1 if the value was found else 0.
 */
uint8_t cff_hashmap_get(cff_hashmap* hashmap, uintptr_t key, uintptr_t value);

/**
 * @ingroup Hashmap
 * @brief Try to remove a value by its key, if the key dont be found, returns 0.
 * 
 * @param hashmap [in] Pointer to a hashmap. 
 * @param key [in] Pointer to key.
 * @return uint8_t 1 if the key exists else 0.
 */
uint8_t cff_hashmap_remove(cff_hashmap* hashmap, uintptr_t key);

/**
 * @ingroup Hashmap
 * @brief Checks if a key exists in the hashmap.
 * 
 * @param hashmap [in] Pointer to a hashmap. 
 * @param key [in] Pointer to key.
 * @return uint8_t 1 if the key exists else 0.
 */
uint8_t cff_hashmap_exist_key(cff_hashmap* hashmap, uintptr_t key);

/**
 * @ingroup Hashmap
 * @brief Deallocates the buffer owned by the hashmap.
 * 
 * @param hashmap [in] Pointer to a hashmap. 
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_hashmap_free(cff_hashmap* hashmap, AllocatorInterface* allocator);

/**
 * @ingroup Hashmap
 * @brief Removes all values from hashmap
 * 
 * @param hashmap [in] Pointer to a hashmap. 
 */
void cff_hashmap_clear(cff_hashmap* hashmap);

#endif // !CAFFEINE_HASH_MAP_H
