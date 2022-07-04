#ifndef NANO_QUEUE_IMPL_H
#define NANO_QUEUE_IMPL_H

#include "nano_core.h"

#define nano_implement_queue_for(...) call_macro_x_for_each(nano_implement_queue, __VA_ARGS__)

#define nano_implement_queue(type)                                                                                                                               \
    void __nano_fn(type, queue, create)(__nano_t(type, queue) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                            \
        assert(arr != NULL);                                                                                                                                     \
        arr->lenght = lenght;                                                                                                                                    \
        arr->count = 0;                                                                                                                                          \
        __nano_fn(type, __base_name, create)(&(arr->buffer), lenght);                                                                                            \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, free)(__nano_t(type, queue) * arr)                                                                                               \
    {                                                                                                                                                            \
        assert(arr != NULL);                                                                                                                                     \
        assert(arr->buffer != NULL);                                                                                                                             \
        nano_free(arr->buffer);                                                                                                                                  \
        arr->lenght = 0;                                                                                                                                         \
        arr->buffer = 0;                                                                                                                                         \
        arr->count = 0;                                                                                                                                          \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, clear)(__nano_t(type, queue) * arr)                                                                                              \
    {                                                                                                                                                            \
        arr->count = 0;                                                                                                                                          \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, enqueue)(__nano_t(type, queue) * arr, type value)                                                                                \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, push_back)(arr->buffer, value, &arr->count);                                                                                \
    }                                                                                                                                                            \
    type __nano_fn(type, queue, dequeue)(__nano_t(type, queue) * arr)                                                                                            \
    {                                                                                                                                                            \
        type __v = __nano_fn(type, __base_name, first)(arr->buffer);                                                                                             \
        __nano_fn(type, __base_name, pop_front)(arr->buffer, arr->count);                                                                                        \
        arr->count--;                                                                                                                                            \
        return __v;                                                                                                                                              \
    }                                                                                                                                                            \
    type __nano_fn(type, queue, first)(__nano_t(type, queue) * arr)                                                                                              \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, first)(arr->buffer);                                                                                                 \
    }                                                                                                                                                            \
    type __nano_fn(type, queue, last)(__nano_t(type, queue) * arr)                                                                                               \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, last)(arr->buffer, arr->count);                                                                                      \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, copy)(__nano_t(type, queue) * arr, __nano_t(type, queue) * *out, size_t start, size_t end)                                       \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, copy)(arr->buffer, &((*out)->buffer), start, end);                                                                          \
        (*out)->count = (end - start) < arr->count ? (end - start) : arr->count;                                                                                 \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, clone)(__nano_t(type, queue) * arr, __nano_t(type, queue) * *out)                                                                \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, clone)(arr->buffer, &((*out)->buffer), arr->lenght);                                                                        \
        (*out)->count = arr->count;                                                                                                                              \
    }                                                                                                                                                            \
    bool __nano_fn(type, queue, equal)(__nano_t(type, queue) * a, __nano_t(type, queue) * b)                                                                     \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, equal)(a->buffer, b->buffer, a->count);                                                                              \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, fill)(__nano_t(type, queue) * arr, type value)                                                                                   \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, fill)(arr->buffer, value, arr->lenght);                                                                                     \
    }                                                                                                                                                            \
    int __nano_fn(type, queue, find)(__nano_t(type, queue) * arr, type value)                                                                                    \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, find)(arr->buffer, value, arr->count);                                                                               \
    }                                                                                                                                                            \
    int __nano_fn(type, queue, find_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, find_cmp)(arr->buffer, value, arr->count, cmp);                                                                      \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, resize)(__nano_t(type, queue) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, resize)(&(arr->buffer), lenght);                                                                                            \
        arr->lenght = lenght;                                                                                                                                    \
    }                                                                                                                                                            \
    size_t __nano_fn(type, queue, count)(__nano_t(type, queue) * arr, type value)                                                                                \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, count)(arr->buffer, value, arr->count);                                                                              \
    }                                                                                                                                                            \
    size_t __nano_fn(type, queue, count_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, count_cmp)(arr->buffer, value, arr->count, cmp);                                                                     \
    }                                                                                                                                                            \
    bool __nano_fn(type, queue, all)(__nano_t(type, queue) * arr, type value)                                                                                    \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, all)(arr->buffer, value, arr->count);                                                                                \
    }                                                                                                                                                            \
    bool __nano_fn(type, queue, all_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, all_cmp)(arr->buffer, value, arr->count, cmp);                                                                       \
    }                                                                                                                                                            \
    bool __nano_fn(type, queue, any)(__nano_t(type, queue) * arr, type value)                                                                                    \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, any)(arr->buffer, value, arr->count);                                                                                \
    }                                                                                                                                                            \
    bool __nano_fn(type, queue, any_cmp)(__nano_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        return __nano_fn(type, __base_name, any_cmp)(arr->buffer, value, arr->count, cmp);                                                                       \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, join)(__nano_t(type, queue) * a, __nano_t(type, queue) * b)                                                                      \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->count, b->count);                                                                         \
        a->count += b->count;                                                                                                                                    \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, reverse)(__nano_t(type, queue) * arr)                                                                                            \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, reverse)(arr->buffer, arr->count);                                                                                          \
    }                                                                                                                                                            \
    size_t __nano_fn(type, queue, lenght)(__nano_t(type, queue) * arr)                                                                                           \
    {                                                                                                                                                            \
        return arr->lenght;                                                                                                                                      \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, map)(__nano_t(type, queue) * arr, type * *out, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, map)(arr->buffer, out, arr->count, map_fn);                                                                                 \
    }                                                                                                                                                            \
    void __nano_fn(type, queue, filter)(__nano_t(type, queue) * arr, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                            \
        __nano_fn(type, __base_name, filter)(arr->buffer, out, arr->count, filter_fn, out_len);                                                                  \
    }

#endif