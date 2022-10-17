#include "caffeine_hashmap.h"
#include "caffeine_default_allocator.h"
#include "caffeine_memory.h"
#include "caffeine_assertions.h"

#define DEFAULT_INIT_LENGHT 7
#define PRIME_LENGHT ( ( sizeof(_prime_numbers) / sizeof(uint16_t) ) -1)

const uint16_t _prime_numbers[] = {
		2,		3,		5,		7,		11,		13,		17,		19,		23,
29,		31,		37,		41,		43,		47,		53,		59,		61,		67,
71,		73,		79,		83,		89,		97,		101,	103,	107,	109,
113,	127,	131,	137,	139,	149,	151,	157,	163,	167,
173,	179,	181,	191,	193,	197,	199,	211,	223,	227,
229,	233,	239,	241,	251,	257,	263,	269,	271,	277,
281,	283,	293,	307,	311,	313,	317,	331,	337,	347,
349,	353,	359,	367,	373,	379,	383,	389,	397,	401,
409,	419,	421,	431,	433,	439,	443,	449,	457,	461,
463,	467,	479,	487,	491,	499,	503,	509,	521,	523,
541,	547,	557,	563,	569,	571,	577,	587,	593,	599,
601,	607,	613,	617,	619,	631,	641,	643,	647,	653,
659,	661,	673,	677,	683,	691,	701,	709,	719,	727,
733,	739,	743,	751,	757,	761,	769,	773,	787,	797,
809,	811,	821,	823,	827,	829,	839,	853,	857,	859,
863,	877,	881,	883,	887,	907,	911,	919,	929,	937,
941,	947,	953,	967,	971,	977,	983,	991,	997,	983,
991,	997,	1009,	1013,	1019,	1021,	1031,	1033,	1039,	1049,
1051,	1061,	1063,	1069,	1087,	1091,	1093,	1097,	1103,	1109,
1117,	1123,	1129,	1151,	1153,	1163,	1171,	1181,	1187,	1193,
1201,	1213,	1217,	1223,	1229,	1231,	1237,	1249,	1259,	1277,
1279,	1283,	1289,	1291,	1297,	1301,	1303,	1307,	1319,	1321,
1327,	1361,	1367,	1373,	1381,	1399,	1409,	1423,	1427,	1429,
1433,	1439,	1447,	1451,	1453,	1459,	1471,	1481,	1483,	1487,
1489,	1493,	1499,	1511,	1523,	1531,	1543,	1549,	1553,	1559,
1567,	1571,	1579,	1583,	1597,	1601,	1607,	1609 };
const uint16_t _prime_len = PRIME_LENGHT;
const uint16_t _first_quartil = PRIME_LENGHT / 4;
const uint16_t _second_quartil = (PRIME_LENGHT / 4) * 2;
const uint16_t _third_quartil = (PRIME_LENGHT / 4) * 3;


uint16_t binarySearch(const uint16_t arr[], uint16_t l, uint16_t r, uint64_t x)
{
	uint16_t m = l + (r - l) / 2;
	while (l <= r) {
		m = l + (r - l) / 2;

		// Check if x is present at mid
		if (arr[m] == x || (arr[m - 1] < x && arr[m + 1] > x))
			return m;

		// If x greater, ignore left half
		if (arr[m] < x)
			l = m + 1;

		// If x is smaller, ignore right half
		else
			r = m - 1;
	}

	// if we reach here, then element was
	// not present
	return m;
}

int32_t caffeine_binary_search(const uint16_t arr[], uint16_t value, uint16_t start, uint16_t end) {
	if (value < _prime_numbers[_first_quartil]) end = _first_quartil;
	else if (value < _prime_numbers[_second_quartil]) { start = _first_quartil; end = _second_quartil; }
	else if (value < _prime_numbers[_third_quartil]) { start = _second_quartil; end = _third_quartil; }
	else { start = _third_quartil; }

	uint16_t index = (end - start) / 2;

	while (end != start) {

		index = (end - start) / 2;

		if (arr[index] == value) return index;

		if (value < arr[index]) {
			end = index - 1;
		}
		else if (value > arr[index]) {
			start = index + 1;
		}

	};

	return -1;
}

