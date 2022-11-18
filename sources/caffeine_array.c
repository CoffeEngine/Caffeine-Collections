#include "caffeine_array.h"
#include "caffeine_container.h"
#include "caffeine_assertions.h"

cff_err_e cff_array_create(cff_array* array, uint64_t data_size, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_zero(lenght);
	cff_assert_param_not_zero(data_size);

	cff_cmp_e _err = cff_container_create((cff_container*)array, data_size, lenght, allocator);

	if (_err == CFF_NONE_ERR) {
		array->lenght = lenght;
	}

	return _err;
}

cff_err_e cff_array_resize(cff_array* array, uint64_t lenght, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_zero(lenght);

	cff_err_e err = cff_container_resize((cff_container*)array, lenght,allocator);

	if (err == CFF_NONE_ERR) {
		array->lenght = lenght;
	}
	return err;
}

void cff_array_get(cff_array* array, uint64_t index, uintptr_t ptr_out) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_less(index, array->lenght);

	cff_container_get((cff_container*)array, index, ptr_out, array->lenght);
}

void cff_array_set(cff_array* array, uint64_t index, uintptr_t ptr_in) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_less(index, array->lenght);

	cff_container_set((cff_container*)array, index, ptr_in, array->lenght);
}

void cff_array_insert(cff_array* array, uint64_t index, uintptr_t ptr_in) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_less(index, array->lenght);

	cff_container_insert((cff_container*)array, index, ptr_in, array->lenght);
}

void cff_array_remove(cff_array* array, uint64_t index) {
	cff_assert_param_not_null(array);
	cff_assert_param_less(index, array->lenght);

	cff_container_remove((cff_container*)array, index, array->lenght);
}

cff_err_e cff_array_copy(cff_array* array, cff_array* ptr_out, uint64_t start, uint64_t count, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_less((start + count), array->lenght);
	
	return cff_container_copy((cff_container*)array, (cff_container*)ptr_out, start, count, array->lenght, &ptr_out->lenght, allocator);

}

cff_err_e cff_array_clone(cff_array* array, cff_array* ptr_out, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_out);

	cff_err_e err = cff_container_clone((cff_container*)array, (cff_container*)ptr_out, array->lenght, allocator);

	if (err == CFF_NONE_ERR) {
		ptr_out->lenght = array->lenght;
	}
	return err;
}

void cff_array_fill(cff_array* array, uintptr_t ptr_in) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);

	cff_container_fill((cff_container*)array, ptr_in, array->lenght);
}

cff_err_e cff_array_join(cff_array* array, cff_array* other, uint64_t start_at, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(other);
	cff_assert_param_less(start_at, array->lenght);

	cff_err_e err = cff_container_join((cff_container*)array, (cff_container*)other, start_at, array->lenght, other->lenght, allocator);

	if (err == CFF_NONE_ERR) {
		array->lenght += other->lenght;
	}
	return err;
}

cff_err_e cff_array_reverse(cff_array* array) {
	cff_assert_param_not_null(array);

	return cff_container_reverse((cff_container*)array, array->lenght);
}

cff_err_e cff_array_filter(cff_array* array, filter_fn filter_function, cff_array* ptr_out, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_not_null(filter_function);

	return cff_container_filter((cff_container*)array, filter_function, (cff_container*)ptr_out, array->lenght, &ptr_out->lenght, allocator);
}

cff_err_e cff_array_map(cff_array* array, map_fn map_function, cff_array* ptr_out, uint64_t out_data_size, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_out);
	cff_assert_param_not_null(map_function);
	cff_assert_param_not_zero(out_data_size);


	cff_err_e err = cff_container_map((cff_container*)array, map_function, (cff_container*)ptr_out, out_data_size, array->lenght, allocator);
	if (err == CFF_NONE_ERR) {
		ptr_out->lenght = array->lenght;
	}
	return err;
}

void cff_array_foreach(cff_array* array, foreach_fn foreach_function) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(foreach_function);

	cff_container_foreach((cff_container*)array, foreach_function, array->lenght);
}

cff_err_e cff_array_sort(cff_array* array, comparer_fn comparer_function) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(comparer_function);

	return cff_container_sort((cff_container*)array, comparer_function, array->lenght);
}

void cff_array_free(cff_array* array, AllocatorInterface* allocator) {
	cff_assert_param_not_null(array);

	cff_container_free((cff_container*)array, allocator);
}

uint8_t cff_array_equal(cff_array* array, cff_array* other) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(other);

	return cff_container_equal((cff_container*)array, (cff_container*)other, array->lenght);
}

uint8_t cff_array_find(cff_array* array, uintptr_t ptr_in, uint64_t* out_index) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(out_index);

	return cff_container_find((cff_container*)array, ptr_in, out_index, array->lenght);
}

uint8_t cff_array_find_cmp(cff_array* array, uintptr_t ptr_in, uint64_t* out_index, comparer_fn comparer_function) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(comparer_function);
	cff_assert_param_not_null(out_index);

	return cff_container_find_cmp((cff_container*)array, ptr_in, out_index, comparer_function, array->lenght);
}

uint64_t cff_array_count(cff_array* array, uintptr_t ptr_in) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);


	return cff_container_count((cff_container*)array, ptr_in, array->lenght);
}

uint64_t cff_array_count_cmp(cff_array* array, uintptr_t ptr_in, comparer_fn comparer_function) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(comparer_function);

	return cff_container_count_cmp((cff_container*)array, ptr_in, comparer_function, array->lenght);
}

uint8_t cff_array_any(cff_array* array, uintptr_t ptr_in) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);

	return cff_container_any((cff_container*)array, ptr_in, array->lenght);
}

uint8_t cff_array_any_cmp(cff_array* array, uintptr_t ptr_in, comparer_fn comparer_function) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(comparer_function);

	return cff_container_any_cmp((cff_container*)array, ptr_in, comparer_function, array->lenght);
}

uint8_t cff_array_all(cff_array* array, uintptr_t ptr_in) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);

	return cff_container_all((cff_container*)array, ptr_in, array->lenght);
}

uint8_t cff_array_all_cmp(cff_array* array, uintptr_t ptr_in, comparer_fn comparer_function) {
	cff_assert_param_not_null(array);
	cff_assert_param_not_null(ptr_in);
	cff_assert_param_not_null(comparer_function);

	return cff_container_all_cmp((cff_container*)array, ptr_in, comparer_function, array->lenght);
}

