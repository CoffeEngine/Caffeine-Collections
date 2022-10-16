#ifndef CAFFEINE_BITMAP_H
#define CAFFEINE_BITMAP_H

#include "caffeine_core.h"

struct caffeine_bitmap_s
{
	uint64_t* buffer;
	uint64_t lenght;
};

typedef struct caffeine_bitmap_s cff_bitmap;

void caffeine_bitmap_create(cff_bitmap* bmp, uint64_t lenght, AllocatorInterface* allocator);
void caffeine_bitmap_set(cff_bitmap* bmp, uint64_t bit);
void caffeine_bitmap_clear(cff_bitmap* bmp, uint64_t bit);
void caffeine_bitmap_set_all(cff_bitmap* bmp);
void caffeine_bitmap_clear_all(cff_bitmap* bmp);
void caffeine_bitmap_resize(cff_bitmap* bmp, uint64_t lenght, AllocatorInterface* allocator);
void caffeine_bitmap_free(cff_bitmap* bmp, AllocatorInterface* allocator);
uint8_t caffeine_bitmap_get(cff_bitmap* bmp, uint64_t bit);



#endif // !CAFFEINE_BITMAP_H