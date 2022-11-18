#include "caffeine_container.h"
#include "caffeine_memory.h"
#include "caffeine_assertions.h"

#define ITEM_ADDRESS(container,idx) (container->buffer + idx * container->data_size)

#pragma region UTILS

inline cff_err_e caffeine_container_quick_sort_swap(uintptr_t a, uintptr_t b, uint64_t data_size) {
	cff_assert_param_not_null(a);
	cff_assert_param_not_null(b);
	cff_assert_param_not_zero(data_size);

	uintptr_t tmp = (uintptr_t)cff_stack_alloc((size_t)data_size);
	if (tmp == 0) return CFF_ALLOC_ERR;
	cff_memcpy((const void* const)a, (void* const)tmp, (size_t)data_size, (size_t)data_size);
	cff_memcpy((const void* const)b, (void* const)a, (size_t)data_size, (size_t)data_size);
	cff_memcpy((const void* const)tmp, (void* const)b, (size_t)data_size, (size_t)data_size);
	cff_stack_alloc_free((void*)tmp);
	return CFF_NONE_ERR;
}

inline cff_err_e caffeine_container_quick_sort_partition(uintptr_t arr, uint64_t data_size, uint64_t l, uint64_t h, comparer_fn predicate, uint64_t* pivot) {
	cff_assert_param_not_null(arr);
	cff_assert_param_not_null(predicate);
	cff_assert_param_not_zero(data_size);

	uintptr_t x = arr + (uintptr_t)(h * data_size);
	int64_t i = ((int64_t)l) - 1;

	for (int64_t j = l; j <= ((int64_t)h) - 1; j++)
	{
		if (predicate((void*)resolve_ptr(arr + (j * data_size)), (void*)x, data_size) == CFF_LESS) {
			i++;
			caffeine_container_quick_sort_swap(resolve_ptr(arr + (i * data_size)), resolve_ptr(arr + (j * data_size)), data_size);
		}
	}
	cff_err_e err = caffeine_container_quick_sort_swap(resolve_ptr(arr + ((i + 1) * data_size)), resolve_ptr(arr + (h * data_size)), data_size);
	if (err != CFF_NONE_ERR) return err;
	*pivot = i + 1;
	return CFF_NONE_ERR;
}

inline cff_err_e caffeine_container_quick_sort(uintptr_t buffer, uint64_t data_size, comparer_fn predicate, uint64_t left, uint64_t right) {
	cff_assert_param_not_null(predicate);
	cff_assert_param_not_null(buffer);
	cff_assert_param_not_zero(data_size);

	size_t stack_size = (size_t)(sizeof(uint64_t) * (right - left + 1));
	uint64_t* stack = (uint64_t*)cff_stack_alloc(stack_size);
	if (stack == NULL) return CFF_ALLOC_ERR;
	int64_t top = -1;
	uint64_t h = 0;
	uint64_t l = 0;

#ifdef DEBUG
	cff_memset_64(stack, 0, stack_size);
#endif // DEBUG


	//push left and right to stack
	cff_memcpy((const void* const)&left, (void* const)resolve_ptr(stack + (++top)), sizeof(uint64_t), sizeof(uint64_t));
	cff_memcpy((const void* const)&right, (void* const)resolve_ptr(stack + (++top)), sizeof(uint64_t), sizeof(uint64_t));


	while (top >= 0)
	{
		cff_memcpy((const void* const)resolve_ptr(stack + (top--)), (void* const)&h, sizeof(uint64_t), sizeof(uint64_t));
		cff_memcpy((const void* const)resolve_ptr(stack + (top--)), (void* const)&l, sizeof(uint64_t), sizeof(uint64_t));

		uint64_t pivot = 0;
		cff_err_e err = caffeine_container_quick_sort_partition(buffer, data_size, l, h, predicate, &pivot);
		if (err != CFF_NONE_ERR) return err;

		int64_t tmp = ((int64_t)pivot) - 1;
		if (tmp > (int64_t)l) {
			cff_memcpy((const void* const)&l, (void* const)resolve_ptr(stack + (++top)), sizeof(uint64_t), sizeof(uint64_t));
			cff_memcpy((const void* const)&tmp, (void* const)resolve_ptr(stack + (++top)), sizeof(uint64_t), sizeof(uint64_t));
		}

		tmp = ((int64_t)pivot) + 1;
		if (tmp < (int64_t)h) {
			cff_memcpy((const void* const)&tmp, (void* const)resolve_ptr(stack + (++top)), sizeof(uint64_t), sizeof(uint64_t));
			cff_memcpy((const void* const)&h, (void* const)resolve_ptr(stack + (++top)), sizeof(uint64_t), sizeof(uint64_t));
		}
	}

	cff_stack_alloc_free((void*)stack);
	return CFF_NONE_ERR;
}

