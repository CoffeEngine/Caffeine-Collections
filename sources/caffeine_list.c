#include "caffeine_list.h"

#pragma region Auxiliar

 cff_err_e __caffeine_build_bucket(caffeine_list_bucket** bucket, uintptr_t data, uint64_t data_size, AllocatorInterface* allocator) {

	cff_assert_param_not_null(bucket);
	cff_assert_param_not_null(allocator);
	cff_assert_param_not_zero(data_size);
	cff_assert_param_not_zero(data);

	*bucket = (caffeine_list_bucket*)cff_allocator_alloc(allocator, sizeof(caffeine_list_bucket) + (size_t)data_size);
	if (*bucket == NULL) return CFF_ALLOC_ERR;
	(*bucket)->next_bucket = NULL;
	(*bucket)->data_ptr = ((uintptr_t)(*bucket)) + (uintptr_t)sizeof(caffeine_list_bucket);

	cff_memcpy((const void* const)data, (void* const)((*bucket)->data_ptr), (size_t)data_size, (size_t)data_size);

	return CFF_NONE_ERR;
}

 caffeine_list_bucket* __caffeine_get_bucket(cff_list* list, uint64_t index) {
	cff_assert_param_not_null(list);
	cff_assert_param_less(index, list->count);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i != index && i < list->count; i++)
	{
		bucket = bucket->next_bucket;
	}

	return bucket;
}

 void __caffeine_swap(caffeine_list_bucket* prev_a, caffeine_list_bucket* a, caffeine_list_bucket* b) {

	cff_assert_param_not_null(prev_a);
	cff_assert_param_not_null(a);
	cff_assert_param_not_null(b);

	caffeine_list_bucket* a_next = a->next_bucket;
	prev_a->next_bucket = b;
	a->next_bucket = b->next_bucket;
	b->next_bucket = a_next;
}

#pragma endregion


void cff_list_create(cff_list* list, uint64_t data_size) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_zero(data_size);

	list->count = 0;
	list->data_size = data_size;
	list->list_start = NULL;
	list->list_end = NULL;
}

cff_err_e cff_list_add(cff_list* list, uintptr_t data, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data);
	cff_assert_param_not_zero(list->data_size);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	caffeine_list_bucket* bucket;
	if (__caffeine_build_bucket(&bucket, data, list->data_size, allocator) != CFF_NONE_ERR) return CFF_ALLOC_ERR;

	if (list->list_start == NULL) {
		list->list_start = bucket;
		list->list_end = bucket;
	}
	else {
		list->list_end->next_bucket = bucket;
		list->list_end = bucket;
	}

	list->count++;

	return CFF_NONE_ERR;
}

void cff_list_set(cff_list* list, uint64_t index, uintptr_t data) {
	cff_assert_param_not_null(list);
	cff_assert_param_less(index, list->count);
	cff_assert_param_not_null(data);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = __caffeine_get_bucket(list, index);

	cff_memcpy((const void* const)data, (void* const)(bucket->data_ptr), (size_t)list->data_size, (size_t)list->data_size);
}

cff_err_e cff_list_insert(cff_list* list, uint64_t index, uintptr_t data, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);
	cff_assert_param_less_eq(index, list->count);
	cff_assert_param_not_null(data);
	cff_assert_param_not_zero(list->data_size);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	if (index == list->count) {
		return cff_list_add(list, data, allocator);
	}
	caffeine_list_bucket* bucket;
	if (__caffeine_build_bucket(&bucket, data, list->data_size, allocator) != CFF_NONE_ERR) return CFF_ALLOC_ERR;

	if (index == 0) {
		bucket->next_bucket = list->list_start;
		list->list_start = bucket;
	}
	else {
		caffeine_list_bucket* prev_bucket = __caffeine_get_bucket(list, index - 1);
		caffeine_list_bucket* next_bucket = prev_bucket->next_bucket;

		bucket->next_bucket = next_bucket;
		prev_bucket->next_bucket = bucket;
	}

	list->count++;
	return CFF_NONE_ERR;
}

void cff_list_get(cff_list* list, uint64_t index, uintptr_t data_out) {
	cff_assert_param_not_null(list);
	cff_assert_param_less(index, list->count);
	cff_assert_param_not_null(data_out);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = __caffeine_get_bucket(list, index);

	cff_memcpy((const void* const)(bucket->data_ptr), (void* const)data_out, (size_t)list->data_size, (size_t)list->data_size);
}

