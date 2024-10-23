#ifndef G_VECTOR_H
#define G_VECTOR_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// Memory Debug Macros
#define MALLOC_DEBUG(size) MallocDebug(size)
#define REALLOC_DEBUG(dst, newSize) ReallocDebug(dst, newSize)

void *ReallocDebug(void *dst, size_t newSize);
void *MallocDebug(size_t size);

// Vector Head Structure
typedef struct g_vector_head
{
    size_t len;
    size_t ptr;
} g_vector_head_t;

// Generic Vector Structure
typedef struct g_vector
{
    struct g_vector_head head;
    void *rawMem;
} g_vector_t;

// Vector Declaration Macro
#define G_VECTOR_STRUCT(vectorType, structName) \
    typedef struct                              \
    {                                           \
        struct g_vector_head head;              \
        vectorType *rawMem;                     \
    } structName;

#define G_VECTOR_OPAGUE(type, name) \
    struct name                     \
    {                               \
        struct g_vector_head head;  \
        type *rawMem;               \
    } name;

// Vector Initialization Macros
#define G_VECTOR_INIT(type, vec, len)                  \
    {                                                  \
        g_vector_init(&vec, len);                      \
        vec.rawMem = MALLOC_DEBUG(len * sizeof(type)); \
    }

#define G_VECTOR_INIT_DEFAULT(type, vec, len, defaultValue) \
    G_VECTOR_INIT(type, vec, len)                           \
    G_VECTOR_SET(type, vec, defaultValue)

// Vector Accessor Macros
#define G_VECTOR_RAW_CONVERTED(type, vec) ((type *)vec.rawMem)

#define G_VECTOR_ITEM_AT(type, vec, index) (type) G_VECTOR_RAW_CONVERTED(type, vec)[index]

// Vector Modifier Macros
#define G_VECTOR_SET(type, vec, val)              \
    {                                             \
        if (!vec.rawMem)                          \
        {                                         \
            G_VECTOR_INIT(type, vec, 1)           \
        }                                         \
                                                  \
        for (size_t i = 0; i < vec.head.len; i++) \
        {                                         \
            ((type *)vec.rawMem)[i] = val;        \
        }                                         \
    }

#define G_VECTOR_SET_INDEX(type, vec, val, i) \
    {                                         \
        if (vec.rawMem)                       \
        {                                     \
            ((type *)vec.rawMem)[i] = val;    \
        }                                     \
    }

#define G_VECTOR_EXPAND(type, vec, expandBy)                                                           \
    {                                                                                                  \
        vec.rawMem = REALLOC_DEBUG(vec.rawMem, vec.head.len * sizeof(type) + expandBy * sizeof(type)); \
        if (vec.rawMem)                                                                                \
            vec.head.len += expandBy;                                                                  \
    }

#define G_VECTOR_PUSH_BACK(type, vec, elementToAdd)                    \
    {                                                                  \
        if (vec.rawMem)                                                \
        {                                                              \
            G_VECTOR_EXPAND(type, vec, 1);                             \
        }                                                              \
        else                                                           \
        {                                                              \
            vec.rawMem = MALLOC_DEBUG(sizeof(type));                   \
            vec.head.len = 1;                                          \
        }                                                              \
        G_VECTOR_SET_INDEX(type, vec, elementToAdd, vec.head.len - 1); \
    }

#define G_VECTOR_REMOVE_AT(type, vec, i)                                         \
    {                                                                            \
        if (vec.rawMem && i < vec.head.len)                                      \
        {                                                                        \
            for (size_t j = i; j < vec.head.len - 1; j++)                        \
            {                                                                    \
                G_VECTOR_RAW_CONVERTED(type, vec)                                \
                [j] = G_VECTOR_RAW_CONVERTED(type, vec)[j + 1];                  \
            }                                                                    \
            vec.head.len--;                                                      \
            vec.rawMem = REALLOC_DEBUG(vec.rawMem, vec.head.len * sizeof(type)); \
        }                                                                        \
    }

