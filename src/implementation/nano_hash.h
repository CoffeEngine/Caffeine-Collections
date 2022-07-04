#ifndef NANO_HASH_IMPL_H
#define NANO_HASH_IMPL_H

#include "../internal/nano_macros.h"
#include "../internal/nano_foreach_macro.h"
#include <assert.h>

#define nano_implement_hash_table_for(...) call_macro_x_for_each(___i_nano_implement_ht_, __VA_ARGS__)

#define ___i_nano_implement_ht_(x) nano_implement_hash_table x

#define ___nano_generic_hash_cmp(key_type)                                     \
    bool _____concat(___nano_def_cmp_, key_type)(key_type a, key_type b)       \
    {                                                                          \
        return nano_memcmp((void *)(&a), (void *)(&b), sizeof(key_type)) == 0; \
    }                                                                          \
                                                                               \
    uintmax_t _____concat(___nano_def_hash_, key_type)(char *key)              \
    {                                                                          \
        assert(key != NULL);                                                   \
        uintmax_t k = 0;                                                       \
        char *c = key;                                                         \
        for (size_t i = 0; i < sizeof(key_type); i++)                          \
        {                                                                      \
            k += (int)(c[i]);                                                  \
        }                                                                      \
        return k;                                                              \
    }

#define nano_implement_hash_table(key_type, value_type)                                                                                                                                                 \
    ___nano_generic_hash_cmp(key_type);                                                                                                                                                                 \
    void __nano_fn_hash(key_type, value_type, hash_map, create)(__nano_t_hash(key_type, value_type) * hash_ptr, size_t lenght, uintmax_t(*hash_fn)(char *), bool (*cmp_key_fn)(key_type a, key_type b)) \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        assert(hash_fn != NULL);                                                                                                                                                                        \
        assert(cmp_key_fn != NULL);                                                                                                                                                                     \
        assert(lenght > 0);                                                                                                                                                                             \
        const size_t __bucket_size = sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t));                                                                                             \
        hash_ptr->len = lenght;                                                                                                                                                                         \
        hash_ptr->hash_fn = (hash_fn != 0) ? (hash_fn) : (_____concat(___nano_def_hash_, key_type));                                                                                                    \
        hash_ptr->cmp_key_fn = (cmp_key_fn != 0) ? (cmp_key_fn) : (_____concat(___nano_def_cmp_, key_type));                                                                                            \
        hash_ptr->buffer = nano_malloc((lenght * __bucket_size));                                                                                                                                       \
        hash_ptr->count = 0;                                                                                                                                                                            \
        check_buffer_overflow_size(hash_ptr->buffer, lenght *__bucket_size);                                                                                                                            \
        for (size_t i = 0; i < lenght; i++)                                                                                                                                                             \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i *__bucket_size);                                                                                                                            \
            hash_ptr->buffer[i].arr = 0;                                                                                                                                                                \
            hash_ptr->buffer[i].count = 0;                                                                                                                                                              \
            hash_ptr->buffer[i].len = 0;                                                                                                                                                                \
        }                                                                                                                                                                                               \
    }                                                                                                                                                                                                   \
    void __nano_fn_hash(key_type, value_type, hash_map, add)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type value)                                                            \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        uintmax_t insert_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                   \
        check_buffer_overflow_acess(hash_ptr->buffer, insert_index * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        _____concat(__nano_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = hash_ptr->buffer + insert_index;                                                                                    \
                                                                                                                                                                                                        \
        if (bucket_arr->len == 0)                                                                                                                                                                       \
        {                                                                                                                                                                                               \
            bucket_arr->len = 2;                                                                                                                                                                        \
            size_t alloc_size = sizeof(__nano_bucket(key_type, value_type)) * bucket_arr->len;                                                                                                          \
                                                                                                                                                                                                        \
            bucket_arr->arr = nano_malloc(alloc_size);                                                                                                                                                  \
        }                                                                                                                                                                                               \
        else                                                                                                                                                                                            \
        {                                                                                                                                                                                               \
            for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                              \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(bucket_arr->arr, i * sizeof(__nano_bucket(key_type, value_type)));                                                                                          \
                if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                                  \
                {                                                                                                                                                                                       \
                    bucket_arr->arr[i].value = value;                                                                                                                                                   \
                    return;                                                                                                                                                                             \
                }                                                                                                                                                                                       \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        if (bucket_arr->count == bucket_arr->len)                                                                                                                                                       \
        {                                                                                                                                                                                               \
            bucket_arr->len *= 2;                                                                                                                                                                       \
            size_t relloc_size = sizeof(__nano_bucket(key_type, value_type)) * bucket_arr->len;                                                                                                         \
                                                                                                                                                                                                        \
            void *ptr = nano_realloc(bucket_arr->arr, relloc_size);                                                                                                                                     \
            if (ptr)                                                                                                                                                                                    \
                bucket_arr->arr = ptr;                                                                                                                                                                  \
        }                                                                                                                                                                                               \
        check_buffer_overflow_acess(bucket_arr->arr, bucket_arr->count * sizeof(__nano_bucket(key_type, value_type)));                                                                                  \
        bucket_arr->arr[bucket_arr->count] = (__nano_bucket(key_type, value_type)){.key = key, .value = value};                                                                                         \
        bucket_arr->count++;                                                                                                                                                                            \
        hash_ptr->count++;                                                                                                                                                                              \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, get)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type * value)                                                          \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                      \
        check_buffer_overflow_acess(hash_ptr->buffer, get_index * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                               \
        _____concat(__nano_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = &(hash_ptr->buffer[get_index]);                                                                                     \
        if (bucket_arr->len == 0 || bucket_arr->count == 0)                                                                                                                                             \
            return false;                                                                                                                                                                               \
                                                                                                                                                                                                        \
        for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                                  \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(bucket_arr->arr, i * sizeof(__nano_bucket(key_type, value_type)));                                                                                              \
            if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                                      \
            {                                                                                                                                                                                           \
                *value = bucket_arr->arr[i].value;                                                                                                                                                      \
                return true;                                                                                                                                                                            \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return false;                                                                                                                                                                                   \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, exist)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key)                                                                            \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                      \
        check_buffer_overflow_acess(hash_ptr->buffer, get_index * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                               \
        _____concat(__nano_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = &(hash_ptr->buffer[get_index]);                                                                                     \
        if (bucket_arr->len == 0 || bucket_arr->count == 0)                                                                                                                                             \
            return false;                                                                                                                                                                               \
        for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                                  \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(bucket_arr->arr, i * sizeof(__nano_bucket(key_type, value_type)));                                                                                              \
            if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                                      \
            {                                                                                                                                                                                           \
                return true;                                                                                                                                                                            \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return false;                                                                                                                                                                                   \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, remove)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key)                                                                           \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                      \
        check_buffer_overflow_acess(hash_ptr->buffer, get_index * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                               \
        _____concat(__nano_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = &(hash_ptr->buffer[get_index]);                                                                                     \
        if (bucket_arr->len == 0 || bucket_arr->count == 0)                                                                                                                                             \
            return false;                                                                                                                                                                               \
        bool found = false;                                                                                                                                                                             \
        for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                                  \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(bucket_arr->arr, (i) * sizeof(__nano_bucket(key_type, value_type)));                                                                                            \
            if (found)                                                                                                                                                                                  \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(bucket_arr->arr, (i - 1) * sizeof(__nano_bucket(key_type, value_type)));                                                                                    \
                bucket_arr->arr[i - 1] = bucket_arr->arr[i];                                                                                                                                            \
            }                                                                                                                                                                                           \
            else if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                                 \
            {                                                                                                                                                                                           \
                found = true;                                                                                                                                                                           \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        if (found)                                                                                                                                                                                      \
        {                                                                                                                                                                                               \
            bucket_arr->count--;                                                                                                                                                                        \
            hash_ptr->count--;                                                                                                                                                                          \
        }                                                                                                                                                                                               \
        return found;                                                                                                                                                                                   \
    }                                                                                                                                                                                                   \
    void __nano_fn_hash(key_type, value_type, hash_map, free)(__nano_t_hash(key_type, value_type) * hash_ptr)                                                                                           \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            nano_free(hash_ptr->buffer[i].arr);                                                                                                                                                         \
            hash_ptr->buffer[i].arr = 0;                                                                                                                                                                \
        }                                                                                                                                                                                               \
        nano_free(hash_ptr->buffer);                                                                                                                                                                    \
        hash_ptr->buffer = 0;                                                                                                                                                                           \
    }                                                                                                                                                                                                   \
    void __nano_fn_hash(key_type, value_type, hash_map, clear)(__nano_t_hash(key_type, value_type) * hash_ptr)                                                                                          \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            nano_free(hash_ptr->buffer[i].arr);                                                                                                                                                         \
            hash_ptr->buffer[i].arr = 0;                                                                                                                                                                \
            hash_ptr->buffer[i].count = 0;                                                                                                                                                              \
            hash_ptr->buffer[i].len = 0;                                                                                                                                                                \
        }                                                                                                                                                                                               \
        hash_ptr->count = 0;                                                                                                                                                                            \
    }                                                                                                                                                                                                   \
    size_t __nano_fn_hash(key_type, value_type, hash_map, lenght)(__nano_t_hash(key_type, value_type) * hash_ptr)                                                                                       \
    {                                                                                                                                                                                                   \
        assert(hash_ptr != NULL);                                                                                                                                                                       \
        return hash_ptr->count;                                                                                                                                                                         \
    }                                                                                                                                                                                                   \
    void __nano_fn_hash(key_type, value_type, hash_map, clone)(__nano_t_hash(key_type, value_type) * source, __nano_t_hash(key_type, value_type) * *dest)                                               \
    {                                                                                                                                                                                                   \
        assert(source != NULL);                                                                                                                                                                         \
        assert(dest != NULL);                                                                                                                                                                           \
        assert(*dest != NULL);                                                                                                                                                                          \
        (*dest)->len = source->len;                                                                                                                                                                     \
        (*dest)->count = source->count;                                                                                                                                                                 \
        (*dest)->hash_fn = source->hash_fn;                                                                                                                                                             \
        (*dest)->cmp_key_fn = source->cmp_key_fn;                                                                                                                                                       \
        (*dest)->buffer = nano_malloc(((*dest)->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t))));                                                                          \
        for (size_t i = 0; i < (*dest)->len; i++)                                                                                                                                                       \
        {                                                                                                                                                                                               \
            (*dest)->buffer[i].count = source->buffer[i].count;                                                                                                                                         \
            (*dest)->buffer[i].len = source->buffer[i].len;                                                                                                                                             \
            (*dest)->buffer[i].arr = (__nano_bucket(key_type, value_type) *)nano_malloc(sizeof(__nano_bucket(key_type, value_type)) * source->buffer[i].len);                                           \
            nano_memcpy((*dest)->buffer[i].arr, source->buffer[i].arr, sizeof(__nano_bucket(key_type, value_type)) * source->buffer[i].len);                                                            \
        }                                                                                                                                                                                               \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, equal)(__nano_t_hash(key_type, value_type) * a, __nano_t_hash(key_type, value_type) * b)                                                        \
    {                                                                                                                                                                                                   \
        assert(a != NULL);                                                                                                                                                                              \
        assert(b != NULL);                                                                                                                                                                              \
        if (a->len == b->len &&                                                                                                                                                                         \
            a->count == b->count &&                                                                                                                                                                     \
            a->hash_fn == b->hash_fn &&                                                                                                                                                                 \
            a->cmp_key_fn == b->cmp_key_fn)                                                                                                                                                             \
        {                                                                                                                                                                                               \
            check_buffer_overflow_size(a->buffer, a->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                      \
            for (size_t i = 0; i < a->len; i++)                                                                                                                                                         \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(a->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                      \
                check_buffer_overflow_acess(b->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                      \
                check_buffer_overflow_size(a->buffer[i].arr, sizeof(__nano_bucket(key_type, value_type)) * a->buffer[i].count);                                                                         \
                check_buffer_overflow_size(b->buffer[i].arr, sizeof(__nano_bucket(key_type, value_type)) * a->buffer[i].count);                                                                         \
                if (!(a->buffer[i].count == b->buffer[i].count &&                                                                                                                                       \
                      nano_memcmp(a->buffer[i].arr, b->buffer[i].arr, sizeof(__nano_bucket(key_type, value_type)) * a->buffer[i].count) == 0))                                                          \
                    return false;                                                                                                                                                                       \
            }                                                                                                                                                                                           \
            return true;                                                                                                                                                                                \
        }                                                                                                                                                                                               \
        return false;                                                                                                                                                                                   \
    }                                                                                                                                                                                                   \
    size_t __nano_fn_hash(key_type, value_type, hash_map, count_values)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value)                                                               \
    {                                                                                                                                                                                                   \
        size_t count = 0;                                                                                                                                                                               \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            check_buffer_overflow_size(hash_ptr->buffer[i].arr, hash_ptr->buffer[i].count * sizeof(__nano_bucket(key_type, value_type)));                                                               \
            for (size_t j = 0; j < hash_ptr->buffer[i].count; j++)                                                                                                                                      \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(hash_ptr->buffer[i].arr, j * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                        \
                if (hash_ptr->buffer[i].arr[j].value == value)                                                                                                                                          \
                    count++;                                                                                                                                                                            \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return count;                                                                                                                                                                                   \
    }                                                                                                                                                                                                   \
    size_t __nano_fn_hash(key_type, value_type, hash_map, count_values_cmp)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b))                  \
    {                                                                                                                                                                                                   \
        size_t count = 0;                                                                                                                                                                               \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            check_buffer_overflow_size(hash_ptr->buffer[i].arr, hash_ptr->buffer[i].count * sizeof(__nano_bucket(key_type, value_type)));                                                               \
            for (size_t j = 0; j < hash_ptr->buffer[i].count; j++)                                                                                                                                      \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(hash_ptr->buffer[i].arr, j * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                        \
                if (cmp(hash_ptr->buffer[i].arr[j].value, value))                                                                                                                                       \
                    count++;                                                                                                                                                                            \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return count;                                                                                                                                                                                   \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, all_values)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value)                                                                   \
    {                                                                                                                                                                                                   \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            check_buffer_overflow_size(hash_ptr->buffer[i].arr, hash_ptr->buffer[i].count * sizeof(__nano_bucket(key_type, value_type)));                                                               \
            for (size_t j = 0; j < hash_ptr->buffer[i].count; j++)                                                                                                                                      \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(hash_ptr->buffer[i].arr, j * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                        \
                if (hash_ptr->buffer[i].arr[j].value != value)                                                                                                                                          \
                    return false;                                                                                                                                                                       \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return true;                                                                                                                                                                                    \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, all_values_cmp)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b))                      \
    {                                                                                                                                                                                                   \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            check_buffer_overflow_size(hash_ptr->buffer[i].arr, hash_ptr->buffer[i].count * sizeof(__nano_bucket(key_type, value_type)));                                                               \
            for (size_t j = 0; j < hash_ptr->buffer[i].count; j++)                                                                                                                                      \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(hash_ptr->buffer[i].arr, j * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                        \
                if (!cmp(hash_ptr->buffer[i].arr[j].value, value))                                                                                                                                      \
                    return false;                                                                                                                                                                       \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return true;                                                                                                                                                                                    \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, any_values)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value)                                                                   \
    {                                                                                                                                                                                                   \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            check_buffer_overflow_size(hash_ptr->buffer[i].arr, hash_ptr->buffer[i].count * sizeof(__nano_bucket(key_type, value_type)));                                                               \
            for (size_t j = 0; j < hash_ptr->buffer[i].count; j++)                                                                                                                                      \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(hash_ptr->buffer[i].arr, j * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                        \
                if (hash_ptr->buffer[i].arr[j].value == value)                                                                                                                                          \
                    return true;                                                                                                                                                                        \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return false;                                                                                                                                                                                   \
    }                                                                                                                                                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, any_values_cmp)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b))                      \
    {                                                                                                                                                                                                   \
        check_buffer_overflow_size(hash_ptr->buffer, hash_ptr->len * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                            \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                      \
        {                                                                                                                                                                                               \
            check_buffer_overflow_acess(hash_ptr->buffer, i * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                                   \
            check_buffer_overflow_size(hash_ptr->buffer[i].arr, hash_ptr->buffer[i].count * sizeof(__nano_bucket(key_type, value_type)));                                                               \
            for (size_t j = 0; j < hash_ptr->buffer[i].count; j++)                                                                                                                                      \
            {                                                                                                                                                                                           \
                check_buffer_overflow_acess(hash_ptr->buffer[i].arr, j * sizeof(_____concat(__nano_bucket(key_type, value_type), _hash_arr_t)));                                                        \
                if (cmp(hash_ptr->buffer[i].arr[j].value, value))                                                                                                                                       \
                    return true;                                                                                                                                                                        \
            }                                                                                                                                                                                           \
        }                                                                                                                                                                                               \
        return false;                                                                                                                                                                                   \
    }

#endif