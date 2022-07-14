#include "caffeine_queue.h"

void caffeine_queue_create(cff_queue* queue, uint64_t data_size, uint64_t lenght) {
	caffeine_vector_create(queue, data_size, lenght);
}

void caffeine_queue_resize(cff_queue* queue, uint64_t lenght) {
	caffeine_vector_resize(queue, lenght);
}

void caffeine_queue_enqueue(cff_queue* queue, uintptr_t data_ptr) {
	caffeine_vector_push_back(queue, data_ptr);
}

void caffeine_queue_reverse(cff_queue* queue) {
	caffeine_vector_reverse(queue);
}

void caffeine_queue_free(cff_queue* queue) {
	caffeine_vector_free(queue);
}

void caffeine_queue_clear(cff_queue* queue) {
	caffeine_vector_clear(queue);
}

void caffeine_queue_copy(cff_queue* queue, cff_queue* to, uint64_t start, uint64_t end) {
	caffeine_vector_copy(queue, to, start, end);
}

void caffeine_queue_clone(cff_queue* queue, cff_queue* to) {
	caffeine_vector_clone(queue, to);
}

uint8_t caffeine_queue_dequeue(cff_queue* queue, uintptr_t data_ptr) {
	if (queue->count == 0) return 0;
	caffeine_vector_pop_front(queue, data_ptr);
	return 1;
}

