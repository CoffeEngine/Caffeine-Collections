#include "test_defs.h"
#include "caffeine_container.h"




static void container_arange(cff_container* container, int start, int end) {
	for (int i = start, j = 0; i < end; i++, j++)
	{
		test_data data = data_new_at_index(i);
		cff_container_set(container, j, (uintptr_t)(&data), INI_LEN);
	}
}

TESTDEF(container_create) {
	cff_container* container = (cff_container*)munit_data;

	SKIP_ON_ERR(cff_container_create(container, DATA_SIZE, INI_LEN, NULL));

	munit_assert(container->buffer != 0);
	munit_assert_int64(container->data_size, == , DATA_SIZE);
	return MUNIT_OK;
}

TESTDEF(container_set) {
	cff_container* container = (cff_container*)munit_data;

	int index = munit_rand_int_range(0, (int)(INI_LEN - 1));

	test_data data = data_new();

	cff_container_set(container, (uint64_t)index, (uintptr_t)(&data), INI_LEN);

	test_data get_data = ((test_data*)container->buffer)[index];

	ASSERT_EQUALS(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_get) {
	cff_container* container = (cff_container*)munit_data;

	int index = munit_rand_int_range(0, (int)(INI_LEN - 1));

	test_data data = data_new();

	cff_container_set(container, (uint64_t)index, (uintptr_t)(&data), INI_LEN);

	test_data get_data = { 0 };

	cff_container_get(container, (uint64_t)index, (uintptr_t)(&get_data), INI_LEN);

	ASSERT_EQUALS(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_desloc) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	int index = 3;
	int step = 2;
	cff_container_desloc(container, (uint64_t)index, (int64_t)step, INI_LEN);
	test_data get_data = { 0 };
	cff_container_get(container, (uint64_t)index + step, (uintptr_t)(&get_data), INI_LEN);
	test_data data = data_new_at_index(index);
	ASSERT_EQUALS(get_data, data);


	index = 3;
	step = -2;
	cff_container_desloc(container, (uint64_t)index, (int64_t)step, INI_LEN);
	cff_container_get(container, (uint64_t)index + step, (uintptr_t)(&get_data), INI_LEN);
	data = data_new_at_index(index);
	ASSERT_EQUALS(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_resize) {
	cff_container* container = (cff_container*)munit_data;

	SKIP_ON_ERR(cff_container_resize(container, INI_LEN * 2, NULL));

#ifdef CFF_COMP_MSVC
	size_t allocked = _msize((void*)container->buffer);
	munit_assert(allocked == INI_LEN * 2 * container->data_size);
#endif

	return MUNIT_OK;
}

TESTDEF(container_insert) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	test_data data = data_new();
	test_data get_data = { 0 };
	int insert_index = munit_rand_int_range(0, INI_LEN - 1);
	cff_container_insert(container, insert_index, (uintptr_t)(&data), INI_LEN);
	cff_container_get(container, insert_index, (uintptr_t)(&get_data), INI_LEN);

	ASSERT_EQUALS(get_data, data);
	return MUNIT_OK;
}

TESTDEF(container_remove) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	int index_remove = munit_rand_int_range(0, INI_LEN - 2);

	test_data get_data[2] = { 0 };

	cff_container_get(container, index_remove + 1, (uintptr_t)(&get_data[0]), INI_LEN);

	uint8_t res = cff_container_remove(container, index_remove, INI_LEN);

	cff_container_get(container, index_remove, (uintptr_t)(&get_data[1]), INI_LEN);

	munit_assert_false(index_remove != (INI_LEN - 1) && res == 0);
	munit_assert_false(index_remove == (INI_LEN - 1) && res == 1);

	if (res) ASSERT_EQUALS(get_data[0], get_data[1]);

	return MUNIT_OK;
}

