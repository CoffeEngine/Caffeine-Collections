#include "caffeine_vector.h"
#include "caffeine_container.h"

void caffeine_vector_create(cff_vector* vector, uint64_t data_size, uint64_t lenght) {
	caffeine_container_create((cff_container*)vector, data_size, lenght);
	vector->count = 0;
}

void caffeine_vector_resize(cff_vector* vector, uint64_t lenght) {
	caffeine_container_resize((cff_container*)vector, lenght);
}

void caffeine_vector_get(cff_vector* vector, uint64_t index, uintptr_t out) {
	caffeine_container_get((cff_container*)vector, index, out);
}

void caffeine_vector_set(cff_vector* vector, uintptr_t data_ptr, uint64_t index) {
	caffeine_container_set((cff_container*)vector, data_ptr, index);
}

void caffeine_vector_insert(cff_vector* vector, uintptr_t data_ptr, uint64_t index) {
	caffeine_container_insert((cff_container*)vector, data_ptr, index,vector->count);
	vector->count++;
}

void caffeine_vector_remove(cff_vector* vector, uint64_t index) {
	caffeine_container_remove((cff_container*)vector, index,vector->count);
	vector->count--;
}

void caffeine_vector_copy(cff_vector* vector, cff_vector* to, uint64_t start, uint64_t end) {
	to->lenght =  caffeine_container_copy((cff_container*)vector, to, start, end,to->lenght);
	to->count = to->lenght;
}

void caffeine_vector_clone(cff_vector* vector, cff_vector* to) {
	caffeine_container_clone((cff_container*)vector, to, to->lenght);
	to->count = vector->count;
}

void caffeine_vector_fill(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_container_fill((cff_container*)vector, data_ptr,vector->lenght);
}

void caffeine_vector_join(cff_vector* vector, cff_vector* from) {
	if (vector->lenght < vector->count + from->count) {
		caffeine_vector_resize(vector, vector->count + from->count);
	}
	mcpy(from->buffer, vector->buffer + (vector->count * vector->data_size), from->count * from->data_size);
	vector->count += from->count;
}

void caffeine_vector_reverse(cff_vector* vector) {
	caffeine_container_reverse((cff_container*)vector,vector->count);
}

void caffeine_vector_filter(cff_vector* vector, filter_fn func, cff_vector* filter_result) {
	caffeine_container_filter((cff_container*)vector, func, filter_result, vector->count);
}

void caffeine_vector_push_back(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_vector_insert(vector, data_ptr, vector->count);
}

void caffeine_vector_push_front(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_vector_insert(vector, data_ptr,0);
}
void caffeine_vector_pop_back(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_vector_get(vector, vector->count - 1, data_ptr);
	vector->count--;
}
void caffeine_vector_pop_front(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_vector_get(vector,0, data_ptr);
	caffeine_vector_remove(vector, 0);
}

void caffeine_vector_map(cff_vector* vector, map_fn func, cff_vector* map_result, uint64_t result_data_size) {
	caffeine_container_map((cff_container*)vector, func, map_result, result_data_size, vector->count);
}

void caffeine_vector_foreach(cff_vector* vector, foreach_fn func) {
	caffeine_container_foreach((cff_container*)vector, func, vector->count);
}

void caffeine_vector_free(cff_vector* vector) {
	caffeine_container_free((cff_container*)vector);
}

uint8_t caffeine_vector_equal(cff_vector* vector, cff_vector* other) {
	caffeine_container_equal((cff_container*)vector, other, vector->count);
}

uint8_t caffeine_vector_find(cff_vector* vector, uintptr_t data_ptr, uint64_t* found) {
	caffeine_container_find((cff_container*)vector, data_ptr, found, vector->count);
}

uint8_t caffeine_vector_find_cmp(cff_vector* vector, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate) {
	caffeine_container_find_cmp((cff_container*)vector, data_ptr, found, predicate, vector->count);
}

uint64_t caffeine_vector_count(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_container_count((cff_container*)vector, data_ptr, vector->count);
}

uint64_t caffeine_vector_count_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate) {
	caffeine_container_count_cmp((cff_container*)vector, data_ptr, predicate, vector->count);
}

uint8_t caffeine_vector_any(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_container_any((cff_container*)vector, data_ptr, vector->count);
}

uint8_t caffeine_vector_any_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate) {
	caffeine_container_any_cmp((cff_container*)vector, data_ptr, predicate, vector->count);
}

uint8_t caffeine_vector_all(cff_vector* vector, uintptr_t data_ptr) {
	caffeine_container_all((cff_container*)vector, data_ptr, vector->count);
}

uint8_t caffeine_vector_all_cmp(cff_vector* vector, uintptr_t data_ptr, comparer_fn predicate) {
	caffeine_container_all_cmp((cff_container*)vector, data_ptr, predicate, vector->count);
}

