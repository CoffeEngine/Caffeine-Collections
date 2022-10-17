#include "caffeine_core.h"
#include "caffeine_default_allocator.h"
#include "caffeine_assertions.h"

static AllocatorInterface* _i_caffeine_default_allocator = NULL;

AllocatorInterface* caffeine_get_default_allocator() {
	if (_i_caffeine_default_allocator == NULL)  _i_caffeine_default_allocator = cff_default_allocator_get();
	cff_assert_param_not_null(_i_caffeine_default_allocator);
	return _i_caffeine_default_allocator;
}
void caffeine_set_default_allocator(AllocatorInterface* allocator) {
	_i_caffeine_default_allocator = allocator;
}