void cff_list_foreach(cff_list* list, foreach_fn foreach_function) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(foreach_function);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		foreach_function((void*)(bucket->data_ptr), i);
		bucket = bucket->next_bucket;
	}
}

void cff_list_first(cff_list* list, uintptr_t data_out) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_out);
	cff_assert_param_not_zero(list->data_size);

	cff_assert_msg(list->list_start != NULL, "List is empty");

	caffeine_list_bucket* bucket = list->list_start;

	cff_memcpy((const void* const)(bucket->data_ptr), (void* const)data_out, (size_t)list->data_size, (size_t)list->data_size);
}

void cff_list_last(cff_list* list, uintptr_t data_out) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_out);
	cff_assert_param_not_zero(list->data_size);

	cff_assert_msg(list->list_end != NULL, "List is empty");

	caffeine_list_bucket* bucket = list->list_end;

	cff_memcpy((const void* const)(bucket->data_ptr), (void* const)data_out, (size_t)list->data_size, (size_t)list->data_size);
}

void cff_list_remove(cff_list* list, uint64_t index, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);
	cff_assert_param_less(index, list->count);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	caffeine_list_bucket* bucket_to_remove = NULL;

	if (index == 0) {
		bucket_to_remove = list->list_start;
		list->list_start = bucket_to_remove->next_bucket;
	}
	else {
		caffeine_list_bucket* bucket_prev = __caffeine_get_bucket(list, index - 1);
		bucket_to_remove = bucket_prev->next_bucket;

		bucket_prev->next_bucket = bucket_to_remove->next_bucket;

		if (index == list->count - 1) {
			list->list_end = bucket_prev;
		}
	}

	if (bucket_to_remove != NULL) cff_allocator_free(allocator, bucket_to_remove);

	list->count--;
}

void cff_list_clear(cff_list* list, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	caffeine_list_bucket* aux = NULL;

	while (list->list_start != NULL)
	{
		aux = list->list_start;
		list->list_start = list->list_start->next_bucket;
		cff_allocator_free(allocator, aux);
	}

	list->list_start = NULL;
	list->list_end = NULL;
	list->count = 0;
}

void cff_list_join(cff_list* list, cff_list* other) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(other);
	cff_assert_param_not_zero(list->data_size);
	cff_assert_param_not_zero(other->data_size);
	cff_assert_param_equals(list->data_size, other->data_size);

	list->list_end->next_bucket = other->list_start;
	list->list_end = other->list_end;
	list->count += other->count;

	other->list_start = NULL;
	other->list_end = NULL;
	other->count = 0;
	other->data_size = 0;
}


cff_err_e cff_list_copy(cff_list* list, cff_list* other, uint64_t start, uint64_t count, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(other);
	cff_assert_param_not_zero(list->data_size);
	cff_assert_param_less(start, list->count);
	cff_assert_param_less_eq((start + count), list->count);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	cff_list_create(other, list->data_size);

	caffeine_list_bucket* bucket = __caffeine_get_bucket(list, start);

	for (uint64_t i = 0; i < count; i++)
	{
		cff_err_e err = cff_list_add(other, bucket->data_ptr, allocator);
		if (err != CFF_NONE_ERR) {
			return err;
		}
		bucket = bucket->next_bucket;
	}
	return CFF_NONE_ERR;
}

cff_err_e cff_list_clone(cff_list* list, cff_list* other, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(other);
	cff_assert_param_not_zero(list->data_size);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	return cff_list_copy(list, other, 0, list->count, allocator);
}

cff_err_e cff_list_filter(cff_list* list, filter_fn filter_function, cff_list* ptr_out, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_not_zero(list->data_size);
	cff_assert_param_not_null(filter_function);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	cff_list_create(ptr_out, list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		if (filter_function((void*)(bucket->data_ptr), i, list->data_size)) {
			cff_err_e err = cff_list_add(ptr_out, bucket->data_ptr, allocator);
			if (err != CFF_NONE_ERR) {
				return err;
			}
		}
		bucket = bucket->next_bucket;
	}

	return CFF_NONE_ERR;
}

