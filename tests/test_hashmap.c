#include <stdio.h>
#include "caffeine_hashmap.h"
#include "caffeine_memory.h"

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

#define TEST(FUNC) { "/"#FUNC, test_##FUNC, test_setup, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL }

#define TESTDEF(FUNC) MunitResult test_##FUNC(const MunitParameter params[], cff_hashmap* hashmap)

#define SKIP_ON_ERR(EXP) {cff_err_e err = (EXP); if (err != CFF_NONE_ERR) { return MUNIT_ERROR; }}

#define KEY_SIZE ((uint32_t)(sizeof(char)*32))
#define VALUE_SIZE ((uint32_t)sizeof(int64_t))
#define INI_LEN 4
#define KEYS_LEN (INI_LEN * 4)


#pragma region DEBUG
void dbg_callback(char* str, uint64_t str_len) {
	printf("%s\n", str);
}

uint64_t parse_key(uintptr_t pointer, uint64_t data_size, char** buffer, AllocatorInterface* allocator) {
	const char* str = (const char*)pointer;
	size_t str_len = strnlen(str, 32);
	*buffer = cff_allocator_alloc(allocator, str_len);
	strncpy(*buffer, str, str_len);
	return str_len;
}

uint64_t parse_value(uintptr_t pointer, uint64_t data_size, char** buffer, AllocatorInterface* allocator) {
	int64_t value = *(int64_t*)pointer;
	size_t str_len = snprintf(NULL, 0, "%lld", value);
	*buffer = cff_allocator_alloc(allocator, str_len + 1);
	snprintf(*buffer, str_len, "%lld", value);
	*buffer[str_len] = '\0';
	return str_len;
}

#pragma endregion


char* get_random_string() {
	int strl = 32;
	char* buffer = malloc(strl);
	buffer[strl-1] = '\0';
	for (size_t i = 0; i < strl-1; i++)
	{
		buffer[i] = (char)munit_rand_int_range('A', 'Z');
	}

	return buffer;
}

char** get_random_keys() {
	char** keys = (char**)malloc(sizeof(char*) * KEYS_LEN);

	for (size_t i = 0; i < KEYS_LEN; i++)
	{
		keys[i] = get_random_string();
	}

	return keys;
}

void free_keys(char** keys) {
	for (size_t i = 0; i < KEYS_LEN; i++)
	{
		free(keys[i]);
	}
	free(keys);
}


uint64_t hash_string(uintptr_t data_ptr, uint32_t data_size) {

	char* key = data_ptr;
	uint64_t h = (525201411107845655ull);

	for (; *key; ++key) {
		h ^= *key;
		h *= 0x5bd1e9955bd1e995;
		h ^= h >> 47;
	}
	return h;
}

int8_t cmp_string(uintptr_t key_a, uintptr_t key_b, uint32_t data_size) {
	char* a = key_a;
	char* b = key_b;
	return (int8_t)strcmp(a,b) == 0;
}

void cpy_string(uintptr_t from, uintptr_t to, uint32_t data_size) {
	strncpy(to, from, data_size);
}

TESTDEF(hashmap_create) {
	cff_hashmap_create(hashmap, KEY_SIZE, VALUE_SIZE, INI_LEN, hash_string, cmp_string, cpy_string, NULL);

	munit_assert(hashmap->cmp_func == cmp_string);
	munit_assert(hashmap->hash_func == hash_string);
	munit_assert(hashmap->cpy_func == cpy_string);
	munit_assert(hashmap->buffer != 0);
	munit_assert(hashmap->prime_value != 0);
	munit_assert(hashmap->lenght != 0);
	munit_assert(hashmap->data_size == VALUE_SIZE);
	munit_assert(hashmap->key_size == KEY_SIZE);
	munit_assert(hashmap->count == 0);
	munit_assert(hashmap->collision_count_max == 0);

	return MUNIT_OK;
}

TESTDEF(hashmap_add) {
	char** keys = get_random_keys();
	int64_t start = munit_rand_uint32();
	
	for (size_t i = 0; i < KEYS_LEN; i++)
	{
		int64_t v = start + i;
	 	uint8_t res= cff_hashmap_add(hashmap, keys[i],&v, NULL);
		munit_assert(hashmap->count == i+1);
	}
	munit_assert(hashmap->lenght > INI_LEN);

	free_keys(keys);

	return MUNIT_OK;
}

