#include "caffeine_hashmap.h"
#include "test_defs.h"


#define KEY_SIZE ((uint32_t)(sizeof(char)*32))
#define VALUE_SIZE ((uint32_t)sizeof(int64_t))
#define INI_LEN 4
#define KEYS_LEN (INI_LEN * 4)


char* get_random_string() {
	const size_t strl = 32;
	char* buffer = malloc(strl);

	if (buffer == NULL) return NULL;

	buffer[strl - 1] = '\0';
	for (size_t i = 0; i < strl - 1; i++)
	{
		buffer[i] = (char)munit_rand_int_range('A', 'Z');
	}

	return buffer;
}

char** get_random_keys() {
	char** keys = (char**)malloc(sizeof(char*) * KEYS_LEN);

	if (keys == NULL) return NULL;

	for (size_t i = 0; i < KEYS_LEN; i++)
	{
		char* str = get_random_string();

		if (str == NULL) {
			for (size_t j = 0; j < i; j++)free(keys[j]);
			free(keys);
			return NULL;
		}

		keys[i] = str;
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

	char* key = (char*)data_ptr;
	uint64_t h = (525201411107845655ull);

	for (; *key; ++key) {
		h ^= *key;
		h *= 0x5bd1e9955bd1e995;
		h ^= h >> 47;
	}
	return h;
}

int8_t cmp_string(uintptr_t key_a, uintptr_t key_b, uint32_t data_size) {
	char* a = (char*)key_a;
	char* b = (char*)key_b;
	return (int8_t)strcmp(a, b) == 0;
}

void cpy_string(uintptr_t from, uintptr_t to, uint32_t data_size) {
#ifdef CFF_COMP_MSVC
	strncpy_s((char*)to, (rsize_t)data_size, (const char*)from, (rsize_t)data_size);
#else
	strncpy((char*)to, (const char*)from, data_size);
#endif

}

TESTDEF(hashmap_create) {
	cff_hashmap* hashmap = (cff_hashmap*)munit_data;

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
	cff_hashmap* hashmap = (cff_hashmap*)munit_data;
	
	char** keys = get_random_keys();
	int64_t start = munit_rand_uint32();

	for (int i = 0; i < KEYS_LEN; i++)
	{
		int64_t v = start + i;
		SKIP_ON_ERR(cff_hashmap_add(hashmap, (uintptr_t)keys[i], (uintptr_t)(&v), NULL));
		munit_assert(hashmap->count == i + (uint64_t)1);
	}
	munit_assert(hashmap->lenght > INI_LEN);

	free_keys(keys);

	return MUNIT_OK;
}

TESTDEF(hashmap_get) {
	cff_hashmap* hashmap = (cff_hashmap*)munit_data;
	
	char** keys = get_random_keys();
	int64_t start = munit_rand_uint32();

	for (int i = 0; i < KEYS_LEN; i++)
	{
		int64_t v = start + i;
		SKIP_ON_ERR(cff_hashmap_add(hashmap, (uintptr_t)keys[i], (uintptr_t)(&v), NULL));
		munit_assert(hashmap->count ==i + (uint64_t)1);
	}
	munit_assert(hashmap->lenght > INI_LEN);

	for (int i = 0; i < KEYS_LEN; i++) {
		int64_t value = 0;
		uint8_t res = cff_hashmap_get(hashmap, (uintptr_t)keys[i], (uintptr_t)&value);
		munit_assert(value == (int64_t)(start + i));
		munit_assert(res);
	}

	free_keys(keys);

	return MUNIT_OK;
}

TESTDEF(hashmap_remove) {
	cff_hashmap* hashmap = (cff_hashmap*)munit_data;
	
	char** keys = get_random_keys();
	int64_t v = munit_rand_uint32();
	int64_t value = 0;
	int64_t index = munit_rand_int_range(1, KEYS_LEN - 1);

	SKIP_ON_ERR(cff_hashmap_add(hashmap, (uintptr_t)keys[index], (uintptr_t)&v, NULL));

	uint8_t res = cff_hashmap_remove(hashmap, (uintptr_t)keys[index]);
	munit_assert(res);
	res = cff_hashmap_get(hashmap, (uintptr_t)keys[index], (uintptr_t)&value);
	munit_assert(res == 0);

	free_keys(keys);
	return MUNIT_OK;
}

TESTDEF(hashmap_exist_key) {
	cff_hashmap* hashmap = (cff_hashmap*)munit_data;
	
	char** keys = get_random_keys();
	int64_t v = munit_rand_uint32();
	int64_t index = munit_rand_int_range(1, KEYS_LEN - 1);

	SKIP_ON_ERR(cff_hashmap_add(hashmap, (uintptr_t)keys[index], (uintptr_t)&v, NULL));
	uint8_t res = cff_hashmap_exist_key(hashmap, (uintptr_t)keys[index]);
	munit_assert(res);
	res = cff_hashmap_remove(hashmap, (uintptr_t)keys[index]);
	munit_assert(res);

	free_keys(keys);
	return MUNIT_OK;
}

TESTDEF(hashmap_clear) {
	cff_hashmap* hashmap = (cff_hashmap*)munit_data;
	
	char** keys = get_random_keys();
	int64_t start = munit_rand_uint32();

	for (int i = 0; i < KEYS_LEN; i++)
	{
		int64_t v = start + i;
		SKIP_ON_ERR(cff_hashmap_add(hashmap, (uintptr_t)keys[i], (uintptr_t)&v, NULL));
		munit_assert(hashmap->count == i + (uint64_t)1);
	}
	munit_assert(hashmap->lenght > INI_LEN);
	cff_hashmap_clear(hashmap);
	for (size_t i = 0; i < KEYS_LEN; i++) {
		int64_t value = 0;
		uint8_t res = cff_hashmap_get(hashmap, (uintptr_t)keys[i], (uintptr_t)&value);
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
	if(hashmap!= NULL) *hashmap = (cff_hashmap){0};
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