#pragma endregion


cff_err_e cff_container_create(cff_container* container, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_zero(data_size);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	uintptr_t ptr = (uintptr_t)cff_allocator_alloc(allocator, (size_t)(data_size * lenght), 0);
	if (ptr == 0) return CFF_ALLOC_ERR;
	container->buffer = ptr;
	container->data_size = data_size;
	return CFF_NONE_ERR;
}

cff_err_e caffeine_container_recreate(cff_container* container, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_zero(data_size);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	void* tmp = 0;
	if (cff_allocator_realloc(allocator, (void*)container->buffer, (size_t)(data_size * lenght), 0, &tmp)) {
		container->buffer = (uintptr_t)tmp;
		container->data_size = data_size;
		return CFF_NONE_ERR;
	}
	return CFF_REALLOC_ERR;
}

void cff_container_desloc(cff_container* container, uint64_t from, int64_t steps, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_greater_eq(from + steps, 0);
	cff_assert_param_less_eq(from + steps, lenght);

	if (steps > 0) {
		uint64_t mv_size = ((lenght - from) - steps) * container->data_size;
		uint64_t index_to = from + steps;
		if (mv_size > 0 && index_to < lenght) {
			uintptr_t ptr_from = resolve_ptr(container->buffer + (from * container->data_size));
			uintptr_t ptr_to = resolve_ptr(container->buffer + (index_to * container->data_size));
			cff_memmove((const void* const)ptr_from, (void* const)ptr_to, (size_t)mv_size, (size_t)mv_size);
		}
	}
	else
	{
		int64_t new_index = from + steps;
		int64_t mv_size = (lenght - new_index) * container->data_size;
		if (mv_size > 0) {
			uintptr_t ptr_from = resolve_ptr(container->buffer + (from * container->data_size));
			uintptr_t ptr_to = resolve_ptr(container->buffer + (new_index * container->data_size));
			cff_memmove((const void* const)ptr_from, (void* const)ptr_to, (size_t)mv_size, (size_t)mv_size);
		}
	}
}

cff_err_e cff_container_resize(cff_container* container, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	void* tmp;
	if (cff_allocator_realloc(allocator, (void*)container->buffer, (size_t)(container->data_size * lenght), 0, &tmp)) {
		container->buffer = (uintptr_t)tmp;
		return CFF_NONE_ERR;
	}
	return CFF_REALLOC_ERR;
}

void cff_container_insert(cff_container* container, uint64_t index, uintptr_t ptr_in, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_less(index, lenght);


	cff_container_desloc(container, index, 1, lenght);
	cff_memcpy((const void* const)ptr_in, (void* const)resolve_ptr(ITEM_ADDRESS(container, index)), (size_t)(container->data_size), (size_t)(container->data_size));
}

void cff_container_set(cff_container* container, uint64_t index, uintptr_t ptr_in, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_less(index, lenght);

	cff_memcpy((const void* const)ptr_in, (void* const)resolve_ptr(ITEM_ADDRESS(container, index)), (size_t)(container->data_size), (size_t)(container->data_size));
}

