#ifndef NANO_VECTOR_IMPL_H
#define NANO_VECTOR_IMPL_H

#include "nano_core.h"

#define nano_implement_vector_for(...) call_macro_x_for_each(nano_implement_vector, __VA_ARGS__)

#define __internal_vec_inc(vec, type, inc)                                            \
    {                                                                                 \
        if (vec->count + inc >= vec->lenght)                                          \
        {                                                                             \
            void *nptr = nano_realloc(vec->buffer, (vec->lenght * 2) * sizeof(type)); \
            if (nptr != NULL)                                                         \
            {                                                                         \
                vec->buffer = nptr;                                                   \
                vec->lenght *= 2;                                                     \
                vec->count += inc;                                                    \
            }                                                                         \
        }                                                                             \
        else                                                                          \
        {                                                                             \
            vec->count += inc;                                                        \
        }                                                                             \
    }

#define __internal_vec_dec(vec, dec) \
    {                                \
        vec->count -= dec;           \
    }

#define nano_implement_vector(type)                                                                                                                                \
    void __nano_fn(type, vector, create)(__nano_t(type, vector) * vec, size_t lenght)                                                                              \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(lenght > 0);                                                                                                                                        \
        vec->lenght = lenght;                                                                                                                                      \
        vec->count = 0;                                                                                                                                            \
        __nano_fn(type, __base_name, create)(&(vec->buffer), lenght);                                                                                              \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, desloc)(__nano_t(type, vector) * vec, size_t from, int steps)                                                                     \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        __internal_vec_inc(vec, type, steps);                                                                                                                      \
        __nano_fn(type, __base_name, desloc)(vec->buffer, vec->lenght, from, steps);                                                                               \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, insert)(__nano_t(type, vector) * vec, type value, size_t index)                                                                   \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(index <= vec->lenght);                                                                                                                              \
        __internal_vec_inc(vec, type, 1);                                                                                                                          \
        __nano_fn(type, __base_name, insert)(vec->buffer, value, index, vec->lenght);                                                                              \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, set)(__nano_t(type, vector) * vec, type value, size_t index)                                                                      \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(index < vec->lenght);                                                                                                                               \
        __nano_fn(type, __base_name, set)(vec->buffer, value, index);                                                                                              \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, remove)(__nano_t(type, vector) * vec, size_t index)                                                                               \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(index < vec->lenght);                                                                                                                               \
        __nano_fn(type, __base_name, remove)(vec->buffer, index, vec->count);                                                                                      \
        __internal_vec_dec(vec, 1);                                                                                                                                \
    }                                                                                                                                                              \
    type __nano_fn(type, vector, get)(__nano_t(type, vector) * vec, size_t index)                                                                                  \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(index < vec->lenght);                                                                                                                               \
        return __nano_fn(type, __base_name, get)(vec->buffer, index);                                                                                              \
    }                                                                                                                                                              \
    type __nano_fn(type, vector, first)(__nano_t(type, vector) * vec)                                                                                              \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, first)(vec->buffer);                                                                                                   \
    }                                                                                                                                                              \
    type __nano_fn(type, vector, last)(__nano_t(type, vector) * vec)                                                                                               \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, last)(vec->buffer, vec->count);                                                                                        \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, push_front)(__nano_t(type, vector) * vec, type value)                                                                             \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        __internal_vec_inc(vec, type, 1);                                                                                                                          \
        __nano_fn(type, __base_name, push_front)(vec->buffer, value, vec->count);                                                                                  \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, push_back)(__nano_t(type, vector) * vec, type value)                                                                              \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        __nano_fn(type, __base_name, push_back)(vec->buffer, value, &(vec->count));                                                                                \
        __internal_vec_inc(vec, type, 0);                                                                                                                          \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, pop_front)(__nano_t(type, vector) * vec)                                                                                          \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        __nano_fn(type, __base_name, pop_front)(vec->buffer, vec->count);                                                                                          \
        __internal_vec_dec(vec, 1);                                                                                                                                \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, pop_back)(__nano_t(type, vector) * vec)                                                                                           \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        __nano_fn(type, __base_name, remove)(vec->buffer, vec->count - 1, vec->count);                                                                             \
        __internal_vec_dec(vec, 1);                                                                                                                                \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, copy)(__nano_t(type, vector) * vec, __nano_t(type, vector) * out, size_t start, size_t end)                                       \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(out != NULL);                                                                                                                                       \
        __nano_fn(type, __base_name, copy)(vec->buffer, &(out->buffer), start, end);                                                                               \
        out->count = (end - start) < vec->count ? (end - start) : vec->count;                                                                                      \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, clone)(__nano_t(type, vector) * vec, __nano_t(type, vector) * out)                                                                \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(out != NULL);                                                                                                                                       \
        __nano_fn(type, __base_name, clone)(vec->buffer, &(out->buffer), vec->lenght);                                                                             \
        out->count = vec->count;                                                                                                                                   \
    }                                                                                                                                                              \
    bool __nano_fn(type, vector, equal)(__nano_t(type, vector) * a, __nano_t(type, vector) * b)                                                                    \
    {                                                                                                                                                              \
        assert(a != NULL);                                                                                                                                         \
        assert(b != NULL);                                                                                                                                         \
        return __nano_fn(type, __base_name, equal)(a->buffer, b->buffer, a->count);                                                                                \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, fill)(__nano_t(type, vector) * vec, type value)                                                                                   \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        __nano_fn(type, __base_name, fill)(vec->buffer, value, vec->lenght);                                                                                       \
    }                                                                                                                                                              \
    int __nano_fn(type, vector, find)(__nano_t(type, vector) * vec, type value)                                                                                    \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, find)(vec->buffer, value, vec->count);                                                                                 \
    }                                                                                                                                                              \
    int __nano_fn(type, vector, find_cmp)(__nano_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(cmp != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, find_cmp)(vec->buffer, value, vec->count, cmp);                                                                        \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, resize)(__nano_t(type, vector) * vec, size_t lenght)                                                                              \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(lenght > 0);                                                                                                                                        \
        __nano_fn(type, __base_name, resize)(&(vec->buffer), lenght);                                                                                              \
        vec->lenght = lenght;                                                                                                                                      \
    }                                                                                                                                                              \
    size_t __nano_fn(type, vector, count)(__nano_t(type, vector) * vec, type value)                                                                                \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, count)(vec->buffer, value, vec->count);                                                                                \
    }                                                                                                                                                              \
    size_t __nano_fn(type, vector, count_cmp)(__nano_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(cmp != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, count_cmp)(vec->buffer, value, vec->count, cmp);                                                                       \
    }                                                                                                                                                              \
    bool __nano_fn(type, vector, all)(__nano_t(type, vector) * vec, type value)                                                                                    \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, all)(vec->buffer, value, vec->count);                                                                                  \
    }                                                                                                                                                              \
    bool __nano_fn(type, vector, any)(__nano_t(type, vector) * vec, type value)                                                                                    \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, any)(vec->buffer, value, vec->count);                                                                                  \
    }                                                                                                                                                              \
    bool __nano_fn(type, vector, all_cmp)(__nano_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(cmp != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, all_cmp)(vec->buffer, value, vec->count, cmp);                                                                         \
    }                                                                                                                                                              \
    bool __nano_fn(type, vector, any_cmp)(__nano_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        assert(cmp != NULL);                                                                                                                                       \
        return __nano_fn(type, __base_name, any_cmp)(vec->buffer, value, vec->count, cmp);                                                                         \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, join)(__nano_t(type, vector) * a, __nano_t(type, vector) * b)                                                                     \
    {                                                                                                                                                              \
        assert(a != NULL);                                                                                                                                         \
        assert(b != NULL);                                                                                                                                         \
        __nano_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->count, b->count);                                                                           \
        a->count += b->count;                                                                                                                                      \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, reverse)(__nano_t(type, vector) * vec)                                                                                            \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        __nano_fn(type, __base_name, reverse)(vec->buffer, vec->count);                                                                                            \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, clear)(__nano_t(type, vector) * vec)                                                                                              \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        vec->lenght = 0;                                                                                                                                           \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, free)(__nano_t(type, vector) * vec)                                                                                               \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        nano_free(vec->buffer);                                                                                                                                    \
        vec->count = 0;                                                                                                                                            \
        vec->lenght = 0;                                                                                                                                           \
        vec->buffer = 0;                                                                                                                                           \
    }                                                                                                                                                              \
    size_t __nano_fn(type, vector, lenght)(__nano_t(type, vector) * vec)                                                                                           \
    {                                                                                                                                                              \
        assert(vec != NULL);                                                                                                                                       \
        return vec->lenght;                                                                                                                                        \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, map)(__nano_t(type, vector) * vec, type * *out, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                              \
        __nano_fn(type, __base_name, map)(vec->buffer, out, vec->count, map_fn);                                                                                   \
    }                                                                                                                                                              \
    void __nano_fn(type, vector, filter)(__nano_t(type, vector) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                              \
        __nano_fn(type, __base_name, filter)(vec->buffer, out, vec->count, filter_fn, out_len);                                                                    \
    }

#endif