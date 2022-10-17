#ifndef CAFFEINE_SPARSE_SET
#define CAFFEINE_SPARSE_SET

#include "caffeine_core.h"
#include "caffeine_allocator_interface.h"

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

cff_err_e caffeine_sparseset_create(cff_sparseset* set, uint64_t lenght, uint64_t data_size, AllocatorInterface* allocator);
cff_err_e caffeine_sparseset_add(cff_sparseset* set, uint64_t index, uintptr_t data, AllocatorInterface* allocator);
void caffeine_sparseset_get(cff_sparseset* set, uint64_t index, uintptr_t data);
void caffeine_sparseset_remove(cff_sparseset* set, uint64_t index);
void caffeine_sparseset_clear(cff_sparseset* set);
void caffeine_sparseset_free(cff_sparseset* set, AllocatorInterface* allocator);
uintptr_t caffeine_sparseset_get_dense(cff_sparseset* set);
#endif // !CAFFEINE_SPARSE_SET