void cff_container_get(cff_container* container, uint64_t index, uintptr_t ptr_out, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_less(index, lenght);

	uintptr_t from = resolve_ptr(ITEM_ADDRESS(container, index));
	cff_memcpy((const void* const)from, (void* const)ptr_out, (size_t)container->data_size, (size_t)container->data_size);
}

uint8_t cff_container_remove(cff_container* container, uint64_t index, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_less(index, lenght);

	uint64_t mv_payload_size = ((lenght - index) - 1) * container->data_size;
	uintptr_t mv_from = resolve_ptr(container->buffer + (index + 1) * container->data_size);
	uintptr_t mv_to = resolve_ptr(container->buffer + index * container->data_size);

	if (index + 1 < lenght) {
		cff_memmove((const void* const)mv_from, (void* const)mv_to, (size_t)mv_payload_size, (size_t)mv_payload_size);
		return 1;
	}
	return 0;
}

cff_err_e cff_container_copy(cff_container* container, cff_container* ptr_out, uint64_t start, uint64_t count, uint64_t to_lenght, uint64_t* copied_count, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(to_lenght);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_less_eq((count + start), to_lenght);

	uint64_t n_len = count;
	uint64_t mv_size = container->data_size * n_len;
	cff_err_e err = CFF_NONE_ERR;

	if (ptr_out->buffer == 0) {
		err = cff_container_create(ptr_out, container->data_size, n_len, allocator);
		to_lenght = n_len;
	}
	else if (to_lenght < n_len || container->data_size != ptr_out->data_size) {
		err = caffeine_container_recreate(ptr_out, container->data_size, n_len, allocator);
		to_lenght = n_len;
	}

	if (err != CFF_NONE_ERR) return err;

	cff_memcpy((const void* const)resolve_ptr(ITEM_ADDRESS(container, start)), (void* const)ptr_out->buffer, (size_t)mv_size, (size_t)mv_size);

	if (copied_count != NULL) *copied_count = to_lenght;
	return CFF_NONE_ERR;
}

cff_err_e cff_container_clone(cff_container* container, cff_container* ptr_out, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_null(ptr_out);

	cff_err_e err = CFF_NONE_ERR;
	if (ptr_out->buffer == 0) err = cff_container_create(ptr_out, container->data_size, lenght, allocator);
	else err = caffeine_container_recreate(ptr_out, container->data_size, lenght, allocator);
	if (err != CFF_NONE_ERR) return err;

	uint64_t size = lenght * container->data_size;
	cff_memcpy((const void* const)container->buffer, (void* const)ptr_out->buffer, (size_t)size, (size_t)size);
	return CFF_NONE_ERR;
}

void caffeine_container_overwrite(cff_container* container, cff_container* ptr_out, uint64_t start, uint64_t end, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_less(end, lenght);
	cff_assert_param_less(start, end);

	uint64_t n_len = end - start;
	uint64_t mv_size = container->data_size * n_len;
	ptr_out->data_size = container->data_size;
	cff_memcpy((const void* const)resolve_ptr(container->buffer + start), (void* const)ptr_out->buffer, (size_t)mv_size, (size_t)mv_size);
}

void cff_container_fill(cff_container* container, uintptr_t ptr_in, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_null(ptr_in);

	for (uint64_t i = 0; i < lenght; i++)
	{
		cff_memcpy((const void* const)ptr_in, (void* const)resolve_ptr(container->buffer + (i * container->data_size)), (size_t)container->data_size, (size_t)container->data_size);
	}
}

cff_err_e cff_container_join(cff_container* container, cff_container* other, uint64_t start, uint64_t container_lenght, uint64_t other_lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(other);
	cff_assert_param_not_zero(container_lenght);
	cff_assert_param_not_zero(other_lenght);
	cff_assert_param_less(start, container_lenght);
	cff_assert_param_equals(container->data_size, other->data_size);

	cff_err_e err = CFF_NONE_ERR;
	if (start + other_lenght >= container_lenght) err = cff_container_resize(container, start + other_lenght, allocator);
	if (err != CFF_NONE_ERR) return err;
	uint64_t size = other_lenght * container->data_size;
	cff_memcpy((const void* const)other->buffer, (void* const)resolve_ptr(ITEM_ADDRESS(container, start)), (size_t)size, (size_t)size);
	return CFF_NONE_ERR;
}

