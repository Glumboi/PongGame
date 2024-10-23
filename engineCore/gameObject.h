#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdint.h>

#include "engineTypes.h"

#define GAME_OBJECT_AS(type, obj) (type) obj

typedef struct gameObject
{
    struct scene *parentScene;

    char *name;
    Location location;
    uint8_t isVisible;

    void (*OnUpdate)(struct gameObject *);
    void (*OnStart)(struct gameObject *);
    void (*OnDestroy)(struct gameObject *);
} GameObject;

GameObject GameObject_NewName(char *name);

void GameObject_New(GameObject *out);
void GameObject_OnUpdate(GameObject *out);
void GameObject_OnStart(GameObject *out);
void GameObject_OnDestroy(GameObject *out);

#endif