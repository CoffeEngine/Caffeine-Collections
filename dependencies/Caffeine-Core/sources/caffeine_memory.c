#include "caffeine_assertions.h"
#include "caffeine_memory.h"

#ifdef CFF_COMP_MSVC

//HEAP ALLOCATOR
void* cff_heap_alloc(size_t size) {
	cff_assert_param_not_zero(size);

	void* ptr = malloc(size);
	return ptr;
}

int cff_heap_realloc(void* ptr, size_t size, void** out) {
	cff_assert_param_not_null(ptr);
	cff_assert_param_not_null(out);
	cff_assert_param_not_zero(size);

	void* tmp = realloc(ptr, size);

	if (tmp != NULL) {
		*out = tmp;
		return 1;
	}
	*out = NULL;
	return 0;
}

void cff_heap_alloc_free(void* ptr) {

	if (ptr != NULL) free(ptr);
}

//STACK ALLOCATOR
void* cff_stack_alloc(size_t size) {
	cff_assert_param_not_zero(size);

	void* ptr = _malloca(size);
	return ptr;
}

int cff_stack_realloc(void* ptr, size_t old_size, size_t size, void** out) {
	cff_assert_param_not_null(ptr);
	cff_assert_param_not_null(out);
	cff_assert_param_not_zero(size);
	cff_assert_param_not_zero(old_size);

	void* n_ptr = _malloca(size);
	if (n_ptr != NULL) {
		cff_memcpy(ptr, n_ptr, old_size, size);
		_freea(ptr);
		*out = n_ptr;
		return 1;
	}
	return 0;
}

void cff_stack_alloc_free(void* ptr) {
	if (ptr != NULL) _freea(ptr);
}


size_t cff_mem_size(void* ptr) {
	cff_assert_param_not_null(ptr);

	return _msize(ptr);
}

#endif // CFF_COMP == MSVC

#ifdef CFF_COMP_GCC

#include <alloca.h>

//HEAP ALLOCATOR
void* cff_heap_alloc(size_t size) {
	cff_assert_param_not_zero(size);

	void* ptr = malloc(size);
	return ptr;
}

int cff_heap_realloc(void* ptr, size_t size, void** out) {
	cff_assert_param_not_null(ptr);
	cff_assert_param_not_null(out);
	cff_assert_param_not_zero(size);

	void* tmp = realloc(ptr, size);

	if (tmp != NULL) {
		*out = tmp;
		return 1;
	}
	*out = NULL;
	return 0;
}

void cff_heap_alloc_free(void* ptr) {

	if (ptr != NULL) free(ptr);
}

//STACK ALLOCATOR
void* cff_stack_alloc(size_t size) {
	cff_assert_param_not_zero(size);

	void* ptr = alloca(size);
	return ptr;
}

int cff_stack_realloc(void* ptr, size_t old_size, size_t size, void** out) {
	cff_assert_param_not_null(ptr);
	cff_assert_param_not_null(out);
	cff_assert_param_not_zero(size);
	cff_assert_param_not_zero(old_size);

	void* n_ptr = alloca(size);
	if (n_ptr != NULL) {
		cff_memcpy(ptr, n_ptr, old_size, size);
		*out = n_ptr;
		return 1;
	}
	return 0;
}

void cff_stack_alloc_free(void* ptr) {
	
}


size_t cff_mem_size(void* ptr) {
	cff_assert_param_not_null(ptr);

#ifdef ISUNIX

	return malloc_usable_size(ptr);
#else // ISUNIX
#error Function unavailable for this system.
#endif	
	
	return 0;
}


#endif // CFF_COMP == GCC

int cff_memcmp(const void* a, const void* b, size_t size) {
	cff_assert_param_not_null(a);
	cff_assert_param_not_null(b);
	cff_assert_param_not_zero(size);

	return memcmp(a, b, size);
}

void cff_memcpy(const void* const src, void* const dest, size_t src_size, size_t dest_size) {
	cff_assert_param_not_null(src);
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(src_size);
	cff_assert_param_not_zero(dest_size);

	#ifdef CFF_COMP_MSVC
	memcpy_s(dest, dest_size, src, src_size);
	#endif

	#ifdef CFF_COMP_GCC
	memcpy(dest,src,src_size);
	#endif
}

void cff_memmove(const void* const src, void* const dest, size_t src_size, size_t dest_size) {
	cff_assert_param_not_null(src);
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(src_size);
	cff_assert_param_not_zero(dest_size);

	#ifdef CFF_COMP_MSVC
	memmove_s(dest, dest_size, src, src_size);
	#endif

	#ifdef CFF_COMP_GCC
	memmove(dest,src,src_size);
	#endif
}

void cff_memset(void* dest, int value, size_t size) {
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	memset(dest, value, size);
}


int cff_memcmp_8(const void* const a, const void* const b, size_t size) {
	cff_assert_param_not_null(a);
	cff_assert_param_not_null(b);
	cff_assert_param_not_zero(size);

	const char* tmp_a = (const char*)a;
	const char* tmp_b = (const char*)b;

	for (size_t i = 0; i < size; i += sizeof(char))
	{
		if (*tmp_a++ != *tmp_b++) return 1;
	}
	return 0;
}

