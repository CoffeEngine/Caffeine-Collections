#ifndef CAFFEINE_ARRAY_H
#define CAFFEINE_ARRAY_H

/**
 * @defgroup Array
 * @file caffeine_array.h
 * @author Ruan Azevedo
 * @brief Defines functions for array initialization and manipulation
 *
 *  The cff_array struct is the closiest to a raw C array regardless its data_size and lenght fields,
 *  it's keeps their elements contiguous on memory and doesnt grow automaticaly when gets full.
 *
 * @version 0.1
 * @date 2022-11-22
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "caffeine_core.h"
#include "caffeine_types.h"

/**
 * @ingroup Array
 * @struct struct caffeine_array_s
 * @brief Is the closiest to a raw C array regardless its data_size and lenght fields.
 *
 * It's keeps their elements contiguous on memory and doesnt grow automaticaly when gets full.
 */
struct caffeine_array_s
{
    struct
    {
        uintptr_t buffer;   ///< Pointer to array buffer.
        uint64_t data_size; ///< Size in bytes of each element.
    };

    uint64_t lenght; ///< How many elements the array contains
};

/**
 * @ingroup Array
 * @typedef typedef struct caffeine_array_s cff_array
 * @brief Syntax sugar for struct caffeine_array_s.
 *
 * It's keeps their elements contiguous on memory and doesnt grow automaticaly when gets full.
 */
typedef struct caffeine_array_s cff_array;

/**
 * @ingroup Array
 * @brief Gets the value at a give index.
 *
 * Copies the data present at the index position to the adress pointed by ptr_out.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param index [in] Position of the data inside the array buffer.
 * @param ptr_out [out] Adress where the data will be copied.
 */
void cff_array_get(cff_array *array, uint64_t index, uintptr_t ptr_out);

/**
 * @ingroup Array
 * @brief Sets the value at index position to the value pointed by ptr_in.
 *
 * This function will copy the content at ptr_in adress to the location indicated by index.
 * Keep in mind that the current value present at index position will be overwrited.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param index [in] Position of the data inside the array buffer.
 * @param ptr_in [in] Adress from where the data will be copied.
 */
void cff_array_set(cff_array *array, uint64_t index, uintptr_t ptr_in);

/**
 * @ingroup Array
 * @brief Shifts all elements starting on index position to right and sets the value at index position to the value pointed by ptr_in.
 *
 * This function will copy the content at ptr_in adress to the location indicated by index.
 * Keep in mind that all elements on index position and after will be sihfted by one position to the right, it means that the value at the last index will be lost.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param index [in] Position of the data inside the array buffer.
 * @param ptr_in [in] Adress from where the data will be copied.
 */
void cff_array_insert(cff_array *array, uint64_t index, uintptr_t ptr_in);

/**
 * @ingroup Array
 * @brief Removes an element from array by shifting all elements starting on index position to the left.
 *
 * This function shifts all elements starting on index to the left, (eg. array[i] = array[i+1]).
 * If the index is equals to lenght - 1 (last element) the function just returns.
 * Keep in mind thet when an element (except at lenght - 1 ) is removed, there will exist two copies of the last element at the end of the array.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param index [in] Position of the data that will be removed.
 */
void cff_array_remove(cff_array *array, uint64_t index);

/**
 * @ingroup Array
 * @brief Sets every element of the array to an especific value.
 *
 * The content at ptr_in address will be replicated to every element of the array.
 * This function is similar to memset from libc.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Adress from where the data will be copied.
 */
void cff_array_fill(cff_array *array, uintptr_t ptr_in);

/**
 * @ingroup Array
 * @brief Iterates over the array and executes an callback to each element.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param foreach_function [in] Callback that will be called for every element.
 */
void cff_array_foreach(cff_array *array, foreach_fn foreach_function);