TESTDEF(container_copy) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	cff_container dest = { 0 };
	uint64_t start = munit_rand_int_range(0, INI_LEN / 2);
	uint64_t count = munit_rand_int_range(0, INI_LEN - start);

	uint64_t n_len = 0;

	SKIP_ON_ERR(cff_container_copy(container, &dest, start, count, INI_LEN, &n_len, NULL));

	for (uint64_t i = start, j = 0; i < (start + count); i++, j++)
	{
		test_data a = { 0 };
		test_data b = { 0 };
		cff_container_get(container, i, (uintptr_t)(&a), INI_LEN);
		cff_container_get(&dest, j, (uintptr_t)(&b), n_len);
		ASSERT_EQUALS(a, b);
	}

	cff_container_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(container_clone) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	cff_container dest = { 0 };

	SKIP_ON_ERR(cff_container_clone(container, &dest, INI_LEN, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data a = { 0 };
		test_data b = { 0 };
		cff_container_get(container, i, (uintptr_t)(&a), INI_LEN);
		cff_container_get(&dest, i, (uintptr_t)(&b), INI_LEN);
		ASSERT_EQUALS(a, b);
	}
	cff_container_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(container_reverse) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	cff_container dest = { 0 };

	
	SKIP_ON_ERR(cff_container_clone(container, &dest, INI_LEN, NULL));

	SKIP_ON_ERR(cff_container_reverse(container, INI_LEN));

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data[2] = { 0 };
		cff_container_get(container, i, (uintptr_t)(&data[0]), INI_LEN);
		cff_container_get(&dest, (uint64_t)(INI_LEN - i - 1), (uintptr_t)(&data[1]), INI_LEN);
		ASSERT_EQUALS(data[0], data[1]);
	}

	cff_container_free(&dest, NULL);
	return MUNIT_OK;
}

TESTDEF(container_fill) {
	cff_container* container = (cff_container*)munit_data;

	test_data data = data_new();

	cff_container_fill(container, (uintptr_t)(&data), INI_LEN);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data out = { 0 };
		cff_container_get(container, i, (uintptr_t)(&out), INI_LEN);
		ASSERT_EQUALS(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(container_join) {
	cff_container* container = (cff_container*)munit_data;

	cff_container other = { 0 };
	SKIP_ON_ERR(cff_container_create(&other, DATA_SIZE, INI_LEN / 2, NULL));

	container_arange(container, 0, (int)(INI_LEN / 2));
	container_arange(&other, (int)(INI_LEN / 2), (int)(INI_LEN));

	SKIP_ON_ERR(cff_container_join(container, &other, INI_LEN / 2, INI_LEN, INI_LEN / 2, NULL));

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i);
		test_data out = { 0 };
		cff_container_get(container, i, (uintptr_t)(&out), INI_LEN);
		ASSERT_EQUALS(data, out);
	}
	return MUNIT_OK;
}

TESTDEF(container_filter) {
	cff_container* container = (cff_container*)munit_data;

	cff_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);

	uint64_t f_len = 0;
	SKIP_ON_ERR(cff_container_filter(container, filter, &other, INI_LEN, &f_len, NULL));

	for (size_t i = 0; i < f_len; i++)
	{
		test_data out = { 0 };
		cff_container_get(&other, i, (uintptr_t)(&out), f_len);
		munit_assert(validate_filter(out, i));
	}
	cff_container_free(&other, NULL);
	return MUNIT_OK;
}

TESTDEF(container_map) {
	cff_container* container = (cff_container*)munit_data;

	cff_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_container_map(container, map, &other, sizeof(int), INI_LEN, NULL));


	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data data = { 0 };
		int sum = 0;
		cff_container_get(container, i, (uintptr_t)(&data), INI_LEN);
		cff_container_get(&other, (uint64_t)i, (uintptr_t)&sum, INI_LEN);

		assert(validate_map(data, sum, i));
	}

	return MUNIT_OK;
}

TESTDEF(container_foreach) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);
	cff_container_foreach(container, foreach, INI_LEN);

	for (size_t i = 0; i < INI_LEN; i++)
	{
		test_data out = { 0 };
		cff_container_get(container, i, (uintptr_t)(&out),INI_LEN);
		munit_assert(validate_foreach(out, i));
	}

	return MUNIT_OK;
}

