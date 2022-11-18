#ifndef CAFFEINE_SPARSE_SET
#define CAFFEINE_SPARSE_SET

#include "caffeine_core.h"
#include "caffeine_types.h"
#include "caffeine_memory.h"

struct caffeine_sparse_set
{
	uintptr_t dense;
	uint64_t* dense_index;
	uint64_t* sparse;
	uint64_t lenght;
	uint64_t count;
	uint64_t data_size;
};

typedef struct caffeine_sparse_set cff_sparseset;

void cff_sparseset_create(cff_sparseset* set, uint64_t lenght, uint64_t data_size, AllocatorInterface* allocator);
void cff_sparseset_add(cff_sparseset* set, uint64_t index, uintptr_t data, AllocatorInterface* allocator);
void cff_sparseset_get(cff_sparseset* set, uint64_t index, uintptr_t data);
void cff_sparseset_remove(cff_sparseset* set, uint64_t index);
void cff_sparseset_clear(cff_sparseset* set);
void cff_sparseset_free(cff_sparseset* set, AllocatorInterface* allocator);
uintptr_t cff_sparseset_get_dense(cff_sparseset* set);
#endif // !CAFFEINE_SPARSE_SET
