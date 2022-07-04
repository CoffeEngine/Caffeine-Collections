#ifndef NANO_STACK_IMPL_H
#define NANO_STACK_IMPL_H

#include "nano_core.h"

#define nano_implement_stack_for(...) call_macro_x_for_each(nano_implement_stack, __VA_ARGS__)

#define nano_implement_stack(type)                                                                                                                               \
    void __nano_fn(type, stack, create)(__nano_t(type, stack) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                            \
        assert(arr != NULL);                                                                                                                                     \
        arr->lenght = lenght;                                                                                                                                    \
        arr->count = 0;                                                                                                                                          \
        __nano_fn(type, __base_name, create)(&(arr->buffer), lenght);                                                                                            \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, free)(__nano_t(type, stack) * arr)                                                                                               \
    {                                                                                                                                                            \
        assert(arr != NULL);                                                                                                                                     \
        assert(arr->buffer != NULL);                                                                                                                             \
        nano_free(arr->buffer);                                                                                                                                  \
        arr->lenght = 0;                                                                                                                                         \
        arr->buffer = 0;                                                                                                                                         \
        arr->count = 0;                                                                                                                                          \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, clear)(__nano_t(type, stack) * arr)                                                                                              \
    {                                                                                                                                                            \
        arr->count = 0;                                                                                                                                          \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, push)(__nano_t(type, stack) * arr, type value)                                                                                   \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, push_back)(arr->buffer, value, &arr->count);                                                                                \
    }                                                                                                                                                            \
    type __nano_fn(type, stack, pop)(__nano_t(type, stack) * arr)                                                                                                \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, get)(arr->buffer, --arr->count);                                                                                     \
    }                                                                                                                                                            \
    type __nano_fn(type, stack, top)(__nano_t(type, stack) * arr)                                                                                                \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, get)(arr->buffer, arr->count - 1);                                                                                   \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, copy)(__nano_t(type, stack) * arr, __nano_t(type, stack) * *out, size_t start, size_t end)                                       \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, copy)(arr->buffer, &((*out)->buffer), start, end);                                                                          \
        (*out)->count = (end - start) < arr->count ? (end - start) : arr->count;                                                                                 \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, clone)(__nano_t(type, stack) * arr, __nano_t(type, stack) * *out)                                                                \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, clone)(arr->buffer, &((*out)->buffer), arr->lenght);                                                                        \
        (*out)->count = arr->count;                                                                                                                              \
    }                                                                                                                                                            \
    bool __nano_fn(type, stack, equal)(__nano_t(type, stack) * a, __nano_t(type, stack) * b)                                                                     \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, equal)(a->buffer, b->buffer, a->count);                                                                              \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, fill)(__nano_t(type, stack) * arr, type value)                                                                                   \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, fill)(arr->buffer, value, arr->lenght);                                                                                     \
    }                                                                                                                                                            \
    int __nano_fn(type, stack, find)(__nano_t(type, stack) * arr, type value)                                                                                    \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, find)(arr->buffer, value, arr->count);                                                                               \
    }                                                                                                                                                            \
    int __nano_fn(type, stack, find_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, find_cmp)(arr->buffer, value, arr->count, cmp);                                                                      \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, resize)(__nano_t(type, stack) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, resize)(&(arr->buffer), lenght);                                                                                            \
        arr->lenght = lenght;                                                                                                                                    \
    }                                                                                                                                                            \
    size_t __nano_fn(type, stack, count)(__nano_t(type, stack) * arr, type value)                                                                                \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, count)(arr->buffer, value, arr->count);                                                                              \
    }                                                                                                                                                            \
    size_t __nano_fn(type, stack, count_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, count_cmp)(arr->buffer, value, arr->count, cmp);                                                                     \
    }                                                                                                                                                            \
    bool __nano_fn(type, stack, all)(__nano_t(type, stack) * arr, type value)                                                                                    \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, all)(arr->buffer, value, arr->count);                                                                                \
    }                                                                                                                                                            \
    bool __nano_fn(type, stack, all_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, all_cmp)(arr->buffer, value, arr->count, cmp);                                                                       \
    }                                                                                                                                                            \
    bool __nano_fn(type, stack, any)(__nano_t(type, stack) * arr, type value)                                                                                    \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, any)(arr->buffer, value, arr->count);                                                                                \
    }                                                                                                                                                            \
    bool __nano_fn(type, stack, any_cmp)(__nano_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, any_cmp)(arr->buffer, value, arr->count, cmp);                                                                       \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, join)(__nano_t(type, stack) * a, __nano_t(type, stack) * b)                                                                      \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->count, b->count);                                                                         \
        a->count += b->count;                                                                                                                                    \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, reverse)(__nano_t(type, stack) * arr)                                                                                            \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, reverse)(arr->buffer, arr->count);                                                                                          \
    }                                                                                                                                                            \
    size_t __nano_fn(type, stack, lenght)(__nano_t(type, stack) * arr)                                                                                           \
    {                                                                                                                                                            \
        return arr->lenght;                                                                                                                                      \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, map)(__nano_t(type, stack) * arr, type * *out, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, map)(arr->buffer, out, arr->count, map_fn);                                                                                 \
    }                                                                                                                                                            \
    void __nano_fn(type, stack, filter)(__nano_t(type, stack) * arr, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, filter)(arr->buffer, out, arr->count, filter_fn, out_len);                                                                  \
    }

#endif