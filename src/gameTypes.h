#ifndef GAMETYPES_H
#define GAMETYPES_H

#include <stdint.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "g_vector.h"

#define VALID_PTR(ptr)                               \
    {                                                \
        if (!ptr)                                    \
            printf("Error: Null pointer access.\n"); \
    }

#define VALID_PTR_RET(ptr, ret) \
    {                           \
        if (!ptr)               \
            return ret;         \
    }

typedef struct location
{
    int x, y;
} Location;

#define GAME_OBJECT_AS(type, obj) (type) obj;

typedef struct gameObject
{
    struct location location;
    uint8_t isVisible;
    char *name;

    void (*ObjectRender)(struct gameObject *);
    void (*ObjectStart)(struct gameObject *);

    void *parentGame;
} GameObject;

G_VECTOR_STRUCT(GameObject *, gameObjectPool_t);

void InitGameObject(GameObject *outObj, void *game);
void InitGameObjectEx(GameObject *outObj, void *game, int initX, int initY);

void RenderGameObject(GameObject *obj);
void StartGameObject(GameObject *obj);

#endif