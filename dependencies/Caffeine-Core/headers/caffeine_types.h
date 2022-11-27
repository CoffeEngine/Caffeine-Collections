/** @defgroup Types
 	@file caffeine_types.h
	@brief Defines common types used by the caffeine libraries.

*/

#ifndef CAFFEINE_TYPES_H
#define CAFFEINE_TYPES_H

/** 
 * @ingroup Types
 * @enum cff_comparer_value_e
*  @brief An Enum that represents a comparation betwen two values.
*
*/
enum cff_comparer_value_e {
	CFF_NOT_EQUAL = -2, ///<  The values are not equals and does not have any ordering relation
	CFF_LESS = -1, ///<  The value is smaller than its comparison
	CFF_EQUALS = 0, ///<  The values are equals
	CFF_GREATER = 1, ///<  The value is greater than its comparison
};

/** 
 * @ingroup Types
 * @enum cff_error_value_e
*	@brief An Enum that represents a caffeine error.
*   
*/
enum cff_error_value_e {
	CFF_NONE_ERR = 0, ///<  Any error ocurred 
	CFF_ALLOC_ERR, ///< A request for memory allocation returned NULL
	CFF_REALLOC_ERR, ///< A request for memory reallocation returned NULL
};

/** 
 * @ingroup Types
 * @typedef typedef enum cff_comparer_value_e cff_cmp_e
*	@brief A syntax sugar for enum cff_comparer_value_e.
*
*/
typedef enum cff_comparer_value_e cff_cmp_e;

/** 
 * @ingroup Types
 * @typedef typedef enum cff_error_value_e cff_err_e
*	@brief A syntax sugar for enum cff_error_value_e.
*
*/
typedef enum cff_error_value_e cff_err_e;

/**
*   @ingroup Types
*	@brief A callback type for value comparison.
*	
*	This callback is usefull to standardize a generic value comparison routine.
* 
*   @param [in] a_ptr pointer for a value
*   @param [in] b_ptr pointer for a value
*   @param [in] data_size the size of the two values
*	@return an cff_cmp_e that represents the comparison betwen the values
*/
typedef cff_cmp_e(*comparer_fn)(const void* const a_ptr, const void* const b_ptr, uint64_t data_size);

/** 
*   @ingroup Types
*	@brief A callback type for collection filtering.
*
*	This callback is usefull to standardize a generic collection filtering routine.
* 
*   @param [in] data_ptr pointer for a value that will be analyzed
*   @param [in] index the index of the value inside the collection
*   @param [in] data_size the size of the value
*   @return a boolean that indicates if the current value passed in the filter
*/
typedef bool (*filter_fn)(const void* const data_ptr, uint64_t index, uint64_t data_size);

/** 
*   @ingroup Types
*	@brief A callback type for collection transformation.
*
*	This callback is usefull to standardize a generic collection transformation routine.
* 
*   @param [in] from_ptr pointer for an initial value before transformation
*   @param [out] to_ptr pointer for a memory block that will receive the transformation result
*   @param [in] index the index of the value inside the collection
*/
typedef void(*map_fn)(const void* const from_ptr, void* to_ptr, uint64_t index);

/**
*   @ingroup Types
*	@brief A callback type for collection transformation.
*
*	This callback is usefull to standardize a generic routine that will be run
*	to every collection element.
*
*   @param [in,out] data_ptr pointer for a value that will be used
*   @param [in] index the index of the value inside an collection
*/
typedef void(*foreach_fn)(void* data_ptr, uint64_t index);



#endif