cff_err_e cff_list_map(cff_list* list, map_fn map_function, cff_list* ptr_out, uint64_t out_data_size, AllocatorInterface* allocator) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_not_zero(list->data_size);
	cff_assert_param_not_zero(out_data_size);
	cff_assert_param_not_null(map_function);

	if (allocator == NULL) allocator = cff_get_default_allocator();

	cff_list_create(ptr_out, out_data_size);

	caffeine_list_bucket* bucket = list->list_start;

	uintptr_t buff = (uintptr_t)cff_stack_alloc((size_t)out_data_size);

	if (buff == 0)
		return CFF_ALLOC_ERR;

	for (uint64_t i = 0; i < list->count; i++)
	{
		map_function((void*)bucket->data_ptr, (void*)buff, i);

		cff_err_e err = cff_list_add(ptr_out, buff, allocator);

		if (err != CFF_NONE_ERR) {
			cff_stack_alloc_free((void*)buff);
			return err;
		}

		bucket = bucket->next_bucket;
	}

	cff_stack_alloc_free((void*)buff);

	return CFF_NONE_ERR;
}

uint8_t cff_list_equal(cff_list* list, cff_list* other) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(other);
	cff_assert_param_not_zero(list->data_size);
	cff_assert_param_equals(list->data_size, other->data_size);

	if (list->count != other->count) return 0;

	caffeine_list_bucket* bucket_a = list->list_start;
	caffeine_list_bucket* bucket_b = other->list_start;

	for (size_t i = 0; i < list->count; i++)
	{

		if (cff_memcmp((const void*)bucket_a->data_ptr, (const void*)bucket_b->data_ptr, (size_t)list->data_size) != 0) {
			return 0;
		}

		bucket_a = bucket_a->next_bucket;
		bucket_b = bucket_b->next_bucket;
	}

	return 1;
}

uint8_t cff_list_equal_cmp(cff_list* list, cff_list* other, comparer_fn comparer_function) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(other);
	cff_assert_param_not_zero(list->data_size);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_equals(list->data_size, other->data_size);

	if (list->count != other->count) return 0;

	caffeine_list_bucket* bucket_a = list->list_start;
	caffeine_list_bucket* bucket_b = other->list_start;

	for (size_t i = 0; i < list->count; i++)
	{

		if (comparer_function((void*)bucket_a->data_ptr, (void*)bucket_b->data_ptr, list->data_size) != CFF_EQUALS) {
			return 0;
		}

		bucket_a = bucket_a->next_bucket;
		bucket_b = bucket_b->next_bucket;
	}

	return 1;
}

uint8_t cff_list_find(cff_list* list, uintptr_t data_f, uint64_t* out_index, uintptr_t data_out) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_null(out_index);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		if (cff_memcmp((const void*)bucket->data_ptr, (const void*)data_f, (size_t)list->data_size) == 0) {
			if (data_out != 0) cff_memcpy((const void* const)bucket->data_ptr, (void* const)data_out, (size_t)list->data_size, (size_t)list->data_size);
			*out_index = i;
			return 1;
		}

		bucket = bucket->next_bucket;
	}

	return 0;
}

uint8_t cff_list_find_cmp(cff_list* list, uintptr_t data_f, uint64_t* out_index, uintptr_t data_out, comparer_fn comparer_function) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_null(out_index);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		if (comparer_function(( void*)bucket->data_ptr, ( void*)data_f, list->data_size) == CFF_EQUALS) {
			if (data_out != 0) cff_memcpy((const void* const)bucket->data_ptr, (void* const)data_out, (size_t)list->data_size, (size_t)list->data_size);
			*out_index = i;
			return 1;
		}

		bucket = bucket->next_bucket;
	}

	return 0;
}

uint64_t cff_list_count(cff_list* list, uintptr_t data_f) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;
	uint64_t count = 0;
	for (uint64_t i = 0; i < list->count; i++)
	{
		if (cff_memcmp((const void*)bucket->data_ptr, (const void*)data_f, (size_t)list->data_size) == 0) {
			count++;
		}

		bucket = bucket->next_bucket;
	}

	return count;
}

uint64_t cff_list_count_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;
	uint64_t count = 0;
	for (uint64_t i = 0; i < list->count; i++)
	{
		if (comparer_function((const void* const)bucket->data_ptr, (const void* const)data_f, list->data_size) == CFF_EQUALS) {
			count++;
		}

		bucket = bucket->next_bucket;
	}

	return count;
}

uint8_t cff_list_any(cff_list* list, uintptr_t data_f) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		if (cff_memcmp((const void* const)bucket->data_ptr, (const void* const)data_f, (size_t)list->data_size) == 0) {
			return 1;
		}

		bucket = bucket->next_bucket;
	}

	return 0;
}

uint8_t cff_list_any_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		if (comparer_function((const void* const)bucket->data_ptr, (const void* const)data_f, list->data_size) == CFF_EQUALS) {
			return 1;
		}

		bucket = bucket->next_bucket;
	}

	return 0;
}

