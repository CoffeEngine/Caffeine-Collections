/** @defgroup Memory
    @file caffeine_memory.h
	@brief Defines abstractions for common memory related functions.

	This module declares functions for dynamic memory management either on heap or stack, also defines
	an interface for custom memory allocators.
*/

#ifndef CAFFEINE_MEMORY_H
#define CAFFEINE_MEMORY_H

#include "caffeine_flags.h"

#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

/**
 * @ingroup Memory
 * @struct AllocatorInterface_s
 * @brief Defines an interface to standardize custom allocators implementation.
 * 
 */
struct AllocatorInterface_s
{

	/**
	 * @brief A function pointer to a memory allocation function.
	 * 
	 *  @param [in] context pointer for the context data needed by the allocator.
	 *  @param [in] size the size of memory block to be allocated in bytes.
	 *	@return a pointer to the allocated memory block or null in failure cases.
	 */
	void* (*alloc)(void* context, size_t size);

	/**
	 * @brief A function pointer to a memory reallocation function.
	 * 
	 *	@param [in] context pointer for the context data needed by the allocator.
	 * 	@param [in] ptr pointer to the memory block previusly allocated.
	 * 	@param [in] size the size of memory block to be allocated in bytes.
	 *	@return a pointer to the reallocated memory block or null in failure cases.
	 */
	void* (*realloc)(void* context, void* ptr, size_t size);

	/** 
	*	@brief A function pointer to a memory deallocation function.
	*
	*   @param [in] context pointer for the context data needed by the allocator.
	*   @param [in] ptr pointer to the memory block previusly allocated.
	*/
	void (*free)(void* context, void* ptr);

	/** 
	* @brief A function pointer to function that gets the size of an allocated block.
	*
	*	@param [in] context pointer for the context data needed by the allocator.
	*   @param [in] ptr pointer to the memory block previusly allocated.
	*	@return the size of the block in bytes.
	*/
	size_t(*get_size)(void* context, void* ptr);

	/**
	* @brief A pointer to any auxiliaty data needed by the allocator.
	*
	*  The purporse of this pointer is to keep track of a possible information that the allocator maybe need to know (eg. a linked list with allocated blocks).
	*  This pointer will be passed to every function defined by this interface.
	*/
	void* context;
};

/** 
 * @ingroup Memory
 * @typedef typedef struct AllocatorInterface_s AllocatorInterface.
 * @brief A syntax sugar for struct AllocatorInterface_s.
 *
 *	Defines an interface to standardize custom allocators implementation.
 */
typedef struct AllocatorInterface_s AllocatorInterface;


/**
* @ingroup Memory
* @fn void* cff_allocator_alloc(AllocatorInterface* allocator, size_t size)
* @brief A function to allocate memory using an AllocatorInterface.
*
*	This funcion calls the allocator alloc function passing the necessary parameters.
*
*	@param [in] allocator pointer to an AllocatorInterface.
*   @param [in] size the size of memory block to be allocated in bytes.
*	@return a pointer to the allocated memory block or null in failure cases.
*/
void* cff_allocator_alloc(AllocatorInterface* allocator, size_t size);

/** 
* @ingroup Memory
* @fn int cff_allocator_realloc(AllocatorInterface* allocator, void* ptr, size_t size, void** out)
* @brief A function to reallocate memory using an AllocatorInterface.
*
*	This funcion calls the allocator realloc function passing the necessary parameters.
*
*	@param [in] allocator pointer to an AllocatorInterface.
*	@param [in] ptr pointer to the block that will be reallocated.
*   @param [in] size the new size for the memory block in bytes.
*   @param [out] out pointer to the memory block after reallocated or to null in failure case.
*	@return 0 in failure case or 1 in sucess case.
*/
int cff_allocator_realloc(AllocatorInterface* allocator, void* ptr, size_t size, void** out);

/** 
* @ingroup Memory
* @fn void cff_allocator_free(AllocatorInterface* allocator, void* ptr )
* @brief A function to deallocate memory using an AllocatorInterface.
*
*	This funcion calls the allocator dealloc function passing the necessary parameters.
*
*	@param [in] allocator pointer to an AllocatorInterface.
*	@param [in] ptr pointer to the block that will be deallocated.
*/
void cff_allocator_free(AllocatorInterface* allocator, void* ptr);

