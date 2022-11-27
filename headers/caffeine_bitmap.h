#ifndef CAFFEINE_BITMAP_H
#define CAFFEINE_BITMAP_H

/**
 * @defgroup Bitmap
 * @file caffeine_bitmap.h
 * @author Ruan Azevedo
 * @brief Provides a bitmap data structure
 * @version 0.1
 * @date 2022-11-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caffeine_core.h"

/**
 * @ingroup Bitmap
 * @struct caffeine_bitmap_s
 * @brief Provides a boolean array with less memory consumption
 * 
 * This structure works by flipping bits instead a whole byte.
 * 
 */
struct caffeine_bitmap_s
{
	/**
	 * @brief Buffer where the bits are stored 
	 * 
	 */
	uint64_t* buffer;
	/**
	 * @brief Tracks the number of bits in use.
	 * 
	 * Note that this value is different from the number of allocated bits which is generally a little higher.
	 * 
	 */
	uint64_t lenght;
};

/**
 * @ingroup Bitmap
 * @typedef struct caffeine_bitmap_s cff_bitmap
 * @brief Syntax sugar for truct caffeine_bitmap_s.
 * 
 */
typedef struct caffeine_bitmap_s cff_bitmap;

/**
 * @ingroup Bitmap
 * @brief Initializes the bitmap structure
 * 
 * @param bmp [in] Pointer to a bitmap.
 * @param lenght [in] Amount of bits desired.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_bitmap_create(cff_bitmap* bmp, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Bitmap
 * @brief Sets the bit to 1.
 * 
 * @param bmp [in] Pointer to a bitmap.
 * @param bit [in] Bit index.
 */
void cff_bitmap_set(cff_bitmap* bmp, uint64_t bit);

/**
 * @ingroup Bitmap
 * @brief Sets the bit to 0.
 * 
 * @param bmp [in] Pointer to a bitmap.
 * @param bit [in] Bit index.
 */
void cff_bitmap_clear(cff_bitmap* bmp, uint64_t bit);

/**
 * @ingroup Bitmap
 * @brief Sets all bits to 1.
 * 
 * @param bmp [in] Pointer to a bitmap.
 */
void cff_bitmap_set_all(cff_bitmap* bmp);

/**
 * @ingroup Bitmap
 * @brief Sets all bits to 0.
 * 
 * @param bmp [in] Pointer to a bitmap.
 */
void cff_bitmap_clear_all(cff_bitmap* bmp);

/**
 * @ingroup Bitmap
 * @brief Resizes the bitmap buffer.
 * 
 * This function reallocates the buffer who can have it's memory position changed.
 * If the new lenght requires a buffer with same size than current buffer the function just returns.
 * 
 * @param bmp [in] Pointer to a bitmap.
 * @param lenght [in] New lenght.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 * @return cff_err_e A cff_err_e indicating if any error ocurred.
 */
cff_err_e cff_bitmap_resize(cff_bitmap* bmp, uint64_t lenght, AllocatorInterface* allocator);

/**
 * @ingroup Bitmap
 * @brief Deallocates the bitmap buffer
 * 
 * @param bmp [in] Pointer to a bitmap.
 * @param allocator [in] Pointer to a custom allocator. If NULL is setted the function will use the default allocator from Caffeine-Core library.
 */
void cff_bitmap_free(cff_bitmap* bmp, AllocatorInterface* allocator);

/**
 * @ingroup Bitmap
 * @brief Gets the value of one bit.
 * 
 * @param bmp [in] Pointer to a bitmap.
 * @param bit [in] Bit index.
 * @return uint8_t The bit value.
 */
uint8_t cff_bitmap_get(cff_bitmap* bmp, uint64_t bit);



#endif // !CAFFEINE_BITMAP_H
