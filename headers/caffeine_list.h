#ifndef CAFFEINE_LIST_H
#define CAFFEINE_LIST_H

/**
 * @defgroup List
 * @file caffeine_list.h
 * @author Ruan Azevedo
 * @brief 
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caffeine_core.h"
#include "caffeine_types.h"
#include "caffeine_assertions.h"

/**
 * @ingroup List
 * @struct caffeine_list_bucket_t;
 * @brief Wrapper arround the element to make the reference chain.
 * 
 */
struct caffeine_list_bucket_t {
	/**
	 * @brief Pointer to the next bucket.
	 * 
	 */
	struct caffeine_list_bucket_t* next_bucket;

	/**
	 * @brief Pointer to bucket data.
	 * 
	 */
	uintptr_t data_ptr;
};

/**
 * @ingroup List
 * @typedef struct caffeine_list_bucket_t caffeine_list_bucket
 * @brief Syntax sugar for struct caffeine_list_bucket_t.
 * 
 */
typedef struct caffeine_list_bucket_t caffeine_list_bucket;

/**
 * @ingroup List
 * @struct caffeine_list_t
 * @brief A struct that keeps its elements by reference chain betwen them, this feature leads to slow data acess but fast insertion/deletion
 * 
 */
struct caffeine_list_t
{
	/**
	 * @brief Size in bytes of each element.
	 * 
	 */
	uint64_t data_size;
	/**
	 * @brief How many elements the list contains
	 * 
	 */
	uint64_t count;
	/**
	 * @brief Pointer to the first element.
	 * 
	 */
	caffeine_list_bucket* list_start;
	/**
	 * @brief Pointer to the last element.
	 * 
	 */
	caffeine_list_bucket* list_end;
};

/**
 * @ingroup List
 * @typedef struct caffeine_list_t cff_list
 * @brief Syntax sugar for struct caffeine_list_t.
 * 
 */
typedef struct caffeine_list_t cff_list;

/**
 * @ingroup List
 * @brief Allocates a buffer to the list and sets its fields properly.
 * 
 * @param list [in] Pointer to a list.
 * @param data_size [in] The size in bytes of each element.
 */
void cff_list_create(cff_list* list, uint64_t data_size);

/**
 * @ingroup List
 * @brief Sets the value at index position to the value pointed by ptr_in.
 *
 * This function will copy the content at ptr_in adress to the location indicated by index.
 * Keep in mind that the current value present at index position will be overwrited.
 * 
 * @param list [in] Pointer to a list.
 * @param index [in] Position of the data inside the list.
 * @param data [in] Adress from where the data will be copied.
 */
void cff_list_set(cff_list* list, uint64_t index, uintptr_t data);

/**
 * @ingroup List
 * @brief Gets the value at a give index.
 * 
 * @param list [in] Pointer to a list.
 * @param index [in] Position of the data inside the list.
 * @param data_out [out] Adress where the data will be copied.
 */
void cff_list_get(cff_list* list, uint64_t index, uintptr_t data_out);

/**
 * @ingroup List
 * @brief Get the first element of the list.
 * 
 * @param list [in] Pointer to a list.
 * @param data_out [out] Adress where the data will be copied.
 */
void cff_list_first(cff_list* list, uintptr_t data_out);

/**
 * @ingroup List
 * @brief Get the last element of the list.
 * 
 * @param list [in] Pointer to a list.
 * @param data_out [out] Adress where the data will be copied.
 */
void cff_list_last(cff_list* list, uintptr_t data_out);

/**
 * @ingroup List
 * @brief Removes an element from list.
 * 
 * @param list [in] Pointer to a list.
 * @param index [in] Position of the data inside the list.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_list_remove(cff_list* list, uint64_t index, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Reverses the order of elements.
 * 
 * @param list [in] Pointer to a list.
 */
void cff_list_reverse(cff_list* list);

/**
 * @ingroup List
 * @brief Removes all elements from the list.
 * 
 * @param list [in] Pointer to a list.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_list_clear(cff_list* list, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Links the first element of other at last element of list
 * 
 * @param list [in] Pointer to a list.
 * @param other [in] Pointer to another list.
 */
void cff_list_join(cff_list* list, cff_list* other);

/**
 * @ingroup List
 * @brief Order the elements using the merge sort algorithm.
 * 
 * @param list [in] Pointer to a list.
 * @param comparer_function [in] Callback used to compare the elements.
 */
void cff_list_sort(cff_list* list, comparer_fn comparer_function);

/**
 * @ingroup List
 * @brief Iterates over the list and executes an callback to each element.
 * 
 * @param list [in] Pointer to a list.
 * @param foreach_function [in] Callback that will be called for every element.
 */
void cff_list_foreach(cff_list* list, foreach_fn foreach_function);