/** 
* @ingroup Memory
* @fn size_t cff_allocator_mem_size(AllocatorInterface* allocator, void* ptr)
* @brief A function that gets the size of an allocated block.
*
*	This funcion calls the allocator get_size function passing the necessary parameters.
*
*	@param [in] allocator pointer to an AllocatorInterface.
*	@param [in] ptr pointer to the block.
*	@return the size of the block in bytes.
*/
size_t cff_allocator_mem_size(AllocatorInterface* allocator, void* ptr);

/** 
* @ingroup Memory
* @fn AllocatorInterface* cff_get_default_allocator()
* @brief Utility function that provides a pointer to the default memory allocator in the process.
*
*	By default this function will return a pointer to an allocator interface that uses the functions provided by the libc (eg. malloc, realloc and free).
*	The default allocator can be changed using the @fn cff_set_default_allocator function.
*
*	@return pointer to an AllocatorInterface.
*/
AllocatorInterface* cff_get_default_allocator();

/** 
* @ingroup Memory
* @fn void cff_set_default_allocator(AllocatorInterface* allocator)
* @brief Utility function that provides a pointer to the default memory allocator in the process.
*
*	By default this function will return a pointer to an allocator interface that uses the functions provided by the libc (eg. malloc, realloc and free).
*	The default allocator can be changed using the @fn cff_set_default_allocator function.
*
*	@return pointer to an AllocatorInterface.
*/
void cff_set_default_allocator(AllocatorInterface* allocator);

/** 
 * @ingroup Memory
 * @fn void* cff_heap_alloc(size_t size)
*	@brief Allocates a memory block using the libc malloc function.
*
*	@param [in] size the size of block to be allocated in bytes.
*	@return a pointer to the allocated memory block or null in failure cases.
*
*	 @warning The function called depends on the compiler used and target operating system.
*/
void* cff_heap_alloc(size_t size);

/** 
 * @ingroup Memory
 * @fn int cff_heap_realloc(void* ptr, size_t size, void** out)
*	@brief Reallocates a memory block using the libc realloc function.
*
*	@param [in] ptr pointer to the block that will be reallocated.
*   @param [in] size the new size for the memory block in bytes.
*   @param [out] out pointer to the memory block after reallocated or to null in failure case.
*	@return 0 in failure case or 1 in sucess case.
*
* @warning The function called depends on the compiler used and target operating system.
*/
int cff_heap_realloc(void* ptr, size_t size, void** out);

/** 
 * @ingroup Memory
 * @fn void cff_heap_alloc_free(void* ptr)
*	@brief Releases a memory block using the libc free function.
*
*	@param [in] ptr pointer to the block that will be deallocated.
*
* @warning The function called depends on the compiler used and target operating system.
*/
void cff_heap_alloc_free(void* ptr);

/** 
 * @ingroup Memory
 * @fn void* cff_stack_alloc(size_t size)
*	@brief Allocates a memory block on stack.
*
*	@param [in] size the size of block to be allocated in bytes.
*	@return a pointer to the allocated memory block or null in failure cases.
*
*	 @warning The function called depends on the compiler used and target operating system.
*/
void* cff_stack_alloc(size_t size);

/** 
 * @ingroup Memory
 * @fn int cff_stack_realloc(void* ptr, size_t old_size, size_t size, void** out)
*	@brief Reallocates a memory block on stack.
*
*	Internally, this function will allocate a new block on stack, copy the data from old block to the new and try to dealloc the old block,
*	be aware that some runtimes doesn't allow manually stack release, in such cases both memory blocks will be allocated until the end of scope.
*
*	@param [in] ptr pointer to the block that will be reallocated.
*   @param [in] size the new size for the memory block in bytes.
*   @param [out] out pointer to the memory block after reallocated or to null in failure case.
*	@return 0 in failure case or 1 in sucess case.
*
* @warning The function called depends on the compiler used and target operating system.
*/
int cff_stack_realloc(void* ptr, size_t old_size, size_t size, void** out);

