#include "caffeine_container.h"

void caffeine_container_create(cff_container* container, uint64_t data_size, uint64_t lenght) {
	container->buffer = (uintptr_t)cff_realloc(container->buffer,data_size * lenght);
	container->data_size = data_size;
}

void caffeine_container_desloc(cff_container* container, uint64_t from, int64_t steps, uint64_t lenght) {
	if (steps > 0) {
		uint64_t mv_size = ((lenght - from) - steps) * container->data_size;
		uint64_t index_to = from + steps;
		if (mv_size > 0 && index_to < lenght) {
			uintptr_t ptr_from = container->buffer + from;
			uintptr_t ptr_to = container->buffer + to;
			cff_memmove(ptr_to, ptr_from, mv_size);
		}
	}
	else
	{
		int64_t new_index = from + steps;
		int64_t mv_size = (lenght - new_index) * container->data_size;
		if (mv_size > 0) {
			uintptr_t ptr_from = container->buffer + from;
			uintptr_t ptr_to = container->buffer + new_index;
			cff_memmove(ptr_to, ptr_from, mv_size);
		}
	}
}

void caffeine_container_resize(cff_container* container, uint64_t lenght) {
	void* tmp = cff_realloc(container->data_size * lenght);
	if (tmp != NULL) {
		container->buffer = (uintptr_t)tmp;
	}
}

void caffeine_container_insert(cff_container* container, uintptr_t data_ptr, uint64_t index, uint64_t lenght) {
	caffeine_container_desloc(container, index, 1,lenght);
	mcpy(data_ptr, container->buffer + index, container->data_size);
}

void caffeine_container_set(cff_container* container, uintptr_t data_ptr, uint64_t index) {
	mcpy(data_ptr, container->buffer + index, container->data_size);
}

void caffeine_container_get(cff_container* container, uint64_t index, uintptr_t out) {
	uintptr_t from = container->buffer + (index * container->data_size);
	mcpy(from, out, container->data_size);
}

void caffeine_container_remove(cff_container* container, uint64_t index, uint64_t lenght) {
	if (index < lenght) {
		uint64_t mv_size = ((lenght - 1) - index) * container->data_size;
		mcpy(container->buffer + index + 1, container->buffer + index, mv_size);
	}
}

uint64_t caffeine_container_copy(cff_container* container, cff_container* to, uint64_t start, uint64_t end, uint64_t lenght) {
	uint64_t n_len = end - start;
	uint64_t mv_size = container->data_size * n_len;
	if(lenght < n_len || to->buffer == 0) caffeine_container_create(to, container->data_size, n_len);
	mcpy(container->buffer + start, to->buffer, mv_size);
	return n_len;
}

void caffeine_container_clone(cff_container* container, cff_container* to, uint64_t lenght) {
	caffeine_container_create(to, container->data_size, lenght);
	mcpy(container->buffer , to->buffer, lenght * container->data_size);
}

void caffeine_container_overwrite(cff_container* container, cff_container* to, uint64_t start, uint64_t end) {
	uint64_t n_len = end - start;
	uint64_t mv_size = container->data_size * n_len;
	to->data_size = container->data_size;
	to->lenght = n_len;
	mcpy(container->buffer + start, to->buffer, mv_size);
}

void caffeine_container_fill(cff_container* container, uintptr_t data_ptr, uint64_t lenght) {
	for (uint64_t i = 0; i <lenght; i++)
	{
		mcpy(data_ptr, container->buffer + (i * container->data_size), container->data_size);
	}
}

void caffeine_container_join(cff_container* container, cff_container* from, uint64_t c_lenght, uint64_t f_lenght) {
	caffeine_container_resize(container, c_lenght + f_lenght);
	mcpy(from->buffer, container->buffer + c_lenght * container->data_size, f_lenght * from->data_size);
}

