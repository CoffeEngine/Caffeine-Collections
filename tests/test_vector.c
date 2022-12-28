#include "caffeine_vector.h"
#include "test_defs.h"


TESTDEF(vector_create) {
	cff_vector* vector = (cff_vector*)munit_data;

	cff_vector_create(vector, DATA_SIZE, INI_LEN, NULL);

	munit_assert_not_null((void*)vector->buffer);
	munit_assert(vector->count == 0);
	munit_assert(vector->lenght == INI_LEN);
	munit_assert(vector->data_size == DATA_SIZE);

	return MUNIT_OK;
}

TESTDEF(vector_free) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	cff_vector_free(vector, NULL);

	munit_assert_null((void*)vector->buffer);
	munit_assert(vector->count == 0);
	munit_assert(vector->lenght == 0);
	munit_assert(vector->data_size == 0);

	return MUNIT_OK;
}

TESTDEF(vector_resize) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	int n_size = (int)INI_LEN * 2;
	cff_vector_resize(vector, n_size, NULL);

	munit_assert(vector->count == 0);
	munit_assert(vector->lenght == INI_LEN * 2);
	munit_assert(vector->data_size == DATA_SIZE);

	return MUNIT_OK;
}

TESTDEF(vector_get) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	int rnd_value = munit_rand_uint32();
	test_data value = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

	*((test_data*)vector->buffer) = value;
	vector->count = 1;

	test_data out= {0};
	cff_vector_get(vector, 0, (uintptr_t)&out);

	ASSERT_EQUALS(value, out);

	return MUNIT_OK;
}

TESTDEF(vector_set) {
cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN - 1; i++)
	{
		int rnd_value = munit_rand_uint32();
		test_data value = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

		cff_vector_set(vector, (uintptr_t)&value, i);

		test_data out= {0};
		cff_vector_get(vector, i, (uintptr_t)&out);

		ASSERT_EQUALS(value, out);
	}

	return MUNIT_OK;
}

TESTDEF(vector_insert) {
cff_vector* vector = (cff_vector*)munit_data;
	
	int rnd_value = munit_rand_uint32();
	test_data value1 = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

	rnd_value = munit_rand_uint32();
	test_data value2 = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

	cff_vector_insert(vector, (uintptr_t)&value1, 0);
	cff_vector_insert(vector, (uintptr_t)&value2, 0);

	test_data out= {0};
	cff_vector_get(vector, 1, (uintptr_t)&out);
	ASSERT_EQUALS(value1, out);

	cff_vector_get(vector, 0, (uintptr_t)&out);
	ASSERT_EQUALS(value2, out);

	return MUNIT_OK;
}

TESTDEF(vector_remove) {
cff_vector* vector = (cff_vector*)munit_data;
	
	int rnd_value = munit_rand_uint32();
	test_data value1 = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

	rnd_value = munit_rand_uint32();
	test_data value2 = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

	cff_vector_insert(vector, (uintptr_t)&value1, 0);
	cff_vector_insert(vector, (uintptr_t)&value2, 0);

	cff_vector_remove(vector, 0, NULL);

	test_data out= {0};
	cff_vector_get(vector, 0, (uintptr_t)&out);
	ASSERT_EQUALS(value1, out);

	return MUNIT_OK;
}

TESTDEF(vector_copy) {
cff_vector* vector = (cff_vector*)munit_data;
	
	cff_vector tmp_vec;
	for (size_t i = 0; i < INI_LEN - 1; i++)
	{
		int rnd_value = munit_rand_uint32();
		test_data value = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

		cff_vector_set(vector, (uintptr_t)&value, i);
	}

	cff_vector_create(&tmp_vec, vector->data_size, INI_LEN / 2, NULL);
	cff_vector_copy(vector, &tmp_vec, 0, INI_LEN / 2, NULL);

	for (size_t i = 0; i < INI_LEN / 2; i++)
	{
		test_data out1 = { 0 }, out2 = {0};

		cff_vector_get(vector, i, (uintptr_t)&out1);
		cff_vector_get(&tmp_vec, i, (uintptr_t)&out2);

		ASSERT_EQUALS(out1, out2);
	}

	cff_vector_free(&tmp_vec, NULL);
	return MUNIT_OK;
}