uint8_t cff_list_all(cff_list* list, uintptr_t data_f) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		if (cff_memcmp((const void*)bucket->data_ptr, (const void*)data_f, (size_t)list->data_size) != 0) {
			return 0;
		}

		bucket = bucket->next_bucket;
	}

	return 1;
}

uint8_t cff_list_all_cmp(cff_list* list, uintptr_t data_f, comparer_fn comparer_function) {

	cff_assert_param_not_null(list);
	cff_assert_param_not_null(data_f);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(list->data_size);

	caffeine_list_bucket* bucket = list->list_start;

	for (uint64_t i = 0; i < list->count; i++)
	{
		if (comparer_function((const void* const)bucket->data_ptr, (const void* const)data_f, list->data_size) != CFF_EQUALS) {
			return 0;
		}

		bucket = bucket->next_bucket;
	}

	return 1;
}

void cff_list_reverse(cff_list* list) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_zero(list->data_size);

	if (list->count < 2) return;

	caffeine_list_bucket* start = list->list_end;
	caffeine_list_bucket* end = list->list_start;


	caffeine_list_bucket* current = list->list_start->next_bucket;
	caffeine_list_bucket* last_current = list->list_start;
	caffeine_list_bucket* next_current = NULL;

	while (current != NULL)
	{

		next_current = current->next_bucket;
		current->next_bucket = last_current;
		last_current = current;
		current = next_current;
	}


	list->list_start = start;
	list->list_end = end;
	if (list->list_end != NULL)list->list_end->next_bucket = NULL;
}

void cff_list_sort(cff_list* list, comparer_fn comparer_function) {
	cff_assert_param_not_null(list);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_zero(list->data_size);

	if (list->count < 2) return;

	uint64_t list_count = list->count;
	caffeine_list_bucket* list_start = list->list_start;
	caffeine_list_bucket* list_end = NULL;

	for (uint64_t gap = 1; gap < list_count; gap = gap << 1)
	{
		caffeine_list_bucket* next_group = list_start;
		caffeine_list_bucket* prev_group = NULL;

		bool first_iter = true;

		while (next_group)
		{
			caffeine_list_bucket* helve_a_start = next_group;
			caffeine_list_bucket* helve_a_end = helve_a_start;
			uint64_t _tmp_count = gap;

			while (--_tmp_count && helve_a_end->next_bucket != NULL) helve_a_end = helve_a_end->next_bucket;


			caffeine_list_bucket* helve_b_start = helve_a_end->next_bucket;
			caffeine_list_bucket* helve_b_end = helve_b_start;
			_tmp_count = gap;

			if (helve_b_start) {
				while (--_tmp_count && helve_b_end->next_bucket) helve_b_end = helve_b_end->next_bucket;
				next_group = helve_b_end->next_bucket;
				helve_b_end->next_bucket = NULL;
			}
			else next_group = (helve_a_end != NULL) ? helve_a_end->next_bucket : NULL;

			if ((helve_a_end != NULL)) helve_a_end->next_bucket = NULL;

			caffeine_list_bucket sorted_helve = { 0 };
			caffeine_list_bucket* sorted_helve_ptr = &sorted_helve;

			if (helve_b_start == NULL) {
				sorted_helve.next_bucket = helve_a_start;
				sorted_helve_ptr = helve_a_end;
			}
			else
				while (helve_a_start != NULL || helve_b_start != NULL)
				{
					if (helve_a_start == NULL || (helve_b_start != NULL && comparer_function((const void* const)helve_a_start->data_ptr, (const void* const)helve_b_start->data_ptr, list->data_size) != CFF_LESS)) {
						// b
						sorted_helve_ptr->next_bucket = helve_b_start;
						helve_b_start = helve_b_start->next_bucket;
						sorted_helve_ptr = sorted_helve_ptr->next_bucket;
					}
					else {
						// a
						sorted_helve_ptr->next_bucket = helve_a_start;
						helve_a_start = helve_a_start->next_bucket;
						sorted_helve_ptr = sorted_helve_ptr->next_bucket;
					}
				}

			if (first_iter) {
				//first iteration
				list_start = sorted_helve.next_bucket;
				first_iter = false;
			}
			else if (prev_group != NULL) {
				prev_group->next_bucket = sorted_helve.next_bucket;
			}

			list_end = sorted_helve_ptr;
			if (sorted_helve_ptr)sorted_helve_ptr->next_bucket = next_group;
			prev_group = sorted_helve_ptr;

		}

	}

	list->list_start = list_start;
	list->list_end = list_end;
}