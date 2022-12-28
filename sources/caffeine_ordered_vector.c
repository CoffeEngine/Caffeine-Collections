#include "caffeine_ordered_vector.h"
#include "caffeine_ordered_container.h"
#include "caffeine_assertions.h"

cff_err_e cff_ordered_vector_create(cff_ordered_vector* vector, uint64_t data_size, comparer_fn compare_function, uint64_t lenght, AllocatorInterface* allocator) {
	vector->lenght = lenght;
	vector->count = 0;
	return cff_ordered_container_create((cff_ordered_container*)vector, data_size, compare_function, lenght, allocator);
}

cff_err_e cff_ordered_vector_resize(cff_ordered_vector* vector, uint64_t lenght, AllocatorInterface* allocator) {
	cff_err_e err = cff_ordered_container_resize((cff_ordered_container*)vector, lenght, allocator);
	if (err == CFF_NONE_ERR) vector->lenght = lenght;
	return err;
}

void cff_ordered_vector_get(cff_ordered_vector* vector, uint64_t index, uintptr_t out) {
	cff_ordered_container_get((cff_ordered_container*)vector, index, out, vector->count);
}

void cff_ordered_vector_remove(cff_ordered_vector* vector, uint64_t index, AllocatorInterface* allocator) {
	cff_ordered_container_remove((cff_ordered_container*)vector, index, vector->count);
	vector->count--;
	if (vector->count < vector->lenght / 2) cff_ordered_vector_resize(vector, vector->lenght / 2, allocator);
}

cff_err_e cff_ordered_vector_copy(cff_ordered_vector* vector, cff_ordered_vector* to, uint64_t start, uint64_t count, AllocatorInterface* allocator) {
	cff_err_e err = cff_ordered_container_copy((cff_ordered_container*)vector, (cff_ordered_container*)to, start, count, to->lenght, &to->count, allocator);
	if (err == CFF_NONE_ERR) {
		to->lenght = to->count;
	}
	return err;
}

cff_err_e cff_ordered_vector_clone(cff_ordered_vector* vector, cff_ordered_vector* to, AllocatorInterface* allocator) {

	cff_err_e err = cff_ordered_container_clone((cff_ordered_container*)vector, (cff_ordered_container*)to, vector->lenght, allocator);
	if (err == CFF_NONE_ERR) {
		to->count = vector->count;
		to->lenght = vector->lenght;
	}
	return err;
}

void cff_ordered_vector_fill(cff_ordered_vector* vector, uintptr_t data_ptr) {
	cff_ordered_container_fill((cff_ordered_container*)vector, data_ptr, vector->lenght);
	vector->count = vector->lenght;
}

cff_err_e cff_ordered_vector_join(cff_ordered_vector* vector, cff_ordered_vector* from, AllocatorInterface* allocator) {
	cff_err_e err = cff_ordered_container_join((cff_ordered_container*)vector, (cff_ordered_container*)from, vector->count, vector->lenght, from->count, allocator);
	if (err == CFF_NONE_ERR) {
		if (vector->count + from->count >= vector->lenght) {
			vector->lenght = vector->count + from->count;
		}
		vector->count += from->count;
	}
	return err;
}

void cff_ordered_vector_filter(cff_ordered_vector* vector, filter_fn func, cff_ordered_vector* filter_result, AllocatorInterface* allocator) {
	cff_ordered_container_filter((cff_ordered_container*)vector, func, (cff_ordered_container*)filter_result, vector->count, &filter_result->lenght, allocator);
	filter_result->count = filter_result->lenght;
}

void cff_ordered_vector_map(cff_ordered_vector* vector, map_fn func, cff_ordered_vector* map_result, comparer_fn out_comparer_function, uint64_t result_data_size, AllocatorInterface* allocator) {
	cff_ordered_container_map((cff_ordered_container*)vector, func, (cff_ordered_container*)map_result, out_comparer_function, result_data_size, vector->count, allocator);
	map_result->count = map_result->lenght = vector->count;
}