TESTDEF(vector_clone) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	cff_vector tmp_vec;
	for (size_t i = 0; i < INI_LEN - 1; i++)
	{
		int rnd_value = munit_rand_uint32();
		test_data value = { .x = rnd_value,.y = rnd_value,.z = rnd_value };

		cff_vector_set(vector, (uintptr_t)&value, i);
	}
	cff_vector_create(&tmp_vec, vector->data_size, INI_LEN, NULL);
	cff_vector_clone(vector, &tmp_vec, NULL);

	for (size_t i = 0; i < INI_LEN - 1; i++)
	{
		test_data out1 = { 0 }, out2 = {0};

		cff_vector_get(vector, i, (uintptr_t)&out1);
		cff_vector_get(&tmp_vec, i, (uintptr_t)&out2);

		ASSERT_EQUALS(out1, out2);
	}

	cff_vector_free(&tmp_vec, NULL);
	return MUNIT_OK;
}

TESTDEF(vector_fill) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	int v = munit_rand_uint32();
	test_data data = { .x = v, .y = 3 * v, .z = 7 * v };
	cff_vector_fill(vector, (uintptr_t)&data);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data out= {0};
		cff_vector_get(vector, i, (uintptr_t)&out);
		ASSERT_EQUALS(data, out);
	}

	return MUNIT_OK;
}

TESTDEF(vector_join) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	cff_vector vector2;
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_set(vector, (uintptr_t)&data, i);
	}
	cff_vector_create(&vector2, DATA_SIZE, INI_LEN, NULL);
	for (int i = (int)INI_LEN; i < (int)INI_LEN * 2; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_set(&vector2, (uintptr_t)&data, i - INI_LEN);
	}

	cff_vector_join(vector, &vector2, NULL);

	for (int i = 0; i < (int)INI_LEN * 2; i++)
	{
		test_data data = {0};
		cff_vector_get(vector, i, (uintptr_t)&data);
		munit_assert(data.x == i);
	}

	cff_vector_free(&vector2, NULL);

	return MUNIT_OK;
}

TESTDEF(vector_reverse) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_set(vector, (uintptr_t)&data, i);
	}
	cff_vector_reverse(vector);

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = {0};
		cff_vector_get(vector, i, (uintptr_t)&data);
		munit_assert(data.x == (INI_LEN - 1) - i);
	}

	return MUNIT_OK;
}

TESTDEF(vector_filter) {
cff_vector* vector = (cff_vector*)munit_data;
	
	cff_vector vector2;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_set(vector, (uintptr_t)&data, i);
	}

	cff_vector_filter(vector, filter, &vector2, NULL);

	for (size_t i = 0; i < vector2.count; i++)
	{
		test_data out= {0};
		cff_vector_get(&vector2, i, (uintptr_t)&out);
		munit_assert(validate_filter(out, i));
	}

	if (vector2.count > 0) cff_vector_free(&vector2, NULL);

	return MUNIT_OK;
}

TESTDEF(vector_push_back) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	munit_assert(vector->lenght == INI_LEN * 2);

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		test_data out= {0};
		cff_vector_get(vector, i, (uintptr_t)&out);
		munit_assert(out.x == i);
	}

	return MUNIT_OK;
}

TESTDEF(vector_push_front) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_push_front(vector, (uintptr_t)&data, NULL);
	}

	munit_assert(vector->lenght == INI_LEN * 2);

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		test_data out= {0};
		cff_vector_get(vector, i, (uintptr_t)&out);
		munit_assert(out.x == ((INI_LEN * 2) - 1) - i);
	}

	return MUNIT_OK;
}

TESTDEF(vector_pop_back) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	munit_assert(vector->lenght == INI_LEN * 2);

	for (int i = (int)(INI_LEN * 2) - 1; i >= 0; --i)
	{
		test_data out= {0};
		cff_vector_pop_back(vector, (uintptr_t)&out, NULL);
		munit_assert(out.x == i);
	}

	return MUNIT_OK;
}

