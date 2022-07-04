#ifndef _NANO_CORE_H
#define _NANO_CORE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#if __linux__
#define memsize malloc_usable_size
#elif __APPLE__
#define memsize malloc_size
#elif _WIN32 || _WIN64
#define memsize _msize
#endif

#ifdef NDEBUG
#undef memsize
#endif

#ifdef memsize
#define check_buffer_overflow_acess(pointer, size) assert((size) < memsize((pointer)) && "Try to acess index out of bounds")     // cppcheck-suppress
#define check_buffer_overflow_size(pointer, size) assert((size) <= memsize((pointer)) && "Buffer have less size than requested") // cppcheck-suppress
#else
#define check_buffer_overflow_acess(pointer, size)
#define check_buffer_overflow_size(pointer, size)
#endif // memsize

#define __prefix nano_
#define __base_name core

#define _____concat2(A, B) A##B
#define _____concat(A, B) _____concat2(A, B)

#define __nano_fn(type, name, fn) _____concat(_____concat(_____concat(__prefix, _____concat(_____concat(name, _), type)), _), fn)
#define __nano_t(type, name) _____concat(_____concat(_____concat(name, _), type), _t)

#define __unique(name) _____concat(name, _____concat(_____concat(_____concat(_, _____concat(__prefix, __base_name)), __LINE__), __COUNTER__))

#define __count_arg_aux (a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a11, ...) a11

#ifdef _MSC_VER
#define count_arg(...) (__count_arg_aux(##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#else
#define count_arg(...) (__count_arg_aux(dummy, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#endif

#define macro_override(_0, _1, _2, _3, _4, macro_name, ...) macro_name

#define _GET_NTH_ARG(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, N, ...) N
#endif