void caffeine_container_reverse(cff_container* container, uint64_t lenght) {
	int64_t start = 0;
	int64_t end = lenght - 1;
	char* tmp = cff_malloca(container->data_size);
	while (start < end)
	{
		mcpy(container->buffer + start * container->data_size, (uintptr_t)tmp, container->data_size);
		mcpy(container->buffer + start * container->data_size, container->buffer + end * container->data_size, container->data_size);
		mcpy((uintptr_t)tmp,container->buffer + start * container->data_size, container->data_size);
		start++;
		end--;
	}
	cff_freea(tmp);
}

uint64_t caffeine_container_filter(cff_container* container, filter_fn func, cff_container* filter_result, uint64_t lenght) {
	caffeine_container_create(filter_result, container->data_size, container->lenght);
	int64_t counter = 0;
	for (int64_t i = 0; i < lenght; i++)
	{
		uintptr_t ptr = container->buffer + i * container->data_size;
		if (func(ptr, i)) {
			mcpy(ptr, container->buffer + counter * filter_result->data_size, container->data_size);
			counter++;
		}
	}
	caffeine_container_resize(filter_result, counter);
	return counter;
}

void caffeine_container_map(cff_container* container, map_fn func, cff_container* map_result, uint64_t result_data_size,uint64_t lenght) {
	caffeine_container_create(map_result, result_data_size, lenght);
	for (size_t i = 0; i < container->lenght; i++)
	{
		func(container->buffer + i * container->data_size, map_result->buffer + i * map_result->data_size, i);
	}
}

void caffeine_container_foreach(cff_container* container, foreach_fn func,uint64_t lenght) {
	for (size_t i = 0; i < lenght; i++)
	{
		func(container->buffer + i * container->data_size, i);
	}
}

void caffeine_container_free(cff_container* container) {
	cff_free(container->buffer);
	*container = { 0 };
}

uint8_t caffeine_container_equal(cff_container* container, cff_container* other, uint64_t lenght) {
	if (container->data_size != other->data_size || lenght != lenght) return 0;
	return mcmp(container->buffer, other->buffer, container->data_size * lenght);
}

uint8_t caffeine_container_find(cff_container* container, uintptr_t data_ptr, uint64_t* found, uint64_t lenght) {
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (mcmp(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			*found = i;
			return 1;
		}
	}
	return 0;
}

uint8_t caffeine_container_find_cmp(cff_container* container, uintptr_t data_ptr, uint64_t* found, comparer_fn predicate, uint64_t lenght) {
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (comparer_fn(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			*found = i;
			return 1;
		}
	}
	return 0;
}

uint64_t caffeine_container_count(cff_container* container, uintptr_t data_ptr, uint64_t lenght) {
	uint64_t count = 0;
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (mcmp(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			count++;
		}
	}
	return count;
}

uint64_t caffeine_container_count_cmp(cff_container* container, uintptr_t data_ptr, comparer_fn predicate, uint64_t lenght) {
	uint64_t count = 0;
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (comparer_fn(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			count++;
		}
	}
	return count;
}

uint8_t caffeine_container_any(cff_container* container, uintptr_t data_ptr, uint64_t lenght) {
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (mcmp(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			return 1;
		}
	}
	return 0;
}

uint8_t caffeine_container_any_cmp(cff_container* container, uintptr_t data_ptr, comparer_fn predicate, uint64_t lenght) {
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (comparer_fn(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			return 1;
		}
	}
	return 0;
}

uint8_t caffeine_container_all(cff_container* container, uintptr_t data_ptr, uint64_t lenght) {
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (!mcmp(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			return 0;
		}
	}
	return 1;
}

uint8_t caffeine_container_all_cmp(cff_container* container, uintptr_t data_ptr, comparer_fn predicate, uint64_t lenght) {
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (!comparer_fn(container->buffer + (i * container->data_size), data_ptr, container->data_size)) {
			return 0;
		}
	}
	return 1;
}