int cff_memcmp_16(const void* const a, const void* const b, size_t size) {
	cff_assert_param_not_null(a);
	cff_assert_param_not_null(b);
	cff_assert_param_not_zero(size);

	const short* tmp_a = (const short*)a;
	const short* tmp_b = (const short*)b;

	for (size_t i = 0; i < size; i += sizeof(short))
	{
		if (*tmp_a++ != *tmp_b++) return 1;
	}
	return 0;
}

int cff_memcmp_32(const void* const a, const void* const b, size_t size) {
	cff_assert_param_not_null(a);
	cff_assert_param_not_null(b);
	cff_assert_param_not_zero(size);

	const int* tmp_a = (const int*)a;
	const int* tmp_b = (const int*)b;

	for (size_t i = 0; i < size; i += sizeof(int))
	{
		if (*tmp_a++ != *tmp_b++) return 1;
	}
	return 0;
}

int cff_memcmp_64(const void* const a, const void* const b, size_t size) {
	cff_assert_param_not_null(a);
	cff_assert_param_not_null(b);
	cff_assert_param_not_zero(size);

	const long long int* tmp_a = (const long long int*)a;
	const long long int* tmp_b = (const long long int*)b;

	for (size_t i = 0; i < size; i += sizeof(long long int))
	{
		if (*tmp_a++ != *tmp_b++) return 1;
	}
	return 0;
}


void cff_memcpy_8(const void* const src, void* const dest, size_t size) {
	cff_assert_param_not_null(src);
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	const char* tmp_src = (const char*)src;
	char* tmp_dest = (char*)dest;

	for (size_t i = 0; i < size; i += sizeof(char))
	{
		*tmp_dest++ = *tmp_src++;
	}
}

void cff_memcpy_16(const void* const src, void* const dest, size_t size) {
	cff_assert_param_not_null(src);
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	const short* tmp_src = (const short*)src;
	short* tmp_dest = (short*)dest;

	for (size_t i = 0; i < size; i += sizeof(short))
	{
		*tmp_dest++ = *tmp_src++;
	}
}

void cff_memcpy_32(const void* const src, void* const dest, size_t size) {
	cff_assert_param_not_null(src);
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	const int* tmp_src = (const int*)src;
	int* tmp_dest = (int*)dest;

	for (size_t i = 0; i < size; i += sizeof(int))
	{
		*tmp_dest++ = *tmp_src++;
	}
}

void cff_memcpy_64(const void* const src, void* const dest, size_t size) {
	cff_assert_param_not_null(src);
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	const long long int* tmp_src = (const long long int*)src;
	long long int* tmp_dest = (long long int*)dest;

	for (size_t i = 0; i < size; i += sizeof(long long int))
	{
		*tmp_dest++ = *tmp_src++;
	}
}


void cff_memset_8(void* const dest, char value, size_t size) {
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	char* tmp_dest = (char*)dest;

	for (size_t i = 0; i < size; i += sizeof(char))
	{
		*tmp_dest++ = value;
	}
}

void cff_memset_16(void* const dest, short value, size_t size) {
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	short* tmp_dest = (short*)dest;

	for (size_t i = 0; i < size; i += sizeof(short))
	{
		*tmp_dest++ = value;
	}
}

void cff_memset_32(void* const dest, int value, size_t size) {
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	int* tmp_dest = (int*)dest;

	for (size_t i = 0; i < size; i += sizeof(int))
	{
		*tmp_dest++ = value;
	}
}

void cff_memset_64(void* const dest, long long int value, size_t size) {
	cff_assert_param_not_null(dest);
	cff_assert_param_not_zero(size);

	long long int* tmp_dest = (long long int*)dest;

	for (size_t i = 0; i < size; i += sizeof(long long int))
	{
		*tmp_dest++ = value;
	}
}


void* cff_allocator_alloc(AllocatorInterface* allocator, size_t size) {
	cff_assert_param_not_null(allocator);
	cff_assert_param_not_zero(size);

	return	allocator->alloc(allocator->context, size);
}

int cff_allocator_realloc(AllocatorInterface* allocator, void* ptr, size_t size, void** out) {
	cff_assert_param_not_null(allocator);
	cff_assert_param_not_null(ptr);
	cff_assert_param_not_null(out);
	cff_assert_param_not_zero(size);

	void* tmp = allocator->realloc(allocator->context, ptr, size);
	if (tmp != NULL) {
		*out = tmp;
		return 1;
	}
	return 0;
}

void cff_allocator_free(AllocatorInterface* allocator, void* ptr) {
	cff_assert_param_not_null(allocator);
	cff_assert_param_not_null(ptr);
	if (ptr != NULL) {
		allocator->free(allocator->context, ptr);
		allocator->context = 0;
	}
}

size_t cff_allocator_mem_size(AllocatorInterface* allocator, void* ptr) {
	cff_assert_param_not_null(allocator);
	return allocator->get_size(allocator->context, ptr);
}