/** 
 * @ingroup Memory
 * @fn void cff_stack_alloc_free(void* ptr)
*	@brief Releases a memory block on stack.
*
*	Be aware that some runtimes doesn't allow manually stack release, in such cases this function does nothing.
*
*	@param [in] ptr pointer to the block that will be deallocated.
*
* @warning The function called depends on the compiler used and target operating system.
*/
void cff_stack_alloc_free(void* ptr);

/** 
 * @ingroup Memory
 * @fn size_t cff_mem_size(void* ptr)
*	@brief A function that gets the size of an allocated block.
*
*	@param [in] ptr pointer to the block.
*	@return the size of the block in bytes.
*
* @warning The function called depends on the compiler used and target operating system.
*/
size_t cff_mem_size(void* ptr);

/** 
 * @ingroup Memory
 * @fn cff_memcmp(const void* a, const void* b, size_t size)
*	@brief Indicates if a sequence of bytes from two adress have the same value.
*
*	@param [in] a pointer to an adress.
*	@param [in] b pointer to an adress.
*	@param [in] size lenght of sequence to be compared.
*	@return 1 if are equals and 0 if not.
*/
int cff_memcmp(const void* a, const void* b, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memcpy(const void* const src, void* const dest, size_t src_size, size_t dest_size)
*	@brief Copy a sequence of bytes from src to dest.
*
*	If the dest and src buffers overlaps use the cff_memmove instead.
* 
*	@param [in] src pointer to the adress of the data to be copied.
*	@param [in] des pointer to the adress that will receive the copy.
*	@param [in] src_size lenght of bytes that will be copied.
*	@param [in] dest_size lenght of bytes of the block that will receive the copy.
*/
void cff_memcpy(const void* const src, void* const dest, size_t src_size, size_t dest_size);

/** 
 * @ingroup Memory
 * @fn void cff_memmove(const void* const src, void* const dest, size_t src_size, size_t dest_size)
*	@brief Moves a sequence of bytes from src to dest.
*
*	Better option when the src and dest buffer overlaps.
* 
*	@param [in] src pointer to the adress of the data to be copied.
*	@param [in] des pointer to the adress that will receive the copy.
*	@param [in] src_size lenght of bytes that will be copied.
*	@param [in] dest_size lenght of bytes of the block that will receive the copy.
*/
void cff_memmove(const void* const src, void* const dest, size_t src_size, size_t dest_size);

/** 
 * @ingroup Memory
 * @fn void cff_memset(void* dest, int value, size_t size)
*	@brief Sets all values of an memory block to a value.
*
*	@param [in] dest pointer to a memory block.
*	@param [in] value value to be setted in every byte of the block.
*	@param [in] size lenght of bytes to be setted.
*/
void cff_memset(void* dest, int value, size_t size);

/** 
 * @ingroup Memory
 * @fn int cff_memcmp_8(const void* const a, const void* const b, size_t size)
*	@brief Indicates if a sequence of bytes from two adress have the same value 8 bits at a time.
*
*	@param [in] a pointer to the adress of the data to be copied.
*	@param [in] b pointer to the adress that will receive the copy.
*	@param [in] size lenght of sequence to be compared.
*	@return 1 if are equals and 0 if not.
*/
int cff_memcmp_8(const void* const a, const void* const b, size_t size);

/** 
 * @ingroup Memory
 * @fn cff_memcmp_16(const void* const a, const void* const b, size_t size)
*	@brief Indicates if a sequence of bytes from two adress have the same value 16 bits at a time.
*
*	@param [in] a pointer to the adress of the data to be copied.
*	@param [in] b pointer to the adress that will receive the copy.
*	@param [in] size lenght of sequence to be compared.
*	@return 1 if are equals and 0 if not.
*/
int cff_memcmp_16(const void* const a, const void* const b, size_t size);

/** 
 * @ingroup Memory
 * @fn cff_memcmp_32(const void* const a, const void* const b, size_t size)
*	@brief Indicates if a sequence of bytes from two adress have the same value 32 bits at a time.
*
*	@param [in] a pointer to the adress of the data to be copied.
*	@param [in] b pointer to the adress that will receive the copy.
*	@param [in] size lenght of sequence to be compared.
*	@return 1 if are equals and 0 if not.
*/
int cff_memcmp_32(const void* const a, const void* const b, size_t size);

/** 
 * @ingroup Memory
 * @fn cff_memcmp_64(const void* const a, const void* const b, size_t size)
*	@brief Indicates if a sequence of bytes from two adress have the same value 64 bits at a time.
*
*	@param [in] a pointer to the adress of the data to be copied.
*	@param [in] b pointer to the adress that will receive the copy.
*	@param [in] size lenght of sequence to be compared.
*	@return 1 if are equals and 0 if not.
*/
int cff_memcmp_64(const void* const a, const void* const b, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memcpy_8(const void* const src, void* const dest, size_t size)
*	@brief Copy a sequence of bytes from src to dest 8 bits at a time.
*
*	If the dest and src buffers overlaps use the cff_memmove instead.
*
*	@param [in] src pointer to the adress of the data to be copied.
*	@param [in] des pointer to the adress that will receive the copy.
*	@param [in] size lenght of bytes that will be copied.
*/
void cff_memcpy_8(const void* const src, void* const dest, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memcpy_16(const void* const src, void* const dest, size_t size)
*	@brief Copy a sequence of bytes from src to dest 16 bits at a time.
*
*	If the dest and src buffers overlaps use the cff_memmove instead.
*
*	@param [in] src pointer to the adress of the data to be copied.
*	@param [in] des pointer to the adress that will receive the copy.
*	@param [in] size lenght of bytes that will be copied.
*/
void cff_memcpy_16(const void* const src, void* const dest, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memcpy_32(const void* const src, void* const dest, size_t size)
*	@brief Copy a sequence of bytes from src to dest 32 bits at a time.
*
*	If the dest and src buffers overlaps use the cff_memmove instead.
*
*	@param [in] src pointer to the adress of the data to be copied.
*	@param [in] des pointer to the adress that will receive the copy.
*	@param [in] size lenght of bytes that will be copied.
*/
void cff_memcpy_32(const void* const src, void* const dest, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memcpy_64(const void* const src, void* const dest, size_t size)
*	@brief Copy a sequence of bytes from src to dest 64 bits at a time.
*
*	If the dest and src buffers overlaps use the cff_memmove instead.
*
*	@param [in] src pointer to the adress of the data to be copied.
*	@param [in] des pointer to the adress that will receive the copy.
*	@param [in] size lenght of bytes that will be copied.
*/
void cff_memcpy_64(const void* const src, void* const dest, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memset_8(void* const dest, char value, size_t size)
*	@brief Sets all values of an memory block to a value 8 bits at a time.
*
*	@param [in] dest pointer to a memory block.
*	@param [in] value value to be setted in every byte of the block.
*	@param [in] size lenght of bytes to be setted.
*/
void cff_memset_8(void* const dest, char value, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memset_16(void* const dest, short value, size_t size)
*	@brief Sets all values of an memory block to a value 16 bits at a time.
*
*	@param [in] dest pointer to a memory block.
*	@param [in] value value to be setted in every byte of the block.
*	@param [in] size lenght of bytes to be setted.
*/
void cff_memset_16(void* const dest, short value, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memset_32(void* const dest, int value, size_t size)
*	@brief Sets all values of an memory block to a value 32 bits at a time.
*
*	@param [in] dest pointer to a memory block.
*	@param [in] value value to be setted in every byte of the block.
*	@param [in] size lenght of bytes to be setted.
*/
void cff_memset_32(void* const dest, int value, size_t size);

/** 
 * @ingroup Memory
 * @fn void cff_memset_64(void* const dest, long long int value, size_t size)
*	@brief Sets all values of an memory block to a value 64 bits at a time.
*
*	@param [in] dest pointer to a memory block.
*	@param [in] value value to be setted in every byte of the block.
*	@param [in] size lenght of bytes to be setted.
*/
void cff_memset_64(void* const dest, long long int value, size_t size);
#endif