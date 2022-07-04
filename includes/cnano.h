#ifndef __NANO_H__
#define __NANO_H__

#ifndef NANO_NO_STD

#include <stdlib.h>
#include <memory.h>

#define nano_malloc malloc

#define nano_free free

#define nano_realloc realloc

#define nano_memmove memmove

#define nano_memcpy memcpy

#define nano_memcmp memcmp

#else

#ifndef nano_malloc
#error when NANO_NO_STD is defined nano_malloc need to be manually defined. ex: #define nano_malloc my_malloc_func
#endif

#ifndef nano_free
#error when NANO_NO_STD is defined nano_free need to be manually defined. ex: #define nano_free my_free_func
#endif

#ifndef nano_realloc
#error when NANO_NO_STD is defined nano_realloc need to be manually defined. ex: #define nano_realloc my_realloc_func
#endif

#ifndef nano_memmove
#error when NANO_NO_STD is defined nano_memmove need to be manually defined. ex: #define nano_memmove my_memmmove_func
#endif

#ifndef nano_memcpy
#error when NANO_NO_STD is defined nano_memcpy need to be manually defined. ex: #define nano_memcpy my_memcpy_func
#endif

#ifndef nano_memcmp
#error when NANO_NO_STD is defined nano_memcmp need to be manually defined. ex: #define nano_memmove my_memmmove_func
#endif

#endif

#include "../src/internal/nano_foreach_macro.h"

#include "../src/definitions/nano_array.h"
#include "../src/definitions/nano_vector.h"
#include "../src/definitions/nano_hash.h"
#include "../src/definitions/nano_linked_list.h"
#include "../src/definitions/nano_stack.h"
#include "../src/definitions/nano_queue.h"
		 
#include "../src/implementation/nano_core.h"
#include "../src/implementation/nano_array.h"
#include "../src/implementation/nano_vector.h"
#include "../src/implementation/nano_hash.h"
#include "../src/implementation/nano_linked_list.h"
#include "../src/implementation/nano_stack.h"
#include "../src/implementation/nano_queue.h"

#endif