/**
 * @ingroup List
 * @brief Adds an element at the end of the list.
 * 
 * @param list [in] Pointer to a list.
 * @param data [in] Adress from where the data will be copied.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_list_add(cff_list* list, uintptr_t data, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Insert an element at and especific position.
 * 
 * @param list [in] Pointer to a list.
 * @param index [in] Position of the data inside the list.
 * @param data [in] Adress from where the data will be copied.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_list_insert(cff_list* list, uint64_t index, uintptr_t data, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Copies all elements from one list to other
 * 
 * @param list [in] Pointer to a list.
 * @param other [out] Pointer to an list that will receive the copy
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_list_clone(cff_list* list, cff_list* other, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Copies a section of data from one list to other.
 * 
 * @param list [in] Pointer to a list.
 * @param other [out] Pointer to an list that will receive the copy
 * @param start [in] Index from where the copy process will start
 * @param count [in] How many elements to copy from start.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_list_copy(cff_list* list, cff_list* other, uint64_t start, uint64_t count, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Filters the elements of an list and puts the result on other.
 * 
 * Creates a new list based on an existing one, the elements of the new list must complies the filter_function criteria.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 *
 * @param list [in] Pointer to a list.
 * @param filter_function [in] Callback that will be called for every element.
 * @param ptr_out 
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_list_filter(cff_list* list, filter_fn filter_function, cff_list* ptr_out, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Transforms the elements of an list and puts the result on other.
 
 * Creates a new list based on an existing one, the elements of the new list will be the result from map_function when called passed an element from list in the parameters.
 * If the allocator parameter is NULL this function will get the default allocator setted in Caffeine-Core library.
 * 
 * @param list [in] Pointer to a list.
 * @param map_function [in] Callback that defines how to transform from one type to other.
 * @param ptr_out [out] Pointer to the list that will receive the mapped elements.
 * @param out_data_size [in] The size in bytes of the target type.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_list_map(cff_list* list, map_fn map_function, cff_list* ptr_out, uint64_t out_data_size, AllocatorInterface* allocator);

/**
 * @ingroup List
 * @brief Checks if the elements in both arrays are equals and with same order.
 * 
 * @param list [in] Pointer to a list.
 * @param other [in] Pointer to other list.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_list_equal(cff_list* list, cff_list* other);

/**
 * @ingroup List
 * @brief Checks if the elements in both arrays are equals and with same order.
 * 
 * @param list [in] Pointer to a list.
 * @param other [in] Pointer to other list.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_list_equal_cmp(cff_list* list, cff_list* other, comparer_fn comparer_function);

/**
 * @ingroup List
 * @brief Gets the index of the first ocurrency of the value pointed by data_f in list.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to find in the list.
 * @param out_index [out] Receives the index where the value was found. If not found the value at its adress will not change.
 * @param data_out [out] Adress where the data will be copied.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_list_find(cff_list* list, uintptr_t data_f,uint64_t* out_index, uintptr_t data_out);

/**
 * @ingroup List
 * @brief Gets the index of the first ocurrency of the value pointed by data_f in list.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to find in the list.
 * @param out_index [out] Receives the index where the value was found. If not found the value at its adress will not change.
 * @param data_out [out] Adress where the data will be copied.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint8_t Returns 0 if false and 1 if true.
 */
uint8_t cff_list_find_cmp(cff_list* list, uintptr_t data_f, uint64_t* out_index, uintptr_t data_out, comparer_fn comparer_function);

/**
 * @ingroup List
 * @brief Checks the ocurrency of value pointed by data_f on the list.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to find in the list.
 * @return uint8_t uint8_t Retuns 1 if there is at least one ocurrency, otherwise returns 0.
 */
uint8_t cff_list_any(cff_list* list, uintptr_t data_f);

/**
 * @ingroup List
 * @brief Checks the ocurrency of value pointed by data_f on the list.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to find in the list.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint8_t uint8_t Retuns 1 if there is at least one ocurrency, otherwise returns 0.
 */
uint8_t cff_list_any_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function);

/**
 * @ingroup List
 * @brief Checks if all list elements are equals to value pointed by data_f.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to find in the list.
 * @return uint8_t Retuns 1 if all elements are equal to value pointed by data_f, otherwise returns 0.
 */
uint8_t cff_list_all(cff_list* list, uintptr_t data_f);

/**
 * @ingroup List
 * @brief Checks if all list elements are equals to value pointed by data_f.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to find in the list.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint8_t Retuns 1 if all elements are equal to value pointed by data_f, otherwise returns 0.
 */
uint8_t cff_list_all_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function);

/**
 * @ingroup List
 * @brief Counts the number of ocurrencies of elements equals to value pointed by data_f.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to be count in the list.
 * @return uint64_t The number of ocurrencies of elements equals to value pointed by ptr_in.
 */
uint64_t cff_list_count(cff_list* list, uintptr_t data_f);

/**
 * @ingroup List
 * @brief  Counts the number of ocurrencies of elements equals to value pointed by data_f.
 * 
 * @param list [in] Pointer to a list.
 * @param data_f [in] Pointer to data to be count in the list.
 * @param comparer_function [in] Callback used to compare the elements.
 * @return uint64_t The number of ocurrencies of elements equals to value pointed by ptr_in.
 */
uint64_t cff_list_count_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function);

#endif