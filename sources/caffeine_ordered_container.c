#include "caffeine_ordered_container.h"

#include "caffeine_container.h"

#define get_at_index(buffer,index,size) ((uintptr_t)(((uintptr_t)(buffer)) + (uint64_t)((index)*(size))))
#define get_pivot(ini,end) (((ini)+(end))/2);

cff_cmp_e cff_ordered_container_compare(cff_ordered_container* container, uintptr_t value_ptr, uint64_t index) {
	uintptr_t value = get_at_index(container->buffer, index, container->data_size);
	cff_cmp_e cmp = container->comparer_function((const void* const)value_ptr, (const void* const)value, container->data_size);
	return cmp;
}

uint64_t cff_ordered_container_binary_search(cff_ordered_container* container, uint64_t start, uint64_t end, uintptr_t value)
{
	uint64_t m = 0;
	uint64_t lenght = end;
	while (start < end)
	{
		m = 1 + (start + end) / 2;

		if (m == start || m == end) return m;

		cff_cmp_e cmp = cff_ordered_container_compare(container, value, m);

		if (cmp == CFF_EQUALS)
			return m + 1;

		if (cmp == CFF_GREATER) {
			cff_cmp_e loc_cmp = cff_ordered_container_compare(container, value, m + 1);

			if (loc_cmp == CFF_LESS || loc_cmp == CFF_EQUALS) {
				return m + 1;
			}

			start = m;
			continue;
		}

		if (cmp == CFF_LESS) {
			cff_cmp_e loc_cmp = cff_ordered_container_compare(container, value, m - 1);

			if (loc_cmp == CFF_GREATER || loc_cmp == CFF_EQUALS) {
				return m;
			}

			end = m;
		}
	}

	return m;
}

uint64_t cff_ordered_container_get_index(cff_ordered_container* container, uintptr_t value_ptr, uint64_t count) {
	if (count == 0) {
		return 0;
	}
	uint64_t idx = 0;
	while (idx < count && cff_ordered_container_compare(container,value_ptr,idx) == CFF_GREATER)
	{
		idx++;
	}

	return idx;
}


void cff_ordered_container_add(cff_ordered_container* container, uintptr_t ptr_in, uint64_t count, uint64_t lenght) {
	uint64_t index = cff_ordered_container_get_index(container, ptr_in, count);
	cff_container_insert((cff_container*)container, index, ptr_in, lenght);
}

void cff_ordered_container_free(cff_ordered_container* container, AllocatorInterface* allocator) {
	cff_container_free((cff_container*)container, allocator);
}

void cff_ordered_container_get(cff_ordered_container* container, uint64_t index, uintptr_t ptr_out, uint64_t lenght) {
	cff_container_get((cff_container*)container, index, ptr_out, lenght);
}

void cff_ordered_container_fill(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght) {
	cff_container_fill((cff_container*)container, ptr_in, lenght);
}

void cff_ordered_container_foreach(cff_ordered_container* container, foreach_fn foreach_function, uint64_t lenght) {
	cff_container_foreach((cff_container*)container, foreach_function, lenght);
}

cff_err_e cff_ordered_container_create(cff_ordered_container* container, uint64_t data_size, comparer_fn comparer_function, uint64_t lenght, AllocatorInterface* allocator) {
	container->comparer_function = comparer_function;
	return cff_container_create((cff_container*)container, data_size, lenght, allocator);
}

cff_err_e cff_ordered_container_join(cff_ordered_container* container, cff_ordered_container* other, uint64_t start, uint64_t container_lenght, uint64_t other_lenght, AllocatorInterface* allocator) {
	cff_err_e err = cff_ordered_container_sort(other, container->comparer_function, other_lenght);
	if (err != CFF_NONE_ERR) return err;
	err = cff_container_join((cff_container*)container, (cff_container*)other, start, container_lenght, other_lenght, allocator);
	return err;
}

cff_err_e cff_ordered_container_sort(cff_ordered_container* container, comparer_fn comparer_function, uint64_t lenght) {
	cff_err_e err = cff_container_sort((cff_container*)container, comparer_function, lenght);
	container->comparer_function = comparer_function;
	return err;
}

cff_err_e cff_ordered_container_map(cff_ordered_container* container, map_fn map_function, cff_ordered_container* ptr_out, comparer_fn out_comparer_function, uint64_t out_data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_err_e err = cff_container_map((cff_container*)container, map_function, (cff_container*)ptr_out, out_data_size, lenght, allocator);
	if (err != CFF_NONE_ERR) return err;
	err = cff_ordered_container_sort(ptr_out, out_comparer_function, lenght);
	return err;
}

