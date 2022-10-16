#include "caffeine_bitmap.h"
#include "caffeine_default_allocator.h"
#include "caffeine_memory.h"
#include "caffeine_assertions.h"


void caffeine_bitmap_create(cff_bitmap* bmp, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_zero(lenght);
	
	if (allocator == NULL) allocator = cff_default_allocator_get();

	size_t buff_size = sizeof(uint64_t) * (((size_t)lenght) / sizeof(uint64_t) * 8);
	if (buff_size == 0) buff_size = 1;

	bmp->buffer = (uint64_t*)cff_allocator_alloc(allocator,buff_size * sizeof(uint64_t), 8);
	bmp->lenght = lenght;
	caffeine_bitmap_clear_all(bmp);
}

void caffeine_bitmap_set(cff_bitmap* bmp, uint64_t bit) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_null(bmp->buffer);
	cff_assert_param_less(bit, bmp->lenght);
	

	uint64_t index = bit / ((uint64_t)sizeof(uint64_t) * 8);
	uint64_t pos = bit % ((uint64_t)sizeof(uint64_t) * 8);
	uint64_t v = ((uint64_t)1) << pos;
	bmp->buffer[index] |= v;
}

void caffeine_bitmap_clear(cff_bitmap* bmp, uint64_t bit) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_null(bmp->buffer);
	cff_assert_param_less(bit, bmp->lenght);
	

	uint64_t index = bit / ((uint64_t)sizeof(uint64_t) * 8);
	uint64_t pos = bit % ((uint64_t)sizeof(uint64_t) * 8);

	bmp->buffer[index] &= ~((uint64_t)1 << pos);
}

uint8_t caffeine_bitmap_get(cff_bitmap* bmp, uint64_t bit) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_null(bmp->buffer);
	cff_assert_param_less(bit, bmp->lenght);
	
	uint64_t index = bit / ((uint64_t)sizeof(uint64_t) * 8);
	uint64_t pos = bit % ((uint64_t)sizeof(uint64_t) * 8);
	uint64_t value = ((uint64_t)1 << pos);
	uint64_t logic = bmp->buffer[index] & value;
	uint8_t ret = logic != 0;
	return ret;
}

void caffeine_bitmap_set_all(cff_bitmap* bmp) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_null(bmp->buffer);

	size_t buff_size = sizeof(uint64_t) * (((size_t)bmp->lenght) / sizeof(uint64_t) * 8);
	if (buff_size == 0) buff_size = 1;

	for (size_t i = 0; i < buff_size; i++)
	{
		bmp->buffer[i] = UINT64_MAX;
	}
}

void caffeine_bitmap_clear_all(cff_bitmap* bmp) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_null(bmp->buffer);

	for (size_t i = 0; i < bmp->lenght; i++)
	{
		uint64_t index = i / ((uint64_t)sizeof(uint64_t) * 8);
		uint64_t pos = i % ((uint64_t)sizeof(uint64_t) * 8);

		bmp->buffer[index] = 0;
	}

}

void caffeine_bitmap_resize(cff_bitmap* bmp, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_null(bmp->buffer);
	cff_assert_param_not_zero(lenght);

	if (allocator == NULL) allocator = cff_default_allocator_get();

	uint64_t* tmp = NULL;
	size_t buff_size = sizeof(uint64_t) * ((size_t)(lenght) / sizeof(uint64_t) * 8);
	if (buff_size == 0) buff_size = 1;

	if (cff_allocator_realloc(allocator, bmp->buffer, buff_size, 8, &tmp)) {
		bmp->buffer = tmp;
		bmp->lenght = lenght;
	}
}

void caffeine_bitmap_free(cff_bitmap* bmp, AllocatorInterface* allocator) {
	cff_assert_param_not_null(bmp);
	cff_assert_param_not_null(bmp->buffer);

	if (allocator == NULL) allocator = cff_default_allocator_get();

	cff_allocator_free(allocator, bmp->buffer, 8);
	bmp->buffer = 0;
	bmp->lenght = 0;
}