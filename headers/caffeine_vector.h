#ifndef CAFFEINE_VECTOR_H
#define CAFFEINE_VECTOR_H

/**
 * @defgroup Vector
 * @file caffeine_vector.h
 * @author Ruan Azevedo
 * @brief A contiguos chunk of memory that is automaticaly resized when gets full and an add attemption is made.
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdint.h>
#include "caffeine_core.h"
#include "caffeine_types.h"

/**
 * @ingroup Vector
 * @struct caffeine_vector_s
 * @brief 
 * 
 * It keeps their elements contiguous on memory and grow automaticaly when gets full.
 * 
 */
struct caffeine_vector_s { 

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
 * @ingroup Vector
 * @typedef struct caffeine_vector_s cff_vector
 * @brief Syntax sugar for struct caffeine_vector_s.
 * 
 */
typedef struct caffeine_vector_s cff_vector;

/**
 * @ingroup Vector
 * @brief Allocates a buffer to the vector and sets its fields properly.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_size [in] The size in bytes of each element.
 * @param lenght [in] The max number of elements the vector will have.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_vector_create(cff_vector* vector, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Reallocates the buffer owned by the vector.
 * 
 * * The size of memory allocated is equals to data_size * lenght in bytes, notes that data_size is the value informed when cff_array_create is called.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param vector [in] Pointer to a vector.
 * @param lenght [in] The new max number of elements the vector will have.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_vector_resize(cff_vector* vector, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Gets the value at a give index.
 * 
 * Copies the data present at the index position to the adress pointed by ptr_out.
 * @param vector [in] Pointer to a vector.
 * @param index [in] Position of the data inside the vector buffer.
 * @param out [out] Adress where the data will be copied.
 */
void cff_vector_get(cff_vector* vector, uint64_t index, uintptr_t out);

/**
 * @ingroup Vector
 * @brief Sets the value at index position to the value pointed by ptr_in.
 * 
 * This function will copy the content at ptr_in adress to the location indicated by index.
 * Keep in mind that the current value present at index position will be overwrited.
 *
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Adress from where the data will be copied.
 * @param index [in] Position of the data inside the vector buffer.
 */
void cff_vector_set(cff_vector* vector, uintptr_t data_ptr, uint64_t index);

/**
 * @ingroup Vector
 * @brief Shifts all elements starting on index position to right and sets the value at index position to the value pointed by ptr_in.
 * 
 * This function will copy the content at ptr_in adress to the location indicated by index.
 * Keep in mind that all elements on index position and after will be sihfted by one position to the right, it means that the value at the last index will be lost.
 *
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Adress from where the data will be copied.
 * @param index [in] Position of the data inside the vector buffer.
 */
void cff_vector_insert(cff_vector* vector, uintptr_t data_ptr, uint64_t index);

/**
 * @ingroup Vector
 * @brief Removes an element from vector by shifting all elements starting on index position to the left.
 *
 * This function shifts all elements starting on index to the left, (eg. vector[i] = vector[i+1]).
 * If the index is equals to lenght - 1 (last element) the function just returns.
 * Keep in mind thet when an element (except at lenght - 1 ) is removed, there will exist two copies of the last element at the end of the vector.
 *
 * @param vector [in] Pointer to a vector.
 * @param index [in] Position of the data inside the vector buffer.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_remove(cff_vector* vector, uint64_t index, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Copies a section of data from one vector to other
 * 
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param vector [in] Pointer to a vector.
 * @param to [out] Pointer to an vector that will receive the copy
 * @param start [in] Index from where the copy process will start
 * @param count [in] How many elements to copy from start.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_vector_copy(cff_vector* vector, cff_vector* to, uint64_t start, uint64_t count, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Copies all elements from one vector to other
 * 
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param vector [in] Pointer to a vector.
 * @param to [out] Pointer to an vector that will receive the copy
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_vector_clone(cff_vector* vector, cff_vector* to, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief 
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Adress from where the data will be copied.
 */
void cff_vector_fill(cff_vector* vector, uintptr_t data_ptr);

/**
 * @ingroup Vector
 * @brief Copies the elements from "other" vector to the vector starting at the end of vector.
 *
 * If the lenght of "other" added to start_at is greater than vector lenght the vector will be resized.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param vector [in] Pointer to a vector.
 * @param from [in] Pointer to an vector to be joined to "vector" at end of vector.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_vector_join(cff_vector* vector, cff_vector* from, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Reverses the order of elements.
 * 
 * @param vector [in] Pointer to a vector.
 */
void cff_vector_reverse(cff_vector* vector);

/**
 * @ingroup Vector
 * @brief Filters the elements of an vector and puts the result on other.
 * 
 * Creates a new vector based on an existing one, the elements of the new vector must complies the filter_function criteria.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param vector [in] Pointer to a vector.
 * @param func [in] Callback that determines if the element complies the criteria for the new vector.
 * @param filter_result [out] Pointer to the vector that will receive the filtered elements.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_filter(cff_vector* vector, filter_fn func, cff_vector* filter_result, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Transforms the elements of an vector and puts the result on other.
 * 
 * Creates a new vector based on an existing one, the elements of the new vector will be the result from map_function when called passed an element from vector in the parameters.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param vector [in] Pointer to a vector.
 * @param func [in] Callback that defines how to transform from one type to other.
 * @param map_result [out] Pointer to the vector that will receive the mapped elements.
 * @param result_data_size [in] The size in bytes of the target type.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_map(cff_vector* vector, map_fn func, cff_vector* map_result, uint64_t result_data_size, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Iterates over the vector and executes an callback to each element.
 * 
 * @param vector [in] Pointer to a vector.
 * @param func [in] Callback that will be called for every element.
 */
void cff_vector_foreach(cff_vector* vector, foreach_fn func);

/**
 * @ingroup Vector
 * @brief Order the elements using the quick sort algorithm.
 * 
 * @param vector [in] Pointer to a vector.
 * @param predicate [in] Callback used to compare the elements.
 */
void cff_vector_sort(cff_vector* vector, comparer_fn predicate);

/**
 * @ingroup Vector
 * @brief Releases the buffer allocated to this vector.
 *
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 * 
 * @param vector [in] Pointer to a vector.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_free(cff_vector* vector, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Removes all elements of the vector.
 * 
 * @param vector [in] Pointer to a vector.
 */
void cff_vector_clear(cff_vector* vector);

/**
 * @ingroup Vector
 * @brief Adds an element at end of the vector.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Adress from where the data will be copied.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_push_back(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Adds an element at start of the vector, this operation forces all other elements to shift 1 position to the right
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Adress from where the data will be copied.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_push_front(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Gets an element from the end of vector removing it
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [out] Adress where the data will be copied.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_pop_back(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Gets an element from the start of vector removing it, this operation forces all other elements to shift 1 position to the left
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [out] Adress where the data will be copied.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_vector_pop_front(cff_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator);

/**
 * @ingroup Vector
 * @brief Checks if the elements in both arrays are equals and with same order.
 * 
 * @param vector [in] Pointer to a vector.
 * @param other [in] Pointer to other vector.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_vector_equal(cff_vector* vector, cff_vector* other);

/**
 * @ingroup Vector
 * @brief Gets the index of the first ocurrency of the value pointed by ptr_in in vector.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to find in the vector.
 * @param found [out] Receives the index where the value was found. If not found the value at its adress will not change.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_vector_find(cff_vector* vector, uintptr_t data_ptr, uint64_t* found);

/**
 * @ingroup Vector
 * @brief Gets the index of the first ocurrency of the value pointed by ptr_in in vector.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to be find in the vector.
 * @param found [out] Receives the index where the value was found. If not found the value at its adress will not change.
 * @param predicate [in] Callback used to compare the elements.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_vector_find_cmp(cff_vector* vector, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate);

/**
 * @ingroup Vector
 * @brief Counts the number of ocurrencies of elements equals to value pointed by ptr_in.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to be count in the vector.
 * @return uint64_t The number of ocurrencies of elements equals to value pointed by ptr_in.
 */
uint64_t cff_vector_count(cff_vector* vector, uintptr_t data_ptr);

/**
 * @ingroup Vector
 * @brief Counts the number of ocurrencies of elements equals to value pointed by ptr_in.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to be count in the vector.
 * @param predicate [in] Callback used to compare the elements.
 * @return uint64_t The number of ocurrencies of elements equals to value pointed by ptr_in.
 */
uint64_t cff_vector_count_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate);