TESTDEF(hashmap_get) {
	char** keys = get_random_keys();
	int64_t start = munit_rand_uint32();

	for (size_t i = 0; i < KEYS_LEN; i++)
	{
		int64_t v = start + i;
		uint8_t res = cff_hashmap_add(hashmap, keys[i], &v, NULL);
		munit_assert(hashmap->count == i + 1);
	}
	munit_assert(hashmap->lenght > INI_LEN);

	for (size_t i = 0; i < KEYS_LEN; i++) {
		int64_t value = 0;
		uint8_t res = cff_hashmap_get(hashmap, keys[i], (uintptr_t)&value);
		munit_assert(value == start + i);
		munit_assert(res);
	}

	free_keys(keys);

	return MUNIT_OK;
}

TESTDEF(hashmap_remove) {
	char** keys = get_random_keys();
	int64_t v = munit_rand_uint32();
	int64_t value = 0;
	int64_t index = munit_rand_int_range(1, KEYS_LEN-1);

	uint8_t res = cff_hashmap_add(hashmap, keys[index], &v, NULL);
	munit_assert(res);
	res = cff_hashmap_remove(hashmap, keys[index]);
	munit_assert(res);
	res = cff_hashmap_get(hashmap, keys[index], (uintptr_t)&value);
	munit_assert(res == 0);

	free_keys(keys);
	return MUNIT_OK;
}

TESTDEF(hashmap_exist_key) {
	char** keys = get_random_keys();
	int64_t v = munit_rand_uint32();
	int64_t index = munit_rand_int_range(1, KEYS_LEN-1);

	uint8_t res = cff_hashmap_add(hashmap, keys[index], &v, NULL);
	munit_assert(res);
	res = cff_hashmap_exist_key(hashmap, keys[index]);
	munit_assert(res);
	res = cff_hashmap_remove(hashmap, keys[index]);
	munit_assert(res);

	free_keys(keys);
	return MUNIT_OK;
}

TESTDEF(hashmap_clear) {
	char** keys = get_random_keys();
	int64_t start = munit_rand_uint32();

	for (size_t i = 0; i < KEYS_LEN; i++)
	{
		int64_t v = start + i;
		uint8_t res = cff_hashmap_add(hashmap, keys[i], &v, NULL);
		munit_assert(hashmap->count == i + 1);
	}
	munit_assert(hashmap->lenght > INI_LEN);
	cff_hashmap_clear(hashmap);
	for (size_t i = 0; i < KEYS_LEN; i++) {
		int64_t value = 0;
		uint8_t res = cff_hashmap_get(hashmap, keys[i], (uintptr_t)&value);
		munit_assert(value == 0);
		munit_assert(res == 0);
	}

	free_keys(keys);
	return MUNIT_OK;
}

static void* test_setup(const MunitParameter params[], void* user_data) {
	cff_hashmap* hashmap = malloc(sizeof(cff_hashmap));
	cff_hashmap_create(hashmap, KEY_SIZE, VALUE_SIZE, INI_LEN, hash_string, cmp_string, cpy_string, NULL);
	return hashmap;
}

static void* test_setup_create(const MunitParameter params[], void* user_data) {
	cff_hashmap* hashmap = malloc(sizeof(cff_hashmap));
	return hashmap;
}

static void test_tear_down(void* fixture) {
	cff_hashmap_free(fixture, NULL);
	free(fixture);
}

int test_hashmap(int argc, char* const argv[]) {
	MunitTest tests[] = {
		{ "/hashmap_create",  test_hashmap_create, test_setup_create, test_tear_down, MUNIT_TEST_OPTION_NONE, NULL },
		TEST(hashmap_add),
		TEST(hashmap_get),
		TEST(hashmap_remove),
		TEST(hashmap_exist_key),
		TEST(hashmap_clear),
		{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
	};

	MunitSuite suite = { "/hashmap", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE };

	return munit_suite_main((const MunitSuite*)(&suite), NULL, argc, argv);
}