uint8_t caffeine_is_prime(uint64_t value) {
	if (value < _prime_numbers[_prime_len]) {
		return caffeine_binary_search(_prime_numbers, (uint16_t)value, 0, _prime_len) > 0;
	}
	for (uint64_t i = 2; i < (value / 2) + 1; i++) {
		if (value % i == 0) return 0;
	}
	return 1;
}

uint64_t caffeine_find_prime_below(uint64_t value) {

	if (value == _prime_numbers[_prime_len]) return _prime_numbers[_prime_len - 1];

	if (value < _prime_numbers[_prime_len]) {
		uint16_t start = 0, end = _prime_len - 1;
		if (value < _prime_numbers[_first_quartil]) end = _first_quartil;
		else if (value < _prime_numbers[_second_quartil]) { start = _first_quartil; end = _second_quartil; }
		else if (value < _prime_numbers[_third_quartil]) { start = _second_quartil; end = _third_quartil; }
		else { start = _third_quartil; }

		uint16_t mid = binarySearch(_prime_numbers, start, end, value);

		while (_prime_numbers[mid] >= value) mid--;
		while (_prime_numbers[mid] < value && _prime_numbers[mid + 1] < value) mid++;
		uint64_t prime = _prime_numbers[mid];
		return prime;
	}


	uint64_t last_prime = _prime_numbers[_prime_len];
	for (uint64_t i = value - 1; i > last_prime; i--)
	{
		if (caffeine_is_prime(i)) {
			return i;
		}
	}
	return last_prime;
}


//---------------- helper -----------------
uintptr_t caffeine_hashmap_get_bucket(cff_hashmap* hashmap, uint64_t index) {
	uintptr_t bucket_ptr = resolve_ptr(hashmap->buffer + index * (hashmap->key_size + hashmap->data_size));
	return bucket_ptr;
}

void caffeint_hashmap_copy_key(cff_hashmap* hashmap, uintptr_t bucket, uintptr_t out) {
	hashmap->cpy_func(bucket, out, hashmap->key_size);
}

void caffeint_hashmap_copy_value(cff_hashmap* hashmap, uintptr_t bucket, uintptr_t out) {
	cff_memcpy((const void* const)(bucket + (size_t)hashmap->key_size), (void* const)out, (size_t)hashmap->data_size, (size_t)hashmap->data_size);
}

void caffeine_hashmap_copy_bucket(cff_hashmap* hashmap, uintptr_t bucket, uintptr_t out) {
	caffeint_hashmap_copy_key(hashmap, bucket, out);
	caffeint_hashmap_copy_value(hashmap, bucket, out + hashmap->key_size);
}

void caffeine_hashmap_set_bucket(cff_hashmap* hashmap, uintptr_t bucket, uintptr_t key, uintptr_t value) {
	hashmap->cpy_func(key, bucket, hashmap->key_size);
	cff_memcpy((const void* const)value, (void* const)(bucket + hashmap->key_size), (size_t)hashmap->data_size, (size_t)hashmap->data_size);
}

//-----------------------------------------