/**
 * @ingroup Array
 * @brief Releases the buffer allocated to this array.
 *
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_array_free(cff_array *array, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Allocates a buffer to the array and sets its fields properly.
 *
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 * The size of memory allocated is equals to data_size * lenght in bytes.
 * The memory allocated is NOT initialized.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param data_size [in] The size in bytes of each element.
 * @param lenght [in] The max number of elements the array will have.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_create(cff_array *array, uint64_t data_size, uint64_t lenght, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Reallocates the buffer owned by the array.
 *
 * The size of memory allocated is equals to data_size * lenght in bytes, notes that data_size is the value informed when cff_array_create is called.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param lenght [in] The new max number of elements the array will have.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_resize(cff_array *array, uint64_t lenght, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Copies a section of data from one array to other
 *
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_out [out] Pointer to an array that will receive the copy
 * @param start [in] Index from where the copy process will start
 * @param count [in] How many elements to copy from start.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_copy(cff_array *array, cff_array *ptr_out, uint64_t start, uint64_t count, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Copies all elements from one array to other
 *
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_out [out] Pointer to an array that will receive the copy
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_clone(cff_array *array, cff_array *ptr_out, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Copies the elements from "other" array to the array starting at the index given to start_at.
 *
 * If the lenght of "other" added to start_at is greater than array lenght the array will be resized.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param other [in] Pointer to an array to be joined to "array" from the position setted at start_at
 * @param start_at [in] Index where the first element of "other" will be copied and so on
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_join(cff_array *array, cff_array *other, uint64_t start_at, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Reverses the order of elements.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_reverse(cff_array *array);

/**
 * @ingroup Array
 * @brief Filters the elements of an array and puts the result on other.
 *
 * Creates a new array based on an existing one, the elements of the new array must complies the filter_function criteria.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param filter_function [in] Callback that determines if the element complies the criteria for the new array.
 * @param ptr_out [out] Pointer to the array that will receive the filtered elements.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_filter(cff_array *array, filter_fn filter_function, cff_array *ptr_out, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Transforms the elements of an array and puts the result on other.
 *
 * Creates a new array based on an existing one, the elements of the new array will be the result from map_function when called passed an element from array in the parameters.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param map_function [in] Callback that defines how to transform from one type to other.
 * @param ptr_out [out] Pointer to the array that will receive the mapped elements.
 * @param out_data_size [in] The size in bytes of the target type.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_map(cff_array *array, map_fn map_function, cff_array *ptr_out, uint64_t out_data_size, AllocatorInterface *allocator);

/**
 * @ingroup Array
 * @brief Order the elements using the quick sort algorithm.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_array_sort(cff_array *array, comparer_fn comparer_function);

/**
 * @ingroup Array
 * @brief Checks if the elements in both arrays are equals and with same order.
 *
 * @param array [in] Pointer to an array.
 * @param other [in] Pointer to other array.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_array_equal(cff_array *array, cff_array *other);

/**
 * @ingroup Array
 * @brief Gets the index of the first ocurrency of the value pointed by ptr_in in array.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to find in the array.
 * @param out_index [out] Receives the index where the value was found. If not found the value at its adress will not change.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_array_find(cff_array *array, uintptr_t ptr_in, uint64_t *out_index);

/**
 * @ingroup Array
 * @brief Gets the index of the first ocurrency of the value pointed by ptr_in in array.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to be find in the array.
 * @param out_index [out] Receives the index where the value was found. If not found the value at its adress will not change.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_array_find_cmp(cff_array *array, uintptr_t ptr_in, uint64_t *out_index, comparer_fn comparer_function);

/**
 * @ingroup Array
 * @brief Counts the number of ocurrencies of elements equals to value pointed by ptr_in.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to be count in the array.
 * @return uint64_t The number of ocurrencies of elements equals to value pointed by ptr_in.
 */
uint64_t cff_array_count(cff_array *array, uintptr_t ptr_in);

/**
 * @ingroup Array
 * @brief Counts the number of ocurrencies of elements equals to value pointed by ptr_in.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to be count in the array.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint64_t The number of ocurrencies of elements equals to value pointed by ptr_in.
 */
uint64_t cff_array_count_cmp(cff_array *array, uintptr_t ptr_in, comparer_fn comparer_function);

/**
 * @ingroup Array
 * @brief Checks the ocurrency of value pointed by ptr_in on the array.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to be find in the array.
 * @return uint8_t Retuns 1 if there is at least one ocurrency, otherwise returns 0.
 */
uint8_t cff_array_any(cff_array *array, uintptr_t ptr_in);

/**
 * @ingroup Array
 * @brief Checks the ocurrency of value pointed by ptr_in on the array.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to be find in the array.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint8_t Retuns 1 if there is at least one ocurrency, otherwise returns 0.
 */
uint8_t cff_array_any_cmp(cff_array *array, uintptr_t ptr_in, comparer_fn comparer_function);

/**
 * @ingroup Array
 * @brief Checks if all array elements are equals to value pointed by ptr_in.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to be find in the array.
 * @return uint8_t Retuns 1 if all elements are equal to value pointed by ptr_in, otherwise returns 0.
 */
uint8_t cff_array_all(cff_array *array, uintptr_t ptr_in);

/**
 * @ingroup Array
 * @brief Checks if all array elements are equals to value pointed by ptr_in.
 *
 * @param array [in] Pointer to the array wich owns the data.
 * @param ptr_in [in] Pointer to data to be find in the array.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint8_t Retuns 1 if all elements are equal to value pointed by ptr_in, otherwise returns 0.
 */
uint8_t cff_array_all_cmp(cff_array *array, uintptr_t ptr_in, comparer_fn comparer_function);

#endif // !CAFFEINE_ARRAY_H
