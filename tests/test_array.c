#include "caffeine_array.h""
#include "test_defs.h"

void array_arange(cff_array* arr, int start, int end) {
	uint64_t c = 0;
	for (int i = start; i < end; i++)
	{
		test_data dt = data_new_at_index(i);
		cff_array_set(arr, c, &dt);
		c++;
	}
}

void array_arange_rand(cff_array* arr, int start, int end) {
	uint64_t c = 0;
	for (int i = start; i < end; i++)
	{
		test_data dt = data_new();
		cff_array_set(arr, c, &dt);
		c++;
	}
}

TESTDEF(array_create) {
	cff_array* array = (cff_array*)munit_data;

	SKIP_ON_ERR(cff_array_create(array, DATA_SIZE, INI_LEN, NULL));

	munit_assert(array->buffer != 0);
	munit_assert_int64(array->data_size, == , DATA_SIZE);

	return MUNIT_OK;
}

TESTDEF(array_set) {
	cff_array* array = (cff_array*)munit_data;


	uint64_t index = (uint64_t)munit_rand_int_range(0, (int)(INI_LEN - 1));

	test_data data = data_new();

	cff_array_set(array, (uint64_t)index, (uintptr_t)(&data));

	test_data get_data = ((test_data*)array->buffer)[index];

	ASSERT_EQUALS(get_data, data);
	return MUNIT_OK;
}

TESTDEF(array_get) {
	cff_array* array = (cff_array*)munit_data;

	test_data data = data_new();

	int index = munit_rand_int_range(0, (int)(INI_LEN - 1));

	cff_array_set(array, (uint64_t)index, (uintptr_t)(&data));

	test_data get_data = { 0 };

	cff_array_get(array, (uint64_t)index, (uintptr_t)(&get_data));

	ASSERT_EQUALS(get_data, data);
	return MUNIT_OK;
}

TESTDEF(array_resize) {
	cff_array* array = (cff_array*)munit_data;

	SKIP_ON_ERR(cff_array_resize(array, INI_LEN * 2, NULL));

#ifdef CFF_COMP_MSVC
	size_t allocked = _msize((void*)array->buffer);
	munit_assert(allocked == INI_LEN * 2 * array->data_size);
#endif

	return MUNIT_OK;
}

TESTDEF(array_insert) {
	cff_array* array = (cff_array*)munit_data;

	array_arange(array, 0, (int)INI_LEN);

	test_data data = data_new();

	test_data get_data = { 0 };

	int insert_index = munit_rand_int_range(0, INI_LEN - 1);

	cff_array_insert(array, insert_index, (uintptr_t)(&data));

	cff_array_get(array, insert_index, (uintptr_t)(&get_data));

	ASSERT_EQUALS(get_data, data);
	return MUNIT_OK;
}

TESTDEF(array_remove) {
	cff_array* array = (cff_array*)munit_data;

	array_arange(array, 0, (int)INI_LEN);

	int index_remove = munit_rand_int_range(0, INI_LEN - 2);

	test_data get_data[2] = { 0 };

	cff_array_get(array, index_remove + 1, (uintptr_t)(&get_data[0]));

	cff_array_remove(array, index_remove);

	cff_array_get(array, index_remove, (uintptr_t)(&get_data[1]));

	ASSERT_EQUALS(get_data[0], get_data[1]);
	return MUNIT_OK;
}