cff_err_e cff_ordered_container_resize(cff_ordered_container* container, uint64_t lenght, AllocatorInterface* allocator) {
	return cff_container_resize((cff_container*)container, lenght, allocator);
}

cff_err_e cff_ordered_container_copy(cff_ordered_container* container, cff_ordered_container* ptr_out, uint64_t start, uint64_t count, uint64_t out_lenght, uint64_t* copied_count, AllocatorInterface* allocator) {
	return cff_container_copy((cff_container*)container, (cff_container*)ptr_out, start, count, out_lenght, copied_count, allocator);
}

cff_err_e cff_ordered_container_clone(cff_ordered_container* container, cff_ordered_container* out, uint64_t lenght, AllocatorInterface* allocator) {
	return cff_container_clone((cff_container*)container, (cff_container*)out, lenght, allocator);
}

cff_err_e cff_ordered_container_filter(cff_ordered_container* container, filter_fn filter_function, cff_ordered_container* ptr_out, uint64_t lenght, uint64_t* out_lenght, AllocatorInterface* allocator) {
	return cff_container_filter((cff_container*)container, filter_function, (cff_container*)ptr_out, lenght, out_lenght, allocator);
}

uint8_t cff_ordered_container_remove(cff_ordered_container* container, uint64_t index, uint64_t lenght) {
	return cff_container_remove((cff_container*)container, index, lenght);
}

uint8_t cff_ordered_container_equal(cff_ordered_container* container, cff_ordered_container* other, uint64_t lenght) {
	return cff_container_equal((cff_container*)container, (cff_container*)other, lenght);
}

uint8_t cff_ordered_container_find(cff_ordered_container* container, uintptr_t ptr_in, uint64_t* out_index, uint64_t lenght) {
	return cff_ordered_container_find_cmp(container, ptr_in, out_index, container->comparer_function, lenght);
}

uint8_t cff_ordered_container_find_cmp(cff_ordered_container* container, uintptr_t ptr_in, uint64_t* out_index, comparer_fn comparer_function, uint64_t lenght) {
	if (lenght == 0) {
		return false;
	}
	if (lenght == 1) {
		uintptr_t value = get_at_index(container->buffer, 0, container->data_size);
		if (comparer_function((const void* const)value, (const void* const)ptr_in, container->data_size) == CFF_EQUALS) return true;
		*out_index = 0;
		return false;
	}

	uint64_t l = 0, r = lenght - 1;
	uint64_t m = 0;

	while (l <= r)
	{
		m = l + (r - l) / 2;
		
		uintptr_t value = get_at_index(container->buffer, m, container->data_size);
		cff_cmp_e cmp_pivot = comparer_function((const void* const)ptr_in, (const void* const)value, container->data_size);

		if (cmp_pivot == CFF_EQUALS) {
			*out_index = m;
			return true;
		}
			
		if (cmp_pivot == CFF_GREATER) {
			if (m == lenght) return false;
			l = m + 1;
		}
		else {
			if (m == 0) return false;
			r = m - 1;
		}
	}

	return false;
}

uint64_t cff_ordered_container_count(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght) {
	return cff_container_count_cmp((cff_container*)container, ptr_in, container->comparer_function, lenght);
}

uint64_t cff_ordered_container_count_cmp(cff_ordered_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght) {
	return cff_container_count_cmp((cff_container*)container, ptr_in, comparer_function, lenght);
}

uint8_t cff_ordered_container_any(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght) {
	return cff_container_any_cmp((cff_container*)container, ptr_in, container->comparer_function, lenght);
}

uint8_t cff_ordered_container_any_cmp(cff_ordered_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght) {
	return cff_container_any_cmp((cff_container*)container, ptr_in, comparer_function, lenght);
}

uint8_t cff_ordered_container_all(cff_ordered_container* container, uintptr_t ptr_in, uint64_t lenght) {
	return cff_container_all_cmp((cff_container*)container, ptr_in, container->comparer_function, lenght);
}

uint8_t cff_ordered_container_all_cmp(cff_ordered_container* container, uintptr_t ptr_in, comparer_fn comparer_function, uint64_t lenght) {
	return cff_container_all_cmp((cff_container*)container, ptr_in, comparer_function, lenght);
}