TESTDEF(vector_pop_front) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		test_data data = { .x = i, .y = i, .z = i };
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	munit_assert(vector->lenght == INI_LEN * 2);

	for (size_t i = 0; i < INI_LEN * 2; i++)
	{
		test_data out = { .x = i, .y = i, .z = i };
		cff_vector_pop_front(vector, (uintptr_t)&out, NULL);
		munit_assert(out.x == i);
	}

	return MUNIT_OK;
}

TESTDEF(vector_map) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	cff_vector len_vector;

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = munit_rand_int_range(0,100),
			.y = munit_rand_int_range(0,100),
			.z = munit_rand_int_range(0,100)
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	cff_vector_map(vector, map, &len_vector, sizeof(int), NULL);

	for (size_t i = 0; i < INI_LEN; i++) {
		test_data v = {0};
		int l = {0};
		cff_vector_get(vector, i, (uintptr_t)&v);
		cff_vector_get(&len_vector, i, (uintptr_t)&l);

		
		munit_assert(validate_map(v,l,i));
	}

	cff_vector_free(&len_vector, NULL);
	return MUNIT_OK;
}

TESTDEF(vector_foreach) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i + 1,
			.z = i + 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	cff_vector_foreach(vector, foreach);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {0};
		cff_vector_get(vector, i, (uintptr_t)&data);

		munit_assert(validate_foreach(data,i));
	}

	return MUNIT_OK;
}

TESTDEF(vector_sort) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i + 1,
			.z = i + 2
		};
		cff_vector_push_front(vector, (uintptr_t)&data, NULL);
	}

	cff_vector_sort(vector, compare);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {0};
		cff_vector_get(vector, i, (uintptr_t)&data);
		munit_assert(data.x == i);
	}

	return MUNIT_OK;
}

TESTDEF(vector_clear) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i + 1,
			.z = i + 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	cff_vector_clear(vector);

	munit_assert(vector->count == 0);

	for (int i = (int)INI_LEN; i < INI_LEN * 2; i++)
	{
		test_data data = {
			.x = i,
			.y = i + 1,
			.z = i + 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = {0};
		cff_vector_get(vector, i, (uintptr_t)&data);

		munit_assert(data.x = (int)(i + INI_LEN));
	}

	return MUNIT_OK;
}

TESTDEF(vector_equal) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	cff_vector vector2;

	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i + 1,
			.z = i + 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	cff_vector_clone(vector, &vector2, NULL);

	uint8_t eq = cff_vector_equal(vector, &vector2);

	munit_assert(eq);

	cff_vector_free(&vector2, NULL);
	return MUNIT_OK;
}

TESTDEF(vector_find) {
cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i + 1,
			.z = i + 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data_ok = {
		.x = 0,
		.y = 1,
		.z = 2
	};
	uint64_t ok_index = -1;

	test_data data_nok = {
		.x = 0,
		.y = 0,
		.z = 0
	};
	uint64_t nok_index = -1;

	uint8_t f_ok = cff_vector_find(vector, (uintptr_t)&data_ok, &ok_index);
	uint8_t f_nok = cff_vector_find(vector, (uintptr_t)&data_nok, &nok_index);

	munit_assert(f_ok);
	munit_assert(ok_index == 0);

	munit_assert(!f_nok);
	munit_assert(nok_index == -1);

	return MUNIT_OK;
}

TESTDEF(vector_find_cmp) {
cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i + 1,
			.z = i + 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data_ok = {
		.x = 0,
		.y = 1,
		.z = 2
	};
	uint64_t ok_index = -1;

	test_data data_nok = {
		.x = 0,
		.y = 0,
		.z = 0
	};
	uint64_t nok_index = -1;

	uint8_t f_ok = cff_vector_find_cmp(vector, (uintptr_t)&data_ok, &ok_index, compare);
	uint8_t f_nok = cff_vector_find_cmp(vector, (uintptr_t)&data_nok, &nok_index, compare);

	munit_assert(f_ok);
	munit_assert(ok_index == 0);

	munit_assert(!f_nok);
	munit_assert(nok_index == -1);

	return MUNIT_OK;
}