/**
 * @ingroup Vector
 * @brief Checks the ocurrency of value pointed by ptr_in on the vector.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to be find in the vector.
 * @return uint8_t Retuns 1 if there is at least one ocurrency, otherwise returns 0.
 */
uint8_t cff_vector_any(cff_vector* vector, uintptr_t data_ptr);

/**
 * @ingroup Vector
 * @brief Checks the ocurrency of value pointed by ptr_in on the vector.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to be find in the vector.
 * @param predicate [in] Callback used to compare the elements.
 * @return uint8_t Retuns 1 if there is at least one ocurrency, otherwise returns 0.
 */
uint8_t cff_vector_any_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate);

/**
 * @ingroup Vector
 * @brief Checks if all vector elements are equals to value pointed by ptr_in.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to be find in the vector.
 * @return uint8_t Retuns 1 if all elements are equal to value pointed by ptr_in, otherwise returns 0.
 */
uint8_t cff_vector_all(cff_vector* vector, uintptr_t data_ptr);

/**
 * @ingroup Vector
 * @brief Checks if all vector elements are equals to value pointed by ptr_in.
 * 
 * @param vector [in] Pointer to a vector.
 * @param data_ptr [in] Pointer to data to be find in the vector.
 * @param predicate [in] Callback used to compare the elements.
 * @return uint8_t Retuns 1 if all elements are equal to value pointed by ptr_in, otherwise returns 0.
 */
uint8_t cff_vector_all_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate);

#endif // !CAFFEINE_VECTOR_H
