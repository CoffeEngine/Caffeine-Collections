#include "caffeine_queue.h"
#include "caffeine_assertions.h"

cff_err_e caffeine_queue_create(cff_queue* queue, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_zero(data_size);
	
	return caffeine_vector_create(queue, data_size, lenght, allocator);
}

cff_err_e caffeine_queue_resize(cff_queue* queue, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_zero(lenght);

	return caffeine_vector_resize(queue, lenght, allocator);
}

cff_err_e caffeine_queue_enqueue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(data_ptr);

	return caffeine_vector_push_back(queue, data_ptr,allocator);
}

cff_err_e caffeine_queue_reverse(cff_queue* queue) {
	cff_assert_param_not_null(queue);

	return caffeine_vector_reverse(queue);
}

void caffeine_queue_free(cff_queue* queue, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);

	caffeine_vector_free(queue, allocator);
}

void caffeine_queue_clear(cff_queue* queue) {
	cff_assert_param_not_null(queue);

	caffeine_vector_clear(queue);
}

cff_err_e caffeine_queue_copy(cff_queue* queue, cff_queue* to, uint64_t start, uint64_t end, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(to);
	cff_assert_param_less(end, queue->lenght);
	cff_assert_param_less(start, end);

	return caffeine_vector_copy(queue, to, start, end, allocator);
}

cff_err_e caffeine_queue_clone(cff_queue* queue, cff_queue* to, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(to);

	return caffeine_vector_clone(queue, to, allocator);
}

cff_err_e caffeine_queue_dequeue(cff_queue* queue, uintptr_t data_ptr,uint8_t* is_empty, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(data_ptr);

	
	if (queue->count == 0) {
		if (is_empty != NULL) *is_empty = 1;
		return CFF_NONE_ERR;
	}
	if (is_empty != NULL) *is_empty = 0;

	return caffeine_vector_pop_front(queue, data_ptr, allocator);
}

