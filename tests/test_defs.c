#include "test_defs.h"

cff_cmp_e data_compare(test_data a, test_data b);

#ifdef USE_VEC3

const uint64_t INI_LEN = 100;
const uint64_t DATA_SIZE = sizeof(test_data);

test_data data_new_at_index(uint64_t i) {
	return (test_data) {
		.x = i * 3,
		.y = i * 5,
		.z = i * 7,
	};

}

test_data data_new() {
	return (test_data) {
		.x = munit_rand_int_range(0, 10),
		.y = munit_rand_int_range(0, 10),
		.z = munit_rand_int_range(0, 10),
	};
}

void data_delete(test_data* ptr) {
	*ptr = (test_data){ 0 };
}

void data_print(test_data data) {
	printf("{%d, %d, %d }", data.x, data.y, data.z);
}

bool data_equals(test_data a, test_data b) {
	return memcmp(&a, &b, sizeof(test_data)) == 0;
}

cff_cmp_e data_compare(test_data a, test_data b) {
	if (a.x == b.x && a.y == b.y && a.z == b.z) return CFF_EQUALS;
	if (a.x < b.x) return CFF_LESS;
	if (a.x > b.x) return CFF_GREATER;
	return CFF_NOT_EQUAL;
}

bool filter(const void* const data, uint64_t index, uint64_t data_size) {
	vec3* vec = (vec3*)data;
	return vec->x % 2 == 0;
}

void map(const void* const data, void* out, uint64_t index) {
	vec3* vec = (vec3*)data;
	int* o = (int*)out;
	*o = vec->x + vec->y + vec->z;
}

void foreach(void* data, uint64_t index) {
	vec3* vec = (vec3*)data;
	vec->x *= 7;
}

bool validate_filter(test_data data, uint64_t index) {
	return data.x % 2 == 0;
}

bool validate_map(test_data data_from, int data_to, uint64_t index) {
	return (data_from.x + data_from.y + data_from.z) == data_to;
}

bool validate_foreach(test_data data, uint64_t index) {
	return data.x % 7 == 0;
}


cff_cmp_e compare(const void* const a, const void* const b, uint64_t data_size) {
	test_data aa = *(test_data*)a;
	test_data bb = *(test_data*)b;
	return data_compare(aa,bb);
}

cff_cmp_e compare_reverse(const void* const a, const void* const b, uint64_t data_size) {
	test_data aa = *(test_data*)a;
	test_data bb = *(test_data*)b;
	return data_compare(bb, aa);
}
#endif // USE_VEC3
