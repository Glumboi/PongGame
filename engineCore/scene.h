#ifndef SCENE_H
#define SCENE_H

#include <raylib.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "gameObject.h"
#include "engineTypes.h"
#include "g_vector.h"

G_VECTOR_STRUCT(GameObject*, GameObjectVector);

typedef struct scene
{
    char *name;
    GameObjectVector objects;

    void (*OnStart)(struct scene *);
    void (*OnUpdate)(struct scene *);
    void (*OnDestroy)(struct scene *);
} Scene;

void Scene_Create(Scene *scene, char *name);
void Scene_OnStart(Scene *scene);
void Scene_OnUpdate(Scene *scene);
void Scene_OnDestroy(Scene *scene);
void Scene_LoadGameObjects(Scene *scene, GameObject *objects, size_t objectsLen);
void Scene_AddGameObject(Scene *scene, GameObject *gameObject);
int Scene_FindGameObject(Scene *scene, GameObject **out, char *objectName, uint8_t ignoreCase);

#endif