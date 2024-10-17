#include "g_vector.h"

void *ReallocDebug(void *dst, size_t newSize)
{
    printf("{g_vector} Reallocating memory [%d bytes]\n", newSize);
    return realloc(dst, newSize);
}

void *MallocDebug(size_t size)
{
    void *ret = malloc(size);
    if (!ret)
    {
        printf("{g_vector} failed to allocate memory [%d bytes]!\n");
        return NULL;
    }
    printf("{g_vector} Allocated memory [%d bytes]\n", size);
    return ret;
}

int g_vector_start(g_vector_t *vec)
{
    return 0;
}

int g_vector_end(g_vector_t *vec)
{
    if (!vec)
        return 0;
    return vec->head.len;
}

void g_vector_init(void *outVec, size_t len)
{
    if (!outVec)
        return;

    ((g_vector_t *)outVec)->head.len = len;
    ((g_vector_t *)outVec)->head.ptr = 0;
}
