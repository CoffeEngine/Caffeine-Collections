#include "caffeine_array.h"
#include "caffeine_container.h"

void caffeine_array_create(cff_array* array, uint64_t data_size, uint64_t lenght) {
	caffeine_container_create(array, data_size, lenght);
	array->lenght = lenght;
}

void caffeine_array_resize(cff_array* array, uint64_t lenght) {
	caffeine_container_resize(array, lenght);
	array->lenght = lenght;
}

void caffeine_array_get(cff_array* array, uint64_t index, uintptr_t out) {
	caffeine_container_get(array, index, out);
}

void caffeine_array_set(cff_array* array, uintptr_t data_ptr, uint64_t index) {
	caffeine_container_set(array, data_ptr, index);
}

void caffeine_array_insert(cff_array* array, uintptr_t data_ptr, uint64_t index) {
	caffeine_container_insert(array, data_ptr, index,array->lenght);
}

void caffeine_array_remove(cff_array* array, uint64_t index) {
	caffeine_container_remove(array, index, array->lenght);
}

void caffeine_array_copy(cff_array* array, cff_array* to, uint64_t start, uint64_t end) {
	to->lenght = caffeine_container_copy(array, to, start, end, array->lenght);
}

void caffeine_array_clone(cff_array* array, cff_array* to) {
	caffeine_container_clone(array, to, array->lenght);
}

void caffeine_array_fill(cff_array* array, uintptr_t data_ptr) {
	caffeine_container_fill(array, data_ptr, array->lenght);
}

void caffeine_array_join(cff_array* array, cff_array* from) {
	caffeine_container_join(array, from, array->lenght,from->lenght);
	array->lenght += from->lenght;
}

void caffeine_array_reverse(cff_array* array) {
	caffeine_container_reverse(array, array->lenght);
}

void caffeine_array_filter(cff_array* array, filter_fn func, cff_array* filter_result) {
	filter_result->lenght = caffeine_container_filter(array, func, filter_result, array->lenght);
}

void caffeine_array_map(cff_array* array, map_fn func, array* map_result, uint64_t result_data_size) {
	caffeine_container_map(array, func, map_result, result_data_size, array->lenght);
}

void caffeine_array_foreach(cff_array* array, foreach_fn func) {
	caffeine_container_foreach(array, func, array->lenght);
}

void caffeine_array_free(cff_array* array) {
	caffeine_container_free(array);
}

uint8_t caffeine_array_equal(cff_array* array, cff_array* other) {
	caffeine_container_equal(array, other, array->lenght);
}

uint8_t caffeine_array_find(cff_array* array, uintptr_t data_ptr, uint64_t* found) {
	caffeine_container_find(array, data_ptr, found, array->lenght);
}

uint8_t caffeine_array_find_cmp(cff_array* array, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate) {
	caffeine_container_find_cmp(array, data_ptr, found, predicate, array->lenght);
}

uint64_t caffeine_array_count(cff_array* array, uintptr_t data_ptr) {
	caffeine_container_count(array, data_ptr, array->lenght);
}

uint64_t caffeine_array_count_cmp(cff_array* array, uintptr_t data_ptr, comparer_fn predicate) {
	caffeine_container_count_cmp(array, data_ptr, predicate, array->lenght);
}

uint8_t caffeine_array_any(cff_array* array, uintptr_t data_ptr) {
	caffeine_container_any(array, data_ptr, array->lenght);
}

uint8_t caffeine_array_any_cmp(cff_array* array, uintptr_t data_ptr, comparer_fn predicate) {
	caffeine_container_any_cmp(array, data_ptr, predicate, array->lenght);
}

uint8_t caffeine_array_all(cff_array* array, uintptr_t data_ptr) {
	caffeine_container_all(array, data_ptr, array->lenght);
}

uint8_t caffeine_array_all_cmp(cff_array* array, uintptr_t data_ptr, comparer_fn predicate) {
	caffeine_container_all_cmp(array, data_ptr, predicate, array->lenght);
}