cff_err_e caffeine_hashmap_expand(cff_hashmap* hashmap, AllocatorInterface* allocator) {
	cff_assert_param_not_null(hashmap);

	if (allocator == NULL) allocator = cff_default_allocator_get();
	cff_assert_param_not_null(allocator);

	uint64_t new_lenght = hashmap->lenght * 2;

	uint64_t bitmap_len = new_lenght / ((uint64_t)(sizeof(uint64_t)) * (uint64_t)8);

	if (bitmap_len == 0) bitmap_len = 1;


	uint64_t* new_bitmap_buffer = cff_allocator_alloc(allocator, (size_t)(sizeof(uint64_t) * bitmap_len), 8);
	if (new_bitmap_buffer == NULL) return CFF_ALLOC_ERR;

	void* new_hashmap_buffer = cff_allocator_alloc(allocator, (size_t)(new_lenght * ((uint64_t)hashmap->data_size + (uint64_t)hashmap->key_size)), 8);
	if (new_hashmap_buffer == NULL) return CFF_ALLOC_ERR;

	cff_memset(new_bitmap_buffer, 0, (size_t)(sizeof(uint64_t) * bitmap_len));


	uintptr_t old_hashmap = hashmap->buffer;
	uint64_t old_len = hashmap->lenght;

	cff_bitmap old_bitmap = hashmap->bitmap;

	hashmap->bitmap.buffer = new_bitmap_buffer;
	hashmap->bitmap.lenght = new_lenght;

	hashmap->buffer = resolve_ptr(new_hashmap_buffer);
	hashmap->lenght = new_lenght;
	hashmap->count = 0;
	hashmap->prime_value = caffeine_find_prime_below(new_lenght);
	hashmap->collision_count_max = 0;

	for (uint64_t i = 0; i < old_len; i++)
	{
		if (caffeine_bitmap_get(&old_bitmap, i)) {

			uintptr_t key = resolve_ptr(old_hashmap + i * (hashmap->data_size + hashmap->key_size));
			uintptr_t value = resolve_ptr(key + hashmap->key_size);
			
			cff_err_e err = caffeine_hashmap_add(hashmap, key, value, allocator);
			
			if (err != CFF_NONE_ERR) return err;
		}
	}
	cff_allocator_free(allocator, (void*)old_hashmap, 8);
	caffeine_bitmap_free(&old_bitmap, allocator);

	return CFF_NONE_ERR;
}

uint64_t caffeine_hashmap_hash_default(uintptr_t data_ptr, uint32_t data_size) {
	cff_assert_param_not_null(data_ptr);
	cff_assert_param_not_zero(data_size);
	char* key = (char*)data_ptr;
	uint64_t h = (525201411107845655ull);

	for (; data_size; --data_size, ++key) {
		h ^= *key;
		h *= 0x5bd1e9955bd1e995;
		h ^= h >> 47;
	}
	return h;
}

int8_t caffeine_hashmap_cmp_default(uintptr_t key_a, uintptr_t key_b, uint32_t data_size) {
	cff_assert_param_not_null(key_a);
	cff_assert_param_not_null(key_b);
	cff_assert_param_not_zero(data_size);

	return cff_memcmp((const void*)key_a, (const void*)key_b, (size_t)data_size);
}

void caffeine_hashmap_cpy_default(uintptr_t from, uintptr_t to, uint32_t data_size) {
	cff_memcpy((const void* const)from, (void* const)to, (size_t)data_size, (size_t)data_size);
}

inline uint64_t caffeine_second_hash(cff_hashmap* hashmap, uint64_t key, uint64_t collision_count) {
	cff_assert_param_not_null(hashmap);

	return ((key + collision_count) * (hashmap->prime_value - (key % hashmap->prime_value))) % hashmap->lenght;
}