#define G_VECTOR_SWAP_XOR(type, vec, iA, iB)               \
    {                                                      \
        if (!(iA > vec.head.len || iB > vec.head.len))     \
        {                                                  \
            G_VECTOR_RAW_CONVERTED(type, vec)              \
            [iA] ^= G_VECTOR_RAW_CONVERTED(type, vec)[iB]; \
            G_VECTOR_RAW_CONVERTED(type, vec)              \
            [iB] ^= G_VECTOR_RAW_CONVERTED(type, vec)[iA]; \
            G_VECTOR_RAW_CONVERTED(type, vec)              \
            [iA] ^= G_VECTOR_RAW_CONVERTED(type, vec)[iB]; \
        }                                                  \
    }

#define G_VECTOR_SWAP_TEMP(type, vec, iA, iB)               \
    {                                                       \
        if (!(iA > vec.head.len || iB > vec.head.len))      \
        {                                                   \
            type a = G_VECTOR_RAW_CONVERTED(type, vec)[iA]; \
            G_VECTOR_RAW_CONVERTED(type, vec)               \
            [iA] = G_VECTOR_RAW_CONVERTED(type, vec)[iB];   \
            G_VECTOR_RAW_CONVERTED(type, vec)               \
            [iB] = a;                                       \
        }                                                   \
    }

#define G_VECTOR_REVERSE_XOR(type, vec)                                             \
    {                                                                               \
        G_VECTOR_FOR(vec, i){                                                       \
            if (i < (vec.head.len / 2)){                                            \
                G_VECTOR_RAW_CONVERTED(type, vec)                                   \
                    [i] ^= G_VECTOR_RAW_CONVERTED(type, vec)[vec.head.len - 1 - i]; \
    G_VECTOR_RAW_CONVERTED(type, vec)                                               \
    [vec.head.len - 1 - i] ^= G_VECTOR_RAW_CONVERTED(type, vec)[i];                 \
    G_VECTOR_RAW_CONVERTED(type, vec)                                               \
    [i] ^= G_VECTOR_RAW_CONVERTED(type, vec)[vec.head.len - 1 - i];                 \
    }                                                                               \
    }                                                                               \
    }

#define G_VECTOR_REVERSE_TEMP(type, vec)                           \
    {                                                              \
        G_VECTOR_FOR(vec, i){                                      \
            if (i < (vec.head.len / 2)){                           \
                type temp = G_VECTOR_RAW_CONVERTED(type, vec)[i];  \
    G_VECTOR_RAW_CONVERTED(type, vec)                              \
    [i] = G_VECTOR_RAW_CONVERTED(type, vec)[vec.head.len - 1 - i]; \
    G_VECTOR_RAW_CONVERTED(type, vec)                              \
    [vec.head.len - 1 - i] = temp;                                 \
    }                                                              \
    }                                                              \
    }

// Vector Utility Macros
#define G_VECTOR_FREE_DATA(vec) \
    {                           \
        if (vec.rawMem)         \
            free(vec.rawMem);   \
        vec.head.len = 0;       \
        vec.head.ptr = 0;       \
    }

// Iteration Macros
#define FOR_RANGE(x, y, iVar) for (size_t iVar = x; iVar < y; iVar++)
#define G_VECTOR_FOR_INDEX(vec, iVar) \
    FOR_RANGE(g_vector_start((g_vector_t *)&vec), g_vector_end((g_vector_t *)&vec), iVar)

// Iterator Macro for Looping Through Vector
#define G_VECTOR_FOR(vec, iVar) G_VECTOR_FOR_INDEX(vec, iVar)

int g_vector_start(g_vector_t *vec);
int g_vector_end(g_vector_t *vec);

// Function to Initialize Vector
void g_vector_init(void *outVec, size_t len);

#endif
