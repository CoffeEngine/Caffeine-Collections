#include "caffeine_core.h"

void mcpy(uintptr_t from, uintptr_t to, uint64_t size) {
	char* restrict f = (char* restrict)from, * restrict t = (char* restrict)to;
	for (uint64_t i = 0; i < size; i++)
	{
		t[i] = f[i];
	}
}

void mcmp(uintptr_t a, uintptr_t b, uint64_t size) {
	char* restrict _a = (char* restrict)a, * restrict _b = (char * restrict)b;

	for (uint64_t i = 0; i < size; i++)
	{
		if (_a[i] != _b[i]) return 0;
	}
	return 1;
}

void mmove(uintptr_t from, uintptr_t to, uint64_t size) {
	char* restrict f = (char * restrict)from, * restrict t = (char * restrict)to;
	if (to > from) {
		for (uint64_t i = size-1; i >= 0; i--)
		{
			t[i] = f[i];
		}
		return;
	}
	for (uint64_t i = 0; i < size; i++)
	{
		t[i] = f[i];
	}
}