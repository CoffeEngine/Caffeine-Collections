#ifndef NANO_HASH_TABLE_H
#define NANO_HASH_TABLE_H

#include "../internal/nano_macros.h"
#include "../internal/nano_foreach_macro.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

#define __nano_bucket(key_type, value_type) _____concat(__prefix, _____concat(_____concat(key_type, _____concat(_, value_type)), _bucket))

#define __nano_bucket_arr(key_type, value_type) _____concat(__nano_bucket(key_type, value_type), _arr)

#define __nano_t_hash(key, value) __nano_t(_____concat(_____concat(key, _), value), hash)

#define __nano_fn_hash(ktype, vtype, name, fn) _____concat(_____concat(_____concat(__prefix, _____concat(_____concat(_____concat(_____concat(name, _), ktype), _), vtype)), _), fn)

#ifndef CNANO_USE_RAW
#define hash_map(key_type, value_type) __nano_t_hash(key_type, value_type)

#define hash_map_create(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, create)
#define hash_map_add(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, add)
#define hash_map_remove(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, remove)
#define hash_map_get(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, get)
#define hash_map_exist(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, exist)
#define hash_map_free(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, free)
#define hash_map_clear(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, clear)
#define hash_map_lenght(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, lenght)
#define hash_map_clone(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, clone)
#define hash_map_equal(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, equal)
#define hash_map_count_values(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, count_values)
#define hash_map_count_values_cmp(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, count_values_cmp)
#define hash_map_all_values(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, all_values)
#define hash_map_all_values_cmp(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, all_values_cmp)
#define hash_map_any_values(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, any_values)
#define hash_map_any_values_cmp(key_type, value_type) __nano_fn_hash(key_type, value_type, hash_map, any_values_cmp)
#endif

#define nano_declare_hash_table_for(...) call_macro_x_for_each(___i_nano_declare_ht_, __VA_ARGS__)

#define __nano_declare_hash_array(data) \
    typedef struct                      \
    {                                   \
        data *arr;                      \
        size_t len;                     \
        size_t count;                   \
    } _____concat(data, _hash_arr_t);

#define ___nano_declare_hash_table(key_type, value_type)                        \
    typedef struct                                                              \
    {                                                                           \
        key_type key;                                                           \
        value_type value;                                                       \
    } __nano_bucket(key_type, value_type);                                      \
                                                                                \
    __nano_declare_hash_array(__nano_bucket(key_type, value_type));             \
                                                                                \
    typedef struct                                                              \
    {                                                                           \
        _____concat(__nano_bucket(key_type, value_type), _hash_arr_t) * buffer; \
        size_t len;                                                             \
        size_t count;                                                           \
        uintmax_t (*hash_fn)(char *);                                           \
        bool (*cmp_key_fn)(key_type a, key_type b);                             \
    } __nano_t_hash(key_type, value_type);

#define nano_declare_hash_table_alias(key_type, key_alias, value_type, value_alias) \
    typedef key_type key_alias;                                                     \
    typedef value_type value_alias;                                                 \
    nano_declare_hash_table(key_alias, value_alias);

#define ___i_nano_declare_ht_(x) nano_declare_hash_table x

#define nano_declare_hash_table(key_type, value_type)                                                                                                                                                    \
    ___nano_declare_hash_table(key_type, value_type);                                                                                                                                                    \
    void __nano_fn_hash(key_type, value_type, hash_map, create)(__nano_t_hash(key_type, value_type) * hash_ptr, size_t lenght, uintmax_t(*hash_fn)(char *), bool (*cmp_key_fn)(key_type a, key_type b)); \
    void __nano_fn_hash(key_type, value_type, hash_map, add)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type value);                                                            \
    bool __nano_fn_hash(key_type, value_type, hash_map, get)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type * value);                                                          \
    bool __nano_fn_hash(key_type, value_type, hash_map, exist)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key);                                                                            \
    bool __nano_fn_hash(key_type, value_type, hash_map, remove)(__nano_t_hash(key_type, value_type) * hash_ptr, key_type key);                                                                           \
    void __nano_fn_hash(key_type, value_type, hash_map, free)(__nano_t_hash(key_type, value_type) * hash_ptr);                                                                                           \
    void __nano_fn_hash(key_type, value_type, hash_map, clear)(__nano_t_hash(key_type, value_type) * hash_ptr);                                                                                          \
    void __nano_fn_hash(key_type, value_type, hash_map, clone)(__nano_t_hash(key_type, value_type) * source, __nano_t_hash(key_type, value_type) * *dest);                                               \
    bool __nano_fn_hash(key_type, value_type, hash_map, equal)(__nano_t_hash(key_type, value_type) * a, __nano_t_hash(key_type, value_type) * b);                                                        \
    size_t __nano_fn_hash(key_type, value_type, hash_map, lenght)(__nano_t_hash(key_type, value_type) * hash_ptr);                                                                                       \
    size_t __nano_fn_hash(key_type, value_type, hash_map, count_values)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value);                                                               \
    size_t __nano_fn_hash(key_type, value_type, hash_map, count_values_cmp)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b));                  \
    bool __nano_fn_hash(key_type, value_type, hash_map, all_values)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value);                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, all_values_cmp)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b));                      \
    bool __nano_fn_hash(key_type, value_type, hash_map, any_values)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value);                                                                   \
    bool __nano_fn_hash(key_type, value_type, hash_map, any_values_cmp)(__nano_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b));

#define ___i___hash_map_foreach_0(key_type, value_type, p_hash, code)    \
    {                                                                    \
        for (size_t i = 0; i < p_hash->len; i++)                         \
        {                                                                \
            for (size_t k = 0; k < p_hash->buffer[i].count; k++)         \
            {                                                            \
                key_type cnano_key = p_hash->buffer[i].arr[k].key;       \
                value_type cnano_value = p_hash->buffer[i].arr[k].value; \
                code;                                                    \
            }                                                            \
        }                                                                \
    }

#define ___i___hash_map_foreach_1(key_type, value_type, p_hash, code, key_name) \
    {                                                                           \
        for (size_t i = 0; i < p_hash->len; i++)                                \
        {                                                                       \
            for (size_t k = 0; k < p_hash->buffer[i].count; k++)                \
            {                                                                   \
                key_type key_name = p_hash->buffer[i].arr[k].key;               \
                value_type cnano_value = p_hash->buffer[i].arr[k].value;        \
                code;                                                           \
            }                                                                   \
        }                                                                       \
    }

#define ___i___hash_map_foreach_2(key_type, value_type, p_hash, code, key_name, value_name) \
    {                                                                                       \
        for (size_t i = 0; i < p_hash->len; i++)                                            \
        {                                                                                   \
            for (size_t k = 0; k < p_hash->buffer[i].count; k++)                            \
            {                                                                               \
                key_type key_name = p_hash->buffer[i].arr[k].key;                           \
                value_type value_name = p_hash->buffer[i].arr[k].value;                     \
                code;                                                                       \
            }                                                                               \
        }                                                                                   \
    }
#endif