void cff_ordered_vector_foreach(cff_ordered_vector* vector, foreach_fn func) {
	cff_ordered_container_foreach((cff_ordered_container*)vector, func, vector->count);
}

void cff_ordered_vector_sort(cff_ordered_vector* vector, comparer_fn predicate) {
	cff_ordered_container_sort((cff_ordered_container*)vector, predicate, vector->count);
}

void cff_ordered_vector_free(cff_ordered_vector* vector, AllocatorInterface* allocator) {
	cff_ordered_container_free((cff_ordered_container*)vector, allocator);
	*vector = (cff_ordered_vector){ 0 };
}

void cff_ordered_vector_clear(cff_ordered_vector* vector) {
	vector->count = 0;
}

void cff_ordered_vector_add(cff_ordered_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator) {

	if (vector->count == vector->lenght) {
		cff_ordered_vector_resize(vector, vector->lenght * 2, allocator);
	}

	cff_ordered_container_add((cff_ordered_container*)vector, data_ptr, vector->count, vector->lenght);
	vector->count++;
}

void cff_ordered_vector_pop_back(cff_ordered_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator) {
	cff_assert_param_not_null(vector);
	cff_assert_param_not_null(data_ptr);

	cff_ordered_vector_get(vector, vector->count - 1, data_ptr);
	vector->count--;
	if (vector->count < vector->lenght / 2) cff_ordered_vector_resize(vector, vector->lenght / 2, allocator);
}

void cff_ordered_vector_pop_front(cff_ordered_vector* vector, uintptr_t data_ptr, AllocatorInterface* allocator) {
	cff_assert_param_not_null(vector);
	cff_assert_param_not_null(data_ptr);

	cff_ordered_vector_get(vector, 0, data_ptr);
	cff_ordered_vector_remove(vector, 0, allocator);
}

uint8_t cff_ordered_vector_equal(cff_ordered_vector* vector, cff_ordered_vector* other) {
	return cff_ordered_container_equal((cff_ordered_container*)vector, (cff_ordered_container*)other, vector->count);
}

uint8_t cff_ordered_vector_find(cff_ordered_vector* vector, uintptr_t data_ptr, uint64_t* found) {
	return cff_ordered_vector_find_cmp(vector, data_ptr, found, vector->comparer_function);
}

uint8_t cff_ordered_vector_find_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate) {
	return cff_ordered_container_find_cmp((cff_ordered_container*)vector, data_ptr, found, predicate, vector->count);
}

uint64_t cff_ordered_vector_count(cff_ordered_vector* vector, uintptr_t data_ptr) {
	return cff_ordered_vector_count_cmp(vector, data_ptr, vector->comparer_function);
}

uint64_t cff_ordered_vector_count_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, comparer_fn predicate) {
	return cff_ordered_container_count_cmp((cff_ordered_container*)vector, data_ptr, predicate, vector->count);
}

uint8_t cff_ordered_vector_any(cff_ordered_vector* vector, uintptr_t data_ptr) {
	return cff_ordered_vector_any_cmp(vector, data_ptr, vector->comparer_function);
}

uint8_t cff_ordered_vector_any_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, comparer_fn predicate) {
	return cff_ordered_container_any_cmp((cff_ordered_container*)vector, data_ptr, predicate, vector->count);
}

uint8_t cff_ordered_vector_all(cff_ordered_vector* vector, uintptr_t data_ptr) {
	return cff_ordered_vector_all_cmp(vector, data_ptr, vector->comparer_function);
}

uint8_t cff_ordered_vector_all_cmp(cff_ordered_vector* vector, uintptr_t data_ptr, comparer_fn predicate) {
	return cff_ordered_container_all_cmp((cff_ordered_container*)vector, data_ptr, predicate, vector->count);
}