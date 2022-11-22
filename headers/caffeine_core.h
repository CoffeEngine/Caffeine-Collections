#ifndef CAFFEINE_CORE_H
#define CAFFEINE_CORE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "caffeine_memory.h"
#include "caffeine_types.h"




struct caffeine_containter_s {
    uintptr_t buffer;
    uint64_t data_size;
};

#define derive_container(name,fields) struct name { struct { uintptr_t buffer; uint64_t data_size;};  fields }

#define resolve_ptr(ptr) ((uintptr_t)(ptr))

#endif // !CAFFEINE_CORE_H