cff_err_e caffeine_hashmap_create(cff_hashmap* hashmap, uint32_t key_size, uint32_t data_size, uint64_t lenght, cff_hash_key_func hash_func, cff_cmp_key_func cmp_func, cff_cpy_key_func cpy_func, AllocatorInterface* allocator) {
	cff_assert_param_not_null(hashmap);
	cff_assert_param_not_null(hash_func);
	cff_assert_param_not_null(cmp_func);
	cff_assert_param_not_null(cpy_func);

	cff_assert_param_not_zero(key_size);
	cff_assert_param_not_zero(data_size);
	cff_assert_param_not_zero(lenght);

	if (allocator == NULL) allocator = cff_default_allocator_get();
	cff_assert_param_not_null(allocator);

	hashmap->buffer = (uintptr_t)cff_allocator_alloc(allocator, (size_t)(((uint64_t)data_size + (uint64_t)key_size) * lenght), 8);

	if (hashmap->buffer == 0) return CFF_ALLOC_ERR;

	hashmap->data_size = data_size;
	hashmap->key_size = key_size;
	hashmap->lenght = lenght;
	hashmap->count = 0;
	hashmap->cmp_func = (cmp_func != NULL) ? cmp_func : caffeine_hashmap_cmp_default;
	hashmap->hash_func = (hash_func != NULL) ? hash_func : caffeine_hashmap_hash_default;
	hashmap->cpy_func = (cpy_func != NULL) ? cpy_func : caffeine_hashmap_cpy_default;
	hashmap->prime_value = caffeine_find_prime_below(lenght);
	hashmap->collision_count_max = 0;


	cff_err_e err = caffeine_bitmap_create(&hashmap->bitmap, lenght, allocator);

	if (err != CFF_NONE_ERR) {
		caffeine_hashmap_free(hashmap, allocator);
		return err;
	}

	return CFF_NONE_ERR;
}

cff_err_e caffeine_hashmap_create_default(cff_hashmap* hashmap, uint32_t key_size, uint32_t data_size, AllocatorInterface* allocator) {
	cff_assert_param_not_null(hashmap);

	cff_assert_param_not_zero(key_size);
	cff_assert_param_not_zero(data_size);

	if (allocator == NULL) allocator = cff_default_allocator_get();
	cff_assert_param_not_null(allocator);

	hashmap->buffer = (uintptr_t)cff_allocator_alloc(allocator, (size_t)((data_size + key_size) * DEFAULT_INIT_LENGHT), 8);

	if (hashmap->buffer == 0) return CFF_ALLOC_ERR;

	hashmap->data_size = data_size;
	hashmap->key_size = key_size;
	hashmap->lenght = DEFAULT_INIT_LENGHT;
	hashmap->count = 0;
	hashmap->cmp_func = caffeine_hashmap_cmp_default;
	hashmap->hash_func = caffeine_hashmap_hash_default;
	hashmap->cpy_func = caffeine_hashmap_cpy_default;
	hashmap->prime_value = caffeine_find_prime_below(DEFAULT_INIT_LENGHT);
	hashmap->collision_count_max = 0;


	cff_err_e err = caffeine_bitmap_create(&hashmap->bitmap, DEFAULT_INIT_LENGHT, allocator);

	if (err != CFF_NONE_ERR) {
		caffeine_hashmap_free(hashmap, allocator);
		return err;
	}

	return CFF_NONE_ERR;
}

cff_err_e caffeine_hashmap_add(cff_hashmap* hashmap, uintptr_t key, uintptr_t value, AllocatorInterface* allocator) {
	cff_assert_param_not_null(hashmap);
	cff_assert_param_not_null(key);
	cff_assert_param_not_null(value);

	if ((((float)hashmap->count) / ((float)hashmap->lenght)) >= 0.75f) {
		cff_err_e err = caffeine_hashmap_expand(hashmap, allocator);
		if (err != CFF_NONE_ERR) return err;
	}

	uint64_t index = hashmap->hash_func(key, hashmap->data_size) % hashmap->lenght;
	uint64_t collision_count = 0;

	while (caffeine_bitmap_get(&hashmap->bitmap, index) != 0) {
		uintptr_t bucket_ptr = caffeine_hashmap_get_bucket(hashmap, index);

		// overwrite 
		if (hashmap->cmp_func(key, bucket_ptr, hashmap->key_size)) {
			caffeine_hashmap_set_bucket(hashmap, bucket_ptr, key, value);
			return 1;
		}

		// calculate new hash;
		collision_count++;
		if (collision_count > hashmap->lenght * 0.75f) {
			
			cff_err_e err = caffeine_hashmap_expand(hashmap, allocator);
			if (err != CFF_NONE_ERR) return err;

			index = hashmap->hash_func(key, hashmap->data_size) % hashmap->lenght;
			collision_count = 0;
		}
		else
			index = caffeine_second_hash(hashmap, index, collision_count);
	}


	if (collision_count > hashmap->collision_count_max) hashmap->collision_count_max = collision_count;

	caffeine_bitmap_set(&hashmap->bitmap, index);
	uintptr_t bucket_ptr = caffeine_hashmap_get_bucket(hashmap, index);
	caffeine_hashmap_set_bucket(hashmap, bucket_ptr, key, value);
	hashmap->count++;
	
	return CFF_NONE_ERR;
}

