#include "caffeine_queue.h"
#include "caffeine_assertions.h"

void cff_queue_create(cff_queue* queue, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_zero(data_size);
	
	cff_vector_create(queue, data_size, lenght, allocator);
}

void cff_queue_resize(cff_queue* queue, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_zero(lenght);

	cff_vector_resize(queue, lenght, allocator);
}

void cff_queue_enqueue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(data_ptr);

	cff_vector_push_back(queue, data_ptr,allocator);
}

void cff_queue_reverse(cff_queue* queue) {
	cff_assert_param_not_null(queue);

	cff_vector_reverse(queue);
}

void cff_queue_free(cff_queue* queue, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);

	cff_vector_free(queue, allocator);
}

void cff_queue_clear(cff_queue* queue) {
	cff_assert_param_not_null(queue);

	cff_vector_clear(queue);
}

void cff_queue_copy(cff_queue* queue, cff_queue* to, uint64_t start, uint64_t count, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(to);
	cff_assert_param_less((start + count), queue->lenght);

	cff_vector_copy(queue, to, start, count, allocator);
}

void cff_queue_clone(cff_queue* queue, cff_queue* to, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(to);

	cff_vector_clone(queue, to, allocator);
}

uint8_t cff_queue_dequeue(cff_queue* queue, uintptr_t data_ptr, AllocatorInterface* allocator) {
	cff_assert_param_not_null(queue);
	cff_assert_param_not_null(data_ptr);

	if (queue->count == 0) return 0;
	cff_vector_pop_front(queue, data_ptr, allocator);
	return 1;
}