TESTDEF(array_copy) {
	cff_array* array = (cff_array*)munit_data;

	array_arange(array, 0, (int)INI_LEN);

	cff_array dest = { 0 };
	uint64_t start = munit_rand_int_range(0, INI_LEN / 2);
	uint64_t count = munit_rand_int_range(0, INI_LEN - start);

	SKIP_ON_ERR(cff_array_copy(array, &dest, start, count, NULL));

	for (uint64_t i = start, j = 0; i < start + count; i++, j++)
	{
		test_data a = { 0 };
		test_data b = { 0 };
		cff_array_get(array, i, (uintptr_t)(&a));
		cff_array_get(&dest, j, (uintptr_t)(&b));
		ASSERT_EQUALS(a, b);
	}
	cff_array_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(array_clone) {
	cff_array* array = (cff_array*)munit_data;

	array_arange(array, 0, (int)INI_LEN);

	cff_array dest = { 0 };

	SKIP_ON_ERR(cff_array_clone(array, &dest, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data a = { 0 };
		test_data b = { 0 };
		cff_array_get(array, i, (uintptr_t)(&a));
		cff_array_get(&dest, i, (uintptr_t)(&b));
		ASSERT_EQUALS(a, b);
	}
	cff_array_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(array_reverse) {
	cff_array* array = (cff_array*)munit_data;

	array_arange(array, 0, (int)INI_LEN);

	cff_array dest = { 0 };

	SKIP_ON_ERR(cff_array_clone(array, &dest, NULL));

	SKIP_ON_ERR(cff_array_reverse(array));

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data[2] = { 0 };
		cff_array_get(array, i, (uintptr_t)(&data[0]));
		cff_array_get(&dest, (uint64_t)(INI_LEN - i - 1), (uintptr_t)(&data[1]));
		ASSERT_EQUALS(data[0], data[1]);
	}

	cff_array_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(array_fill) {
	cff_array* array = (cff_array*)munit_data;

	test_data data = data_new();

	cff_array_fill(array, (uintptr_t)(&data));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data out = { 0 };
		cff_array_get(array, i, (uintptr_t)(&out));
		ASSERT_EQUALS(data, out);
	}

	return MUNIT_OK;
}

TESTDEF(array_join) {
	cff_array* array = (cff_array*)munit_data;

	cff_array other = { 0 };
	SKIP_ON_ERR(cff_array_create(&other, DATA_SIZE, INI_LEN / 2, NULL));

	array_arange(array, 0, (int)INI_LEN / 2);
	array_arange(&other, (int)INI_LEN / 2, (int)INI_LEN);

	SKIP_ON_ERR(cff_array_join(array, &other, INI_LEN / 2, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		test_data out = { 0 };
		cff_array_get(array, i, (uintptr_t)(&out));
		ASSERT_EQUALS(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(array_filter) {
	cff_array* array = (cff_array*)munit_data;

	cff_array other = { 0 };

	array_arange(array, 0, (int)INI_LEN);


	SKIP_ON_ERR(cff_array_filter(array, filter, &other, NULL));

	for (size_t i = 0; i < other.lenght; i++)
	{
		test_data out = { 0 };
		cff_array_get(&other, i, (uintptr_t)(&out));
		munit_assert(validate_filter(out, i));
	}

	if (other.lenght) cff_array_free(&other, NULL);
	return MUNIT_OK;
}

TESTDEF(array_map) {
	cff_array* array = (cff_array*)munit_data;

	cff_array other = { 0 };

	array_arange(array, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_array_map(array, map, &other, sizeof(int), NULL));


	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = { 0 };
		int sum = 0;
		cff_array_get(array, (uint64_t)i, (uintptr_t)(&data));
		cff_array_get(&other, (uint64_t)i, (uintptr_t)&sum);

		munit_assert(validate_map(data, sum, i));
	}

	return MUNIT_OK;
}

TESTDEF(array_foreach) {
	cff_array* array = (cff_array*)munit_data;

	array_arange(array, 0, (int)INI_LEN);
	cff_array_foreach(array, foreach);

	for (size_t i = 0; i < array->lenght; i++)
	{
		test_data out = { 0 };
		cff_array_get(array, i, (uintptr_t)(&out));
		munit_assert(validate_foreach(out, i));
	}

	return MUNIT_OK;
}

TESTDEF(array_sort) {
	cff_array* array = (cff_array*)munit_data;

	array_arange_rand(array, 0, (int)INI_LEN);

	SKIP_ON_ERR(cff_array_sort(&array, compare));

	for (uint64_t i = 1; i < array->lenght; i++)
	{
		test_data data[2] = { 0 };
		cff_array_get(array, i - 1, (uintptr_t)(&(data[0])));
		cff_array_get(array, i, (uintptr_t)((&data[1])));

		ASSERT_LESS_EQ(data[0], data[1]);
	}

	return MUNIT_OK;
}

TESTDEF(array_free) {
	cff_array* array = (cff_array*)munit_data;

	cff_array_free(array, NULL);
	munit_assert(array->data_size == 0);
	munit_assert(array->buffer == 0);
	free(array);
	return MUNIT_OK;
}

TESTDEF(array_equal) {
	cff_array* array = (cff_array*)munit_data;

	cff_array other;
	SKIP_ON_ERR(cff_array_create(&other, DATA_SIZE, INI_LEN, NULL));

	array_arange(array, 0, (int)INI_LEN);
	array_arange(&other, 0, (int)INI_LEN);

	uint8_t eq = cff_array_equal(array, &other);
	cff_array_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(array_find) {
	cff_array* array = (cff_array*)munit_data;

	array_arange_rand(array, 0, (int)INI_LEN);

	int index = munit_rand_int_range(0, INI_LEN - 1);

	test_data data = ((test_data*)array->buffer)[index];

	uint64_t found = 0;

	uint8_t f = cff_array_find(array, (uintptr_t)(&data), &found);

	munit_assert(f);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(array_find_cmp) {
	cff_array* array = (cff_array*)munit_data;

	array_arange_rand(array, 0, (int)INI_LEN);

	int index = munit_rand_int_range(0, INI_LEN - 1);

	test_data data = ((test_data*)array->buffer)[index];

	uint64_t found = 0;

	cff_array_find_cmp(array, (uintptr_t)(&data), &found, compare);

	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(array_count) {
	cff_array* array = (cff_array*)munit_data;

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cc += i % 2;
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	test_data data = data_new_at_index(1);
	uint64_t count = cff_array_count(array, (uintptr_t)(&data));
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(array_count_cmp) {
	cff_array* array = (cff_array*)munit_data;

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cc += i % 2;
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	test_data data = data_new_at_index(1);
	uint64_t count = cff_array_count_cmp(array, (uintptr_t)(&data), compare);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(array_any) {
	cff_array* array = (cff_array*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_array_any(array, (uintptr_t)(&data));
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(array_any_cmp) {
	cff_array* array = (cff_array*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_array_any_cmp(array, (uintptr_t)(&data), compare);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(array_all) {
	cff_array* array = (cff_array*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_array_all(array, (uintptr_t)(&data));
	munit_assert_false(exist);
	return MUNIT_OK;
}

TESTDEF(array_all_cmp) {
	cff_array* array = (cff_array*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_array_set(array, i, (uintptr_t)(&data));
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_array_all_cmp(array, (uintptr_t)(&data), compare);
	munit_assert_false(exist);
	return MUNIT_OK;
}


static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_array* array = malloc(sizeof(cff_array));
	if (array) *array = (cff_array){ 0 };
	return array;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_array* array = malloc(sizeof(cff_array));
	cff_array_create(array, DATA_SIZE, INI_LEN, NULL);
	return array;
}

static void test_tear_down(void* fixture) {
	cff_array_free(fixture, NULL);
	free(fixture);
}


int test_array(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/test_create", test_array_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(array_set),
		TEST(array_get),
		TEST(array_resize),
		TEST(array_insert),
		TEST(array_remove),
		TEST(array_copy),
		TEST(array_clone),
		TEST(array_reverse),
		TEST(array_fill),
		TEST(array_join),
		TEST(array_filter),
		TEST(array_map),
		TEST(array_foreach),
	//	TEST(array_sort),
		{ "/test_free", test_array_free, test_setup, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(array_equal),
		TEST(array_find),
		TEST(array_find_cmp),
		TEST(array_count),
		TEST(array_count_cmp),
		TEST(array_any),
		TEST(array_any_cmp),
		TEST(array_all),
		TEST(array_all_cmp),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/array", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}