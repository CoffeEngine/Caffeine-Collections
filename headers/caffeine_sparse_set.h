#ifndef CAFFEINE_SPARSE_SET
#define CAFFEINE_SPARSE_SET

/**
 * @defgroup Sparse Set
 * @file caffeine_sparse_set.h
 * @author Ruan Azevedo
 * @brief 
 * @version 0.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caffeine_core.h"
#include "caffeine_types.h"
#include "caffeine_memory.h"

/**
 * @defgroup Sparse Set
 * @brief 
 * 
 */
struct caffeine_sparse_set_s
{
	/**
	 * @brief The dense buffer, there is no hole betwen the elements.
	 * 
	 */
	uintptr_t dense;
	/**
	 * @brief Tracks back the index of an element in the dense buffer.
	 * 
	 */
	uint64_t* dense_index;
	/**
	 * @brief Stores the indexes that user "see".
	 * 
	 */
	uint64_t* sparse;
	/**
	 * @brief How many elements fits in the buffer.
	 * 
	 */
	uint64_t lenght;
	/**
	 * @brief How many elements the hashmap contains.
	 * 
	 */
	uint64_t count;
	/**
	 * @brief Element size in bytes.
	 * 
	 */
	uint64_t data_size;
};

/**
 * @defgroup Sparse Set
 * @brief Syntax sugar for struct caffeine_sparse_set
 * 
 */
typedef struct caffeine_sparse_set_s cff_sparseset;

/**
 * @defgroup Sparse Set
 * @brief Initializes the sparse set structure
 * 
 * @param set [in] Pointer to a sparse set.
 * @param lenght [in] How many elements will be allocated initialy.
 * @param data_size [in] Element size in bytes
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_sparseset_create(cff_sparseset* set, uint64_t lenght, uint64_t data_size, AllocatorInterface* allocator);

/**
 * @defgroup Sparse Set
 * @brief Try to add an element in the sparse set.
 * 
 * @param set [in] Pointer to a sparse set.
 * @param index [in] Index where to store the element
 * @param data [in] Pointer to the element to be stored.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_sparseset_add(cff_sparseset* set, uint64_t index, uintptr_t data, AllocatorInterface* allocator);

/**
 * @defgroup Sparse Set
 * @brief Try to retrieve an element from sparse set.
 * 
 * @param set [in] Pointer to a sparse set.
 * @param index [in] Index where to find the element
 * @param data [out] Pointer to buffer that will receive the value.
 */
void cff_sparseset_get(cff_sparseset* set, uint64_t index, uintptr_t data);

/**
 * @defgroup Sparse Set
 * @brief Try to remove an element from the sparse set.
 * 
 * @param set [in] Pointer to a sparse set.
 * @param index [in] Index where to find the element
 */
void cff_sparseset_remove(cff_sparseset* set, uint64_t index);

/**
 * @defgroup Sparse Set
 * @brief Removes all elements from the sparse set.
 * 
 * @param set [in] Pointer to a sparse set.
 */
void cff_sparseset_clear(cff_sparseset* set);

/**
 * @defgroup Sparse Set
 * @brief Deallocates the buffers owned by the sparse set.
 * 
 * @param set [in] Pointer to a sparse set.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_sparseset_free(cff_sparseset* set, AllocatorInterface* allocator);

/**
 * @defgroup Sparse Set
 * @brief Gets the pointer to the sparse set dense buffer
 * 
 * @param set [in] Pointer to a sparse set.
 * @return uintptr_t Pointer to the sparse set dense buffer
 */
uintptr_t cff_sparseset_get_dense(cff_sparseset* set);
#endif // !CAFFEINE_SPARSE_SET