TESTDEF(vector_count) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = i % 2,
			.y = i % 2,
			.z = i % 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	test_data data2 = {
		.x = 2,
		.y = 0,
		.z = 0
	};

	uint64_t count = cff_vector_count(vector, (uintptr_t)&data);
	uint64_t count2 = cff_vector_count(vector, (uintptr_t)&data2);

	munit_assert(count == INI_LEN/2);
	munit_assert(count2 == 0);

	return MUNIT_OK;
}

TESTDEF(vector_count_cmp) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = i % 2,
			.y = i % 2,
			.z = i % 2
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	test_data data2 = {
		.x = 2,
		.y = 0,
		.z = 0
	};

	uint64_t count = cff_vector_count_cmp(vector, (uintptr_t)&data, compare);
	uint64_t count2 = cff_vector_count_cmp(vector, (uintptr_t)&data2, compare);

	munit_assert(count == INI_LEN/2);
	munit_assert(count2 == 0);

	return MUNIT_OK;
}

TESTDEF(vector_any) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i,
			.z = i
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	uint8_t result = cff_vector_any(vector, (uintptr_t)&data);

	munit_assert(result);

	return MUNIT_OK;
}

TESTDEF(vector_any_cmp) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (int i = 0; i < (int)INI_LEN; i++)
	{
		test_data data = {
			.x = i,
			.y = i,
			.z = i
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	uint8_t result = cff_vector_any_cmp(vector, (uintptr_t)&data,compare);

	munit_assert(result);

	return MUNIT_OK;
}

TESTDEF(vector_all) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = 5,
			.y = 5,
			.z = 5
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data = {
		.x = 5,
		.y = 5,
		.z = 5
	};

	test_data data2 = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	uint8_t result1 = cff_vector_all(vector, (uintptr_t)&data);
	uint8_t result2 = cff_vector_all(vector, (uintptr_t)&data2);

	munit_assert(result1);
	munit_assert(!result2);

	return MUNIT_OK;
}

TESTDEF(vector_all_cmp) {
	cff_vector* vector = (cff_vector*)munit_data;
	
	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = {
			.x = 5,
			.y = 5,
			.z = 5
		};
		cff_vector_push_back(vector, (uintptr_t)&data, NULL);
	}

	test_data data = {
		.x = 5,
		.y = 5,
		.z = 5
	};

	test_data data2 = {
		.x = 0,
		.y = 0,
		.z = 0
	};

	uint8_t result1 = cff_vector_all_cmp(vector, (uintptr_t)&data, compare);
	uint8_t result2 = cff_vector_all_cmp(vector, (uintptr_t)&data2, compare);

	munit_assert(result1);
	munit_assert(!result2);

	return MUNIT_OK;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_vector* vector = malloc(sizeof(cff_vector));
	if (vector) *vector = (cff_vector){ 0 };
	return vector;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_vector* vector = malloc(sizeof(cff_vector));
	cff_vector_create(vector, DATA_SIZE, INI_LEN, NULL);
	return vector;
}

static void test_tear_down(void* fixture) {
	cff_vector_free(fixture, NULL);
	free(fixture);
}

int test_vector(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/vector_create", test_vector_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		{ "/vector_free", test_vector_free, test_setup, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(vector_resize),
		TEST(vector_get),
		TEST(vector_set),
		TEST(vector_insert),
		TEST(vector_remove),
		TEST(vector_copy),
		TEST(vector_clone),
		TEST(vector_fill),
		TEST(vector_join),
		TEST(vector_reverse),
		TEST(vector_filter),
		TEST(vector_push_back),
		TEST(vector_push_front),
		TEST(vector_pop_back),
		TEST(vector_pop_front),
		TEST(vector_map),
		TEST(vector_foreach),
		TEST(vector_sort),
		TEST(vector_clear),
		TEST(vector_find),
		TEST(vector_find_cmp),
		TEST(vector_count),
		TEST(vector_count_cmp),
		TEST(vector_any),
		TEST(vector_any_cmp),
		TEST(vector_all),
		TEST(vector_all_cmp),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/vector", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}