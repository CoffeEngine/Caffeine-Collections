#ifndef CAFFEINE_ORDERED_VECTOR_H
#define CAFFEINE_ORDERED_VECTOR_H

#include "caffeine_core.h"


struct caffeine_ordered_vector_s {

    struct
    {
        /**
         * @brief Pointer to vector buffer.
         *
         */
        uintptr_t buffer;
        /**
         * @brief Size in bytes of each element.
         *
         */
        uint64_t data_size;

        comparer_fn comparer_function;
    };
    /**
     * @brief How many elements the vector contains
     *
     */
    uint64_t lenght;
    /**
     * @brief How many elements the vector contains
     *
     */
    uint64_t count;
};

/**
 * @ingroup Ordered Vector
 * @typedef struct caffeine_ordered_vector_s cff_ordered_vector
 * @brief Syntax sugar for struct caffeine_ordered_vector_s.
 *
 */
typedef struct caffeine_ordered_vector_s cff_ordered_vector;


cff_err_e cff_ordered_vector_create(cff_ordered_vector* vector, uint64_t data_size, comparer_fn compare_function, uint64_t lenght, AllocatorInterface* allocator);
cff_err_e cff_ordered_vector_resize(cff_ordered_vector* vector, uint64_t lenght, AllocatorInterface* allocator);
void cff_ordered_vector_get(cff_ordered_vector* vector, uint64_t index, uintptr_t out);
void cff_ordered_vector_remove(cff_ordered_vector* vector, uint64_t index, AllocatorInterface* allocator);
cff_err_e cff_ordered_vector_copy(cff_ordered_vector* vector, cff_ordered_vector* to, uint64_t start, uint64_t count, AllocatorInterface* allocator);
cff_err_e cff_ordered_vector_clone(cff_ordered_vector* vector, cff_ordered_vector* to, AllocatorInterface* allocator);
void cff_ordered_vector_fill(cff_ordered_vector* vector, uintptr_t data_ptr);
cff_err_e cff_ordered_vector_join(cff_ordered_vector* vector, cff_ordered_vector* from, AllocatorInterface* allocator);
void cff_ordered_vector_filter(cff_ordered_vector* vector, filter_fn func, cff_ordered_vector* filter_result, AllocatorInterface* allocator);
void cff_ordered_vector_map(cff_ordered_vector* vector, map_fn func, cff_ordered_vector* map_result, comparer_fn out_comparer_function, uint64_t result_data_size, AllocatorInterface* allocator);
void cff_ordered_vector_foreach(cff_ordered_vector* vector, foreach_fn func);
void cff_ordered_vector_sort(cff_ordered_vector* vector, comparer_fn predicate);
void cff_ordered_vector_free(cff_ordered_vector* vector, AllocatorInterface* allocator);
void cff_ordered_vector_clear(cff_ordered_vector* vector);
void cff_ordered_vector_add(cff_ordered_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);
void cff_ordered_vector_pop_back(cff_ordered_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);
void cff_ordered_vector_pop_front(cff_ordered_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);
uint8_t cff_ordered_vector_equal(cff_ordered_vector* vector, cff_ordered_vector* other);
uint8_t cff_ordered_vector_find(cff_ordered_vector* vector, uintptr_t data_ptr, uint64_t* found);
uint8_t cff_ordered_vector_find_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate);
uint64_t cff_ordered_vector_count(cff_ordered_vector* vector, uintptr_t data_ptr);
uint64_t cff_ordered_vector_count_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, comparer_fn predicate);
uint8_t cff_ordered_vector_any(cff_ordered_vector* vector, uintptr_t data_ptr);
uint8_t cff_ordered_vector_any_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, comparer_fn predicate);
uint8_t cff_ordered_vector_all(cff_ordered_vector* vector, uintptr_t data_ptr);
uint8_t cff_ordered_vector_all_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, comparer_fn predicate);


#endif // !CAFFEINE_ORDERED_VECTOR_H