cff_err_e cff_container_reverse(cff_container* container, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(container->buffer);
	cff_assert_param_not_zero(lenght);

	int64_t start = 0;
	int64_t end = lenght - 1;
	char* tmp = (char*)cff_stack_alloc((size_t)container->data_size);
	if (tmp == NULL) return CFF_ALLOC_ERR;
	while (start < end)
	{
		uintptr_t start_ptr = resolve_ptr(container->buffer + start * container->data_size);
		uintptr_t end_ptr = resolve_ptr(container->buffer + end * container->data_size);
		cff_memcpy((const void* const)start_ptr, (void* const)tmp, (size_t)container->data_size, (size_t)container->data_size);
		cff_memcpy((const void* const)end_ptr, (void* const)start_ptr, (size_t)container->data_size, (size_t)container->data_size);
		cff_memcpy((const void* const)tmp, (void* const)end_ptr, (size_t)container->data_size, (size_t)container->data_size);
		start++;
		end--;
	}
	cff_stack_alloc_free((void*)tmp);
	return CFF_NONE_ERR;
}

cff_err_e cff_container_filter(cff_container* container, filter_fn filter_function, cff_container* ptr_out, uint64_t container_lenght, uint64_t* out_lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_zero(container_lenght);
	cff_assert_param_not_null(filter_function);
	cff_assert_param_not_null(ptr_out);

	cff_err_e err = cff_container_create(ptr_out, container->data_size, container_lenght, allocator);
	if (err != CFF_NONE_ERR) return err;

	uint64_t counter = 0;
	for (uint64_t i = 0; i < container_lenght; i++)
	{
		uintptr_t ptr = resolve_ptr(ITEM_ADDRESS(container, i));
		if (filter_function((void*)ptr, i, container->data_size) == true) {
			cff_container_set(ptr_out, counter, ptr, container_lenght);
			//cff_memcpy((const void* const)ptr, (void* const)resolve_ptr(container->buffer + counter * filter_result->data_size), (size_t)container->data_size, (size_t)container->data_size);
			counter++;
		}
	}

	if (counter > 0) {
		err = cff_container_resize(ptr_out, counter, allocator);
		if (err != CFF_NONE_ERR) return err;
	}
	else {
		cff_container_free(ptr_out, 0);
	}

	if (out_lenght != NULL) *out_lenght = counter;

	return CFF_NONE_ERR;
}

cff_err_e cff_container_map(cff_container* container, map_fn map_function, cff_container* ptr_out, uint64_t out_data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(map_function);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_zero(out_data_size);

	cff_err_e err = cff_container_create(ptr_out, out_data_size, lenght, allocator);
	if (err != CFF_NONE_ERR) return err;

	uintptr_t tmp_ptr_out = (uintptr_t)cff_stack_alloc((size_t)out_data_size);
	if (tmp_ptr_out == 0) return CFF_ALLOC_ERR;

	for (size_t i = 0; i < lenght; i++)
	{

		uintptr_t data = resolve_ptr(container->buffer + i * container->data_size);
		map_function((void*)data, (void*)tmp_ptr_out, i);
		cff_container_set(ptr_out, i, (uintptr_t)tmp_ptr_out, lenght);
	}
	cff_stack_alloc_free((void*)tmp_ptr_out);

	return CFF_NONE_ERR;
}

void cff_container_foreach(cff_container* container, foreach_fn foreach_function, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(foreach_function);
	cff_assert_param_not_zero(lenght);

	for (size_t i = 0; i < lenght; i++)
	{
		foreach_function((void*)resolve_ptr(container->buffer + i * container->data_size), i);
	}
}