uint8_t caffeine_hashmap_get(cff_hashmap* hashmap, uintptr_t key, uintptr_t value) {
	cff_assert_param_not_null(hashmap);
	cff_assert_param_not_null(key);
	cff_assert_param_not_null(value);

	uint64_t index = hashmap->hash_func(key, hashmap->data_size) % hashmap->lenght;
	uint64_t collision_count = 0;


	while (caffeine_bitmap_get(&hashmap->bitmap, index) != 0) {
		uintptr_t bucket_ptr = caffeine_hashmap_get_bucket(hashmap, index);

		if (hashmap->cmp_func(key, bucket_ptr, hashmap->key_size)) {
			caffeint_hashmap_copy_value(hashmap, bucket_ptr, value);
			return 1;
		}

		if (++collision_count > hashmap->collision_count_max) return 0;

		index = caffeine_second_hash(hashmap, index, collision_count);
	}

	return 0;
}

uint8_t caffeine_hashmap_exist_key(cff_hashmap* hashmap, uintptr_t key) {
	cff_assert_param_not_null(hashmap);
	cff_assert_param_not_null(key);

	uint64_t index = hashmap->hash_func(key, hashmap->data_size) % hashmap->lenght;
	uint64_t collision_count = 0;
	uintptr_t bucket_ptr = 0;

	while (caffeine_bitmap_get(&hashmap->bitmap, index) != 0) {
		bucket_ptr = caffeine_hashmap_get_bucket(hashmap, index);

		if (hashmap->cmp_func(key, bucket_ptr, hashmap->key_size)) return 1;

		if (++collision_count > hashmap->collision_count_max) return 0;

		index = caffeine_second_hash(hashmap, index, collision_count);
	}

	bucket_ptr = caffeine_hashmap_get_bucket(hashmap, index);

	if (hashmap->cmp_func(key, bucket_ptr, hashmap->key_size)) return 1;
	return 0;
}

uint8_t caffeine_hashmap_remove(cff_hashmap* hashmap, uintptr_t key) {
	cff_assert_param_not_null(hashmap);
	cff_assert_param_not_null(key);
	;

	uint64_t index = hashmap->hash_func(key, hashmap->data_size) % hashmap->lenght;
	uint64_t collision_count = 0;


	while (caffeine_bitmap_get(&hashmap->bitmap, index) != 0) {
		uintptr_t bucket_ptr = caffeine_hashmap_get_bucket(hashmap, index);

		if (hashmap->cmp_func(key, bucket_ptr, hashmap->key_size)) {
			caffeine_bitmap_clear(&hashmap->bitmap, index);
			return 1;
		}

		if (++collision_count > hashmap->collision_count_max) return 0;

		index = caffeine_second_hash(hashmap, index, collision_count);
	}

	return 0;
}

void caffeine_hashmap_free(cff_hashmap* hashmap, AllocatorInterface* allocator) {
	cff_assert_param_not_null(hashmap);

	if (allocator == NULL) allocator = cff_default_allocator_get();
	cff_assert_param_not_null(allocator);

	caffeine_bitmap_free(&(hashmap->bitmap), allocator);

	cff_allocator_free(allocator, (void*)hashmap->buffer, 8);

	cff_memset((void*)hashmap, 0, sizeof(hashmap));
}

void caffeine_hashmap_clear(cff_hashmap* hashmap) {
	cff_assert_param_not_null(hashmap);

	caffeine_bitmap_clear_all(&hashmap->bitmap);
	hashmap->count = 0;
	hashmap->collision_count_max = 0;
}