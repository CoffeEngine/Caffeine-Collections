#ifndef NANO_LINKED_LIST_IMPL_H
#define NANO_LINKED_LIST_IMPL_H

#include "../internal/nano_macros.h"
#include "../internal/nano_foreach_macro.h"
#include <assert.h>

#define nano_implement_linked_list_for(...) call_macro_x_for_each(nano_implement_linked_list, __VA_ARGS__)

#define nano_implement_linked_list(type)                                                                                                                                    \
    void __nano_fn(type, linked_list, create)(__nano_t(type, linked_list) * arr)                                                                                            \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        arr->count = 0;                                                                                                                                                     \
        arr->first = 0;                                                                                                                                                     \
        arr->last = 0;                                                                                                                                                      \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, insert)(__nano_t(type, linked_list) * arr, type value, size_t index)                                                                  \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert((arr->count > 0 && arr->count > index) || arr->count == 0);                                                                                                  \
        if (index == 0)                                                                                                                                                     \
        {                                                                                                                                                                   \
            __nano_t(type, linked_list_node_t) *new_node = nano_malloc(sizeof(__nano_t(type, linked_list_node_t)));                                                         \
            new_node->value = value;                                                                                                                                        \
            new_node->pnext = arr->first;                                                                                                                                   \
            arr->first = new_node;                                                                                                                                          \
            arr->count++;                                                                                                                                                   \
        }                                                                                                                                                                   \
        else                                                                                                                                                                \
        {                                                                                                                                                                   \
            assert(arr->first != NULL);                                                                                                                                     \
            __nano_t(type, linked_list_node_t) *aux = arr->first;                                                                                                           \
            for (size_t i = 0; i < index - 1; i++)                                                                                                                          \
            {                                                                                                                                                               \
                aux = aux->pnext;                                                                                                                                           \
            }                                                                                                                                                               \
            __nano_t(type, linked_list_node_t) *new_node = nano_malloc(sizeof(__nano_t(type, linked_list_node_t)));                                                         \
            new_node->value = value;                                                                                                                                        \
            new_node->pnext = aux->pnext;                                                                                                                                   \
            aux->pnext = new_node;                                                                                                                                          \
            if (aux == arr->last)                                                                                                                                           \
                arr->last = new_node;                                                                                                                                       \
            arr->count++;                                                                                                                                                   \
        }                                                                                                                                                                   \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, set)(__nano_t(type, linked_list) * arr, type value, size_t index)                                                                     \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(arr->count > index);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *aux = arr->first;                                                                                                               \
        for (size_t i = 0; i < index; i++)                                                                                                                                  \
        {                                                                                                                                                                   \
            aux = aux->pnext;                                                                                                                                               \
        }                                                                                                                                                                   \
        aux->value = value;                                                                                                                                                 \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, add)(__nano_t(type, linked_list) * arr, type value)                                                                                   \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        __nano_t(type, linked_list_node_t) *new_node = nano_malloc(sizeof(__nano_t(type, linked_list_node_t)));                                                             \
        new_node->value = value;                                                                                                                                            \
        new_node->pnext = 0;                                                                                                                                                \
        if (arr->count == 0)                                                                                                                                                \
        {                                                                                                                                                                   \
            arr->last = new_node;                                                                                                                                           \
            arr->first = arr->last;                                                                                                                                         \
        }                                                                                                                                                                   \
        else                                                                                                                                                                \
        {                                                                                                                                                                   \
            arr->last->pnext = new_node;                                                                                                                                    \
            arr->last = new_node;                                                                                                                                           \
        }                                                                                                                                                                   \
        arr->count++;                                                                                                                                                       \
    }                                                                                                                                                                       \
    type __nano_fn(type, linked_list, remove)(__nano_t(type, linked_list) * arr, size_t index)                                                                              \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(arr->count > index);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *rem = arr->first, *last = 0;                                                                                                    \
        for (size_t i = 0; i < index; i++)                                                                                                                                  \
        {                                                                                                                                                                   \
            if (rem->pnext == NULL)                                                                                                                                         \
                break;                                                                                                                                                      \
            last = rem;                                                                                                                                                     \
            rem = rem->pnext;                                                                                                                                               \
        }                                                                                                                                                                   \
                                                                                                                                                                            \
        if (rem == arr->last)                                                                                                                                               \
        {                                                                                                                                                                   \
            arr->last = last;                                                                                                                                               \
            arr->last->pnext = 0;                                                                                                                                           \
        }                                                                                                                                                                   \
        else if (rem == arr->first)                                                                                                                                         \
        {                                                                                                                                                                   \
            arr->first = arr->first->pnext;                                                                                                                                 \
        }                                                                                                                                                                   \
        else                                                                                                                                                                \
            last->pnext = rem->pnext;                                                                                                                                       \
        type v = rem->value;                                                                                                                                                \
        nano_free(rem);                                                                                                                                                     \
        arr->count--;                                                                                                                                                       \
        return v;                                                                                                                                                           \
    }                                                                                                                                                                       \
    type __nano_fn(type, linked_list, get)(__nano_t(type, linked_list) * arr, size_t index)                                                                                 \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(arr->count > index);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < index; i++)                                                                                                                                  \
        {                                                                                                                                                                   \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return current->value;                                                                                                                                              \
    }                                                                                                                                                                       \
    type __nano_fn(type, linked_list, first)(__nano_t(type, linked_list) * arr)                                                                                             \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        return arr->first->value;                                                                                                                                           \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, copy)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out, size_t start, size_t end)                                \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(out != NULL);                                                                                                                                                \
        assert(*out != NULL);                                                                                                                                               \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(arr->count > start);                                                                                                                                         \
        assert(arr->count > end);                                                                                                                                           \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < start; i++)                                                                                                                                  \
        {                                                                                                                                                                   \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        __nano_t(type, linked_list_node_t) *new_node = nano_malloc(sizeof(__nano_t(type, linked_list_node_t)));                                                             \
        new_node->pnext = 0;                                                                                                                                                \
        new_node->value = current->value;                                                                                                                                   \
        current = current->pnext;                                                                                                                                           \
                                                                                                                                                                            \
        (*out)->first = new_node;                                                                                                                                           \
        (*out)->count = 1;                                                                                                                                                  \
        __nano_t(type, linked_list_node_t) *currento = (*out)->first;                                                                                                       \
                                                                                                                                                                            \
        for (size_t i = start + 1; i < end; i++)                                                                                                                            \
        {                                                                                                                                                                   \
            new_node = nano_malloc(sizeof(__nano_t(type, linked_list_node_t)));                                                                                             \
            new_node->pnext = 0;                                                                                                                                            \
            new_node->value = current->value;                                                                                                                               \
                                                                                                                                                                            \
            currento->pnext = new_node;                                                                                                                                     \
                                                                                                                                                                            \
            current = current->pnext;                                                                                                                                       \
            currento = currento->pnext;                                                                                                                                     \
            (*out)->count++;                                                                                                                                                \
        }                                                                                                                                                                   \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, clone)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out)                                                         \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(out != NULL);                                                                                                                                                \
        assert(*out != NULL);                                                                                                                                               \
        assert(arr->first != NULL);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
                                                                                                                                                                            \
        __nano_t(type, linked_list_node_t) *new_node = nano_malloc(sizeof(__nano_t(type, linked_list_node_t)));                                                             \
        new_node->pnext = 0;                                                                                                                                                \
        new_node->value = current->value;                                                                                                                                   \
        current = current->pnext;                                                                                                                                           \
                                                                                                                                                                            \
        (*out)->first = new_node;                                                                                                                                           \
        (*out)->count = 1;                                                                                                                                                  \
        __nano_t(type, linked_list_node_t) *currento = (*out)->first;                                                                                                       \
                                                                                                                                                                            \
        for (size_t i = 1; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            new_node = nano_malloc(sizeof(__nano_t(type, linked_list_node_t)));                                                                                             \
            new_node->pnext = 0;                                                                                                                                            \
            new_node->value = current->value;                                                                                                                               \
                                                                                                                                                                            \
            currento->pnext = new_node;                                                                                                                                     \
                                                                                                                                                                            \
            current = current->pnext;                                                                                                                                       \
            currento = currento->pnext;                                                                                                                                     \
            (*out)->count++;                                                                                                                                                \
        }                                                                                                                                                                   \
    }                                                                                                                                                                       \
    bool __nano_fn(type, linked_list, equal)(__nano_t(type, linked_list) * a, __nano_t(type, linked_list) * b)                                                              \
    {                                                                                                                                                                       \
        assert(a != NULL);                                                                                                                                                  \
        assert(b != NULL);                                                                                                                                                  \
        assert(a->first != NULL);                                                                                                                                           \
        assert(b->first != NULL);                                                                                                                                           \
        if (a->count != b->count)                                                                                                                                           \
            return false;                                                                                                                                                   \
        __nano_t(type, linked_list_node_t) *currenta = a->first;                                                                                                            \
        __nano_t(type, linked_list_node_t) *currentb = b->first;                                                                                                            \
        for (size_t i = 0; i < a->count; i++)                                                                                                                               \
        {                                                                                                                                                                   \
            if (currenta->value != currentb->value)                                                                                                                         \
                return false;                                                                                                                                               \
            currenta = currenta->pnext;                                                                                                                                     \
            currentb = currentb->pnext;                                                                                                                                     \
        }                                                                                                                                                                   \
        return true;                                                                                                                                                        \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, fill)(__nano_t(type, linked_list) * arr, type value)                                                                                  \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            current->value = value;                                                                                                                                         \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
    }                                                                                                                                                                       \
    int __nano_fn(type, linked_list, find)(__nano_t(type, linked_list) * arr, type value)                                                                                   \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (current->value == value)                                                                                                                                    \
            {                                                                                                                                                               \
                return i;                                                                                                                                                   \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return -1;                                                                                                                                                          \
    }                                                                                                                                                                       \
    int __nano_fn(type, linked_list, find_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b))                                                  \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(cmp != NULL);                                                                                                                                                \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (cmp(current->value, value))                                                                                                                                 \
            {                                                                                                                                                               \
                return i;                                                                                                                                                   \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return -1;                                                                                                                                                          \
    }                                                                                                                                                                       \
    size_t __nano_fn(type, linked_list, count)(__nano_t(type, linked_list) * arr, type value)                                                                               \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        size_t c = 0;                                                                                                                                                       \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (current->value == value)                                                                                                                                    \
            {                                                                                                                                                               \
                c++;                                                                                                                                                        \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return c;                                                                                                                                                           \
    }                                                                                                                                                                       \
    size_t __nano_fn(type, linked_list, count_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b))                                              \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(cmp != NULL);                                                                                                                                                \
        size_t c = 0;                                                                                                                                                       \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (cmp(current->value, value))                                                                                                                                 \
            {                                                                                                                                                               \
                c++;                                                                                                                                                        \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return c;                                                                                                                                                           \
    }                                                                                                                                                                       \
    bool __nano_fn(type, linked_list, all)(__nano_t(type, linked_list) * arr, type value)                                                                                   \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (current->value != value)                                                                                                                                    \
            {                                                                                                                                                               \
                return false;                                                                                                                                               \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return true;                                                                                                                                                        \
    }                                                                                                                                                                       \
    bool __nano_fn(type, linked_list, all_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b))                                                  \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(cmp != NULL);                                                                                                                                                \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (!cmp(current->value, value))                                                                                                                                \
            {                                                                                                                                                               \
                return false;                                                                                                                                               \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return true;                                                                                                                                                        \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, join)(__nano_t(type, linked_list) * a, __nano_t(type, linked_list) * b)                                                               \
    {                                                                                                                                                                       \
        assert(a != NULL);                                                                                                                                                  \
        assert(b != NULL);                                                                                                                                                  \
        assert(a->first != NULL);                                                                                                                                           \
        assert(b->first != NULL);                                                                                                                                           \
        __nano_t(type, linked_list_node_t) *current = a->first;                                                                                                             \
        while (current->pnext != NULL)                                                                                                                                      \
        {                                                                                                                                                                   \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        current->pnext = b->first;                                                                                                                                          \
        a->last = b->last;                                                                                                                                                  \
        a->count += b->count;                                                                                                                                               \
        b->first = 0;                                                                                                                                                       \
        b->count = 0;                                                                                                                                                       \
        b->last = 0;                                                                                                                                                        \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, reverse)(__nano_t(type, linked_list) * arr)                                                                                           \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) **buff = nano_malloc(sizeof(__nano_t(type, linked_list_node_t) *) * arr->count);                                                 \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            buff[i] = current;                                                                                                                                              \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        for (size_t i = arr->count - 1; i > 0; i--)                                                                                                                         \
        {                                                                                                                                                                   \
            buff[i]->pnext = buff[i - 1];                                                                                                                                   \
        }                                                                                                                                                                   \
        buff[0]->pnext = 0;                                                                                                                                                 \
        arr->first = buff[arr->count - 1];                                                                                                                                  \
                                                                                                                                                                            \
        nano_free(buff);                                                                                                                                                    \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, free)(__nano_t(type, linked_list) * arr, void (*custom_free)(type a))                                                                 \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        if (custom_free)                                                                                                                                                    \
        {                                                                                                                                                                   \
            for (size_t i = 0; i < arr->count; i++)                                                                                                                         \
            {                                                                                                                                                               \
                __nano_t(type, linked_list_node_t) *tmp = current;                                                                                                          \
                current = current->pnext;                                                                                                                                   \
                custom_free(tmp->value);                                                                                                                                    \
                nano_free(tmp);                                                                                                                                             \
            }                                                                                                                                                               \
        }                                                                                                                                                                   \
        else                                                                                                                                                                \
        {                                                                                                                                                                   \
            for (size_t i = 0; i < arr->count; i++)                                                                                                                         \
            {                                                                                                                                                               \
                __nano_t(type, linked_list_node_t) *tmp = current;                                                                                                          \
                current = current->pnext;                                                                                                                                   \
                nano_free(tmp);                                                                                                                                             \
            }                                                                                                                                                               \
        }                                                                                                                                                                   \
        arr->first = 0;                                                                                                                                                     \
        arr->last = 0;                                                                                                                                                      \
    }                                                                                                                                                                       \
    size_t __nano_fn(type, linked_list, lenght)(__nano_t(type, linked_list) * arr)                                                                                          \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        return arr->count;                                                                                                                                                  \
    }                                                                                                                                                                       \
    bool __nano_fn(type, linked_list, any)(__nano_t(type, linked_list) * arr, type value)                                                                                   \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (current->value == value)                                                                                                                                    \
            {                                                                                                                                                               \
                return true;                                                                                                                                                \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return false;                                                                                                                                                       \
    }                                                                                                                                                                       \
    bool __nano_fn(type, linked_list, any_cmp)(__nano_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b))                                                  \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(arr->first != NULL);                                                                                                                                         \
        assert(cmp != NULL);                                                                                                                                                \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            if (cmp(current->value, value))                                                                                                                                 \
            {                                                                                                                                                               \
                return true;                                                                                                                                                \
            }                                                                                                                                                               \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
        return false;                                                                                                                                                       \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, map)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out, type(*map)(type value, size_t index))                     \
    {                                                                                                                                                                       \
        assert(arr != NULL);                                                                                                                                                \
        assert(out != NULL);                                                                                                                                                \
        assert(map != NULL);                                                                                                                                                \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            __nano_fn(type, linked_list, add)(*out, map(current->value, i));                                                                                                \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
    }                                                                                                                                                                       \
    void __nano_fn(type, linked_list, filter)(__nano_t(type, linked_list) * arr, __nano_t(type, linked_list) * *out, type(*filter)(type value, size_t index, int8_t * add)) \
    {                                                                                                                                                                       \
                                                                                                                                                                            \
        assert(arr != NULL);                                                                                                                                                \
        assert(out != NULL);                                                                                                                                                \
        assert(filter != NULL);                                                                                                                                             \
        __nano_t(type, linked_list_node_t) *current = arr->first;                                                                                                           \
        for (size_t i = 0; i < arr->count; i++)                                                                                                                             \
        {                                                                                                                                                                   \
            int8_t _a = 0;                                                                                                                                                  \
            type _v = filter(current->value, i, &_a);                                                                                                                       \
            if (_a > 0)                                                                                                                                                     \
                __nano_fn(type, linked_list, add)(*out, _v);                                                                                                                \
            current = current->pnext;                                                                                                                                       \
        }                                                                                                                                                                   \
    }                                                                                                                                                                       \
    type __nano_fn(type, linked_list, last)(__nano_t(type, linked_list) * arr) { return __nano_fn(type, linked_list, get)(arr, arr->count - 1); }

#endif