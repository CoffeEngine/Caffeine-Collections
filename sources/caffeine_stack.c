#include "caffeine_stack.h"
#include "caffeine_assertions.h"

void cff_stack_create(cff_stack* stack, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(stack);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_zero(data_size);

	cff_vector_create(stack, data_size, lenght, allocator);
}

void cff_stack_resize(cff_stack* stack, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(stack);
	cff_assert_param_not_zero(lenght);

	cff_vector_resize(stack, lenght, allocator);
}

void cff_stack_push(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator) {
	cff_assert_param_not_null(stack);
	cff_assert_param_not_null(data_ptr);
	
	cff_vector_push_back(stack, data_ptr, allocator);
}

void cff_stack_reverse(cff_stack* stack) {
	cff_assert_param_not_null(stack);

	cff_vector_reverse(stack);
}

void cff_stack_free(cff_stack* stack, AllocatorInterface* allocator) {
	cff_assert_param_not_null(stack);

	cff_vector_free(stack, allocator);
}

void cff_stack_clear(cff_stack* stack) {
	cff_assert_param_not_null(stack);

	cff_vector_clear(stack);
}

void cff_stack_copy(cff_stack* stack, cff_stack* to, uint64_t start, uint64_t count, AllocatorInterface* allocator) {
	cff_assert_param_not_null(stack);
	cff_assert_param_not_null(to);
	cff_assert_param_less((start + count), stack->lenght);


	cff_vector_copy(stack, to, start, count, allocator);
}

void cff_stack_clone(cff_stack* stack, cff_stack* to, AllocatorInterface* allocator) {
	cff_assert_param_not_null(stack);
	cff_assert_param_not_null(to);

	cff_vector_clone(stack, to, allocator);
}

uint8_t cff_stack_pop(cff_stack* stack, uintptr_t data_ptr, AllocatorInterface* allocator) {
	cff_assert_param_not_null(stack);
	cff_assert_param_not_null(data_ptr);

	if (stack->count == 0) return 0;
	cff_vector_pop_back(stack, data_ptr, allocator);
	return 1;
}

uint8_t cff_stack_top(cff_stack* stack, uintptr_t data_ptr) {
	cff_assert_param_not_null(stack);
	cff_assert_param_not_null(data_ptr);

	if (stack->count == 0) return 0;
	cff_vector_get(stack, stack->count - 1, data_ptr);
	return 1;
}