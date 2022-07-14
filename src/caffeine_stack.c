#include "caffeine_stack.h"

void caffeine_stack_create(cff_stack* stack, uint64_t data_size, uint64_t lenght) {
	caffeine_vector_create(stack, data_size, lenght);
}

void caffeine_stack_resize(cff_stack* stack, uint64_t lenght) {
	caffeine_vector_resize(stack, lenght);
}

void caffeine_stack_push(cff_stack* stack, uintptr_t data_ptr) {
	caffeine_vector_push_back(stack, data_ptr);
}

void caffeine_stack_reverse(cff_stack* stack) {
	caffeine_vector_reverse(stack);
}

void caffeine_stack_free(cff_stack* stack) {
	caffeine_vector_free(stack);
}

void caffeine_stack_clear(cff_stack* stack) {
	caffeine_vector_clear(stack);
}

void caffeine_stack_copy(cff_stack* stack, cff_stack* to, uint64_t start, uint64_t end) {
	caffeine_vector_copy(stack, to, start, end);
}

void caffeine_stack_clone(cff_stack* stack, cff_stack* to) {
	caffeine_vector_clone(stack, to);
}

uint8_t caffeine_stack_pop(cff_stack* stack, uintptr_t data_ptr) {
	if (stack->count == 0) return 0;
	caffeine_vector_pop_back(stack, data_ptr);
	return 1;
}

uint8_t caffeine_stack_top(cff_stack* stack, uintptr_t data_ptr) {
	if (stack->count == 0) return 0;
	caffeine_vector_get(stack, stack->count - 1, data_ptr);
	return 1;
}