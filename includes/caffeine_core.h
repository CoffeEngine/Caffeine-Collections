#ifndef CAFFEINE_CORE_H
#define CAFFEINE_CORE_H

#include <stdint.h>

#define cast(type,value)(*(type*)&value)

#ifndef cff_malloc
#define cff_malloc malloc
#endif // !cff_malloc

#ifndef cff_free
#define cff_free free
#endif // !cff_free

#ifndef cff_realloc
#define cff_realloc realloc
#endif // !cff_realloc

#ifndef cff_memmove
#define cff_memmove memmove
#endif // !cff_memmove

#ifndef cff_malloca
#if _WIN32 || _WIN64
//stack allocation
#define cff_malloca _malloca
#else 
#include <alloca.h>
//stack allocation
#define cff_malloca alloca
#endif
#endif

#ifndef cff_freea
#if _WIN32 || _WIN64
//stack free
#define cff_freea _freea
#else 
//stack free
#define cff_freea(ptr) 
#endif
#endif

void mcpy(uintptr_t from, uintptr_t to, uint64_t size);
void mmove(uintptr_t from, uintptr_t to, uint64_t size);
void mcmp(uintptr_t a, uintptr_t b, uint64_t size);

struct caffeine_containter_s {
	uintptr_t buffer;
	uint64_t data_size;
};

#define derive_container(name,fields) struct name { struct caffeine_containter_s;  fields }

#endif // !CAFFEINE_CORE_H