TESTDEF(container_sort) {
	cff_container* container = (cff_container*)munit_data;

	cff_container other = { 0 };

	container_arange(container, 0, (int)INI_LEN);
	SKIP_ON_ERR(cff_container_clone(container, &other, INI_LEN, NULL));
	SKIP_ON_ERR(cff_container_reverse(&other, INI_LEN));
	SKIP_ON_ERR(cff_container_sort(&other, compare, INI_LEN));

	uint8_t eq = cff_container_equal(container, &other, INI_LEN);
	cff_container_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(container_free) {
	cff_container* container = (cff_container*)munit_data;

	cff_container_free(container, NULL);
	munit_assert(container->data_size == 0);
	munit_assert(container->buffer == 0);
	free(container);
	return MUNIT_OK;
}

TESTDEF(container_equal) {
	cff_container* container = (cff_container*)munit_data;

	cff_container other;
	SKIP_ON_ERR(cff_container_create(&other, DATA_SIZE, INI_LEN, NULL));

	container_arange(container, 0, (int)INI_LEN);
	container_arange(&other, 0, (int)INI_LEN);

	uint8_t eq = cff_container_equal(container, &other, INI_LEN);
	cff_container_free(&other, NULL);

	munit_assert(eq == 0);
	return MUNIT_OK;
}

TESTDEF(container_find) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	int index = munit_rand_int_range(0, INI_LEN - 1);
	test_data data = data_new_at_index(index);
	uint64_t found = 0;
	uint8_t f = cff_container_find(container, (uintptr_t)(&data), &found, INI_LEN);
	munit_assert(f);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(container_find_cmp) {
	cff_container* container = (cff_container*)munit_data;

	container_arange(container, 0, (int)INI_LEN);

	int index = munit_rand_int_range(0, INI_LEN - 1);
	test_data data = data_new_at_index(index);
	uint64_t found = 0;
	cff_container_find_cmp(container, (uintptr_t)(&data), &found, compare, INI_LEN);
	munit_assert(found == index);
	return MUNIT_OK;
}

TESTDEF(container_count) {
	cff_container* container = (cff_container*)munit_data;

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cc += i % 2;
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	test_data data = data_new_at_index(1);
	uint64_t count = cff_container_count(container, (uintptr_t)(&data), INI_LEN);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(container_count_cmp) {
	cff_container* container = (cff_container*)munit_data;

	uint64_t cc = 0;
	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cc += i % 2;
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	test_data data = data_new_at_index(1);
	uint64_t count = cff_container_count_cmp(container, (uintptr_t)(&data), compare, INI_LEN);
	munit_assert(cc == count);
	return MUNIT_OK;
}

TESTDEF(container_any) {
	cff_container* container = (cff_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_container_any(container, (uintptr_t)(&data), INI_LEN);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(container_any_cmp) {
	cff_container* container = (cff_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_container_any_cmp(container, (uintptr_t)(&data), compare, INI_LEN);
	munit_assert(exist);
	return MUNIT_OK;
}

TESTDEF(container_all) {
	cff_container* container = (cff_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_container_all(container, (uintptr_t)(&data), INI_LEN);
	munit_assert_false(exist);
	return MUNIT_OK;
}

TESTDEF(container_all_cmp) {
	cff_container* container = (cff_container*)munit_data;

	for (int i = 0; i < INI_LEN; i++)
	{
		test_data data = data_new_at_index(i % 2);
		cff_container_set(container, i, (uintptr_t)(&data), INI_LEN);
	}
	test_data data = data_new_at_index(1);
	uint8_t exist = cff_container_all_cmp(container, (uintptr_t)(&data), compare, INI_LEN);
	munit_assert_false(exist);
	return MUNIT_OK;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_container* container = malloc(sizeof(cff_container));
	cff_container_create(container, DATA_SIZE, INI_LEN, NULL);
	return container;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_container* container = malloc(sizeof(cff_container));
	if (container)*container = (cff_container){ 0 };
	return container;
}

static void test_tear_down(void* fixture) {
	cff_container_free(fixture, NULL);
	free(fixture);
}


int test_container(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/test_create", test_container_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(container_set),
		TEST(container_get),
		TEST(container_desloc),
		TEST(container_resize),
		TEST(container_insert),
		TEST(container_remove),
		TEST(container_copy),
		TEST(container_clone),
		TEST(container_reverse),
		TEST(container_fill),
		TEST(container_join),
		TEST(container_filter),
		TEST(container_map),
		TEST(container_foreach),
		TEST(container_sort),
		{ "/test_free", test_container_free, test_setup, NULL, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(container_equal),
		TEST(container_find),
		TEST(container_find_cmp),
		TEST(container_count),
		TEST(container_count_cmp),
		TEST(container_any),
		TEST(container_any_cmp),
		TEST(container_all),
		TEST(container_all_cmp),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/container", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}