cff_err_e cff_container_sort(cff_container* container, comparer_fn comparer_function, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(lenght);

	return caffeine_container_quick_sort(container->buffer, container->data_size, comparer_function, 0, lenght - 1);
}

void cff_container_free(cff_container* container, AllocatorInterface* allocator) {
	cff_assert_param_not_null(container);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	cff_allocator_free(allocator, (void*)container->buffer, 0);
	container->buffer = 0;
	container->data_size = 0;
}

uint8_t cff_container_equal(cff_container* container, cff_container* other, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(other);
	cff_assert_param_not_zero(lenght);

	if (container->data_size != other->data_size) return 0;
	uint64_t size = container->data_size * lenght;
	return (cff_cmp_e)cff_memcmp((const void*)container->buffer, (const void*)other->buffer, (size_t)size);
}

uint8_t cff_container_find(cff_container* container, uintptr_t ptr_in, uint64_t* out_index, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(out_index);
	cff_assert_param_not_zero(lenght);

	for (uint64_t i = 0; i < lenght; i++)
	{
		if (cff_memcmp((const void*)resolve_ptr(container->buffer + (i * container->data_size)), (const void*)ptr_in, (size_t)container->data_size) == 0) {
			*out_index = i;
			return 1;
		}
	}
	return 0;
}

uint8_t cff_container_find_cmp(cff_container* container, uintptr_t ptr_in, uint64_t* out_index, comparer_fn comparer_function, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(out_index);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(lenght);

	for (uint64_t i = 0; i < lenght; i++)
	{
		if (comparer_function((void*)resolve_ptr(container->buffer + (i * container->data_size)), (void*)ptr_in, container->data_size) == CFF_EQUALS) {
			*out_index = i;
			return 1;
		}
	}
	return 0;
}

uint64_t cff_container_count(cff_container* container, uintptr_t ptr_in, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_zero(lenght);

	uint64_t count = 0;
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (cff_memcmp((const void*)resolve_ptr(container->buffer + (i * container->data_size)), (const void*)ptr_in, (size_t)container->data_size) == 0) {
			count++;
		}
	}
	return count;
}

uint64_t cff_container_count_cmp(cff_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(lenght);

	uint64_t count = 0;
	for (uint64_t i = 0; i < lenght; i++)
	{
		if (comparer_function((void*)resolve_ptr(container->buffer + (i * container->data_size)), (void*)ptr_in, container->data_size) == CFF_EQUALS) {
			count++;
		}
	}
	return count;
}

uint8_t cff_container_any(cff_container* container, uintptr_t ptr_in, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_zero(lenght);

	for (uint64_t i = 0; i < lenght; i++)
	{
		if (cff_memcmp((const void*)resolve_ptr(container->buffer + (i * container->data_size)), (const void*)ptr_in, (size_t)container->data_size) == 0) {
			return 1;
		}
	}
	return 0;
}

uint8_t cff_container_any_cmp(cff_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(lenght);

	for (uint64_t i = 0; i < lenght; i++)
	{
		if (comparer_function((void*)resolve_ptr(container->buffer + (i * container->data_size)), (void*)ptr_in, container->data_size) == CFF_EQUALS) {
			return 1;
		}
	}
	return 0;
}

uint8_t cff_container_all(cff_container* container, uintptr_t ptr_in, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_zero(lenght);

	for (uint64_t i = 0; i < lenght; i++)
	{
		if (!cff_memcmp((const void*)resolve_ptr(container->buffer + (i * container->data_size)), (const void*)ptr_in, (size_t)container->data_size) == 0) {
			return 0;
		}
	}
	return 1;
}

uint8_t cff_container_all_cmp(cff_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght) {
	cff_assert_param_not_null(container);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(lenght);

	for (uint64_t i = 0; i < lenght; i++)
	{
		if (comparer_function((void*)resolve_ptr(container->buffer + (i * container->data_size)), (void*)ptr_in, container->data_size) != CFF_EQUALS) {
			return 0;
		}
	}
	return 1;
}