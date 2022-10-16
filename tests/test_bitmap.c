#include <stdio.h>
#include <math.h>
#include "caffeine_bitmap.h"
#include "caffeine_memory.h"

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

#define BIT_LEN 5

#define TEST(FUNC) { "/"#FUNC, test_##FUNC, test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL }

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], cff_bitmap* bitmap)



TESTDEF(bitmap_create) {
	caffeine_bitmap_create(bitmap, BIT_LEN, NULL);
	
	munit_assert(bitmap->buffer != 0);
	munit_assert_int64(bitmap->lenght, == , BIT_LEN);
	return MUNIT_OK;
}

TESTDEF(bitmap_set) {
	int bit = munit_rand_int_range(0, BIT_LEN - 1);
	uint64_t bit_value = (uint64_t)pow(2, bit);

	caffeine_bitmap_set(bitmap, bit);

	uint64_t buffer_value = bitmap->buffer[0];

	munit_assert(bit_value == buffer_value);
	return MUNIT_OK;
}

TESTDEF(bitmap_clear) {

	memset(bitmap->buffer, UINT64_MAX, sizeof(uint64_t));

	int bit = munit_rand_int_range(0, BIT_LEN - 1);
	uint64_t bit_value = UINT64_MAX ^ ((uint64_t)pow(2, bit));

	caffeine_bitmap_clear(bitmap, bit);

	uint64_t buffer_value = bitmap->buffer[0];

	munit_assert(bit_value == buffer_value);
	return MUNIT_OK;

}

TESTDEF(bitmap_set_all) {

	caffeine_bitmap_set_all(bitmap);
	uint64_t buffer_value = bitmap->buffer[0];

	munit_assert(buffer_value == UINT64_MAX);
	return MUNIT_OK;
}

TESTDEF(bitmap_clear_all) {

	memset(bitmap->buffer, UINT64_MAX, sizeof(uint64_t));
	caffeine_bitmap_clear_all(bitmap);

	uint64_t buffer_value = bitmap->buffer[0];

	munit_assert(buffer_value == 0);
	return MUNIT_OK;
}

TESTDEF(bitmap_get) {

	int bit = munit_rand_int_range(0, BIT_LEN - 1);

	caffeine_bitmap_set(bitmap, bit);

	uint8_t value = caffeine_bitmap_get(bitmap, bit);

	munit_assert(value == 1);

	caffeine_bitmap_clear(bitmap, bit);

	value = caffeine_bitmap_get(bitmap, bit);

	munit_assert(value == 0);
	return MUNIT_OK;
}

TESTDEF(bitmap_resize) {

	caffeine_bitmap_resize(bitmap, 15, NULL);
	int bit = munit_rand_int_range(8, 14);


	caffeine_bitmap_set(bitmap, bit);

	uint8_t value = caffeine_bitmap_get(bitmap, bit);

	munit_assert(value == 1);

	caffeine_bitmap_clear(bitmap, bit);

	value = caffeine_bitmap_get(bitmap, bit);

	munit_assert(value == 0);
	return MUNIT_OK;
}

TESTDEF(bitmap_free) {
	caffeine_bitmap_free(bitmap, NULL);

	munit_assert(bitmap->buffer == NULL);

	return MUNIT_OK;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_bitmap* bitmap = malloc(sizeof(cff_bitmap));
	caffeine_bitmap_create(bitmap, BIT_LEN, NULL);
	return bitmap;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_bitmap* bitmap = malloc(sizeof(cff_bitmap));
	return bitmap;
}

static void test_tear_down(void* fixture) {
	caffeine_bitmap_free(fixture, NULL);
	free(fixture);
}

static void test_tear_down_free(void* fixture) {
	free(fixture);
}

int test_bitmap(int argc, char* const argv[]) {

	MunitTest tests[] = {
		{ "/bitmap_create", test_bitmap_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(bitmap_set),
		TEST(bitmap_clear),
		TEST(bitmap_set_all),
		TEST(bitmap_clear_all),
		TEST(bitmap_get),
		TEST(bitmap_resize),
		{ "/bitmap_free", test_bitmap_free, test_setup, test_tear_down_free, MUNIT_TEST_OPTION_NONE, NULL },

		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/bitmap", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}