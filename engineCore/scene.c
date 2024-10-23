#include "scene.h"

void Scene_Create(Scene *scene, char *name)
{
    if (!scene || !name)
        return;

    scene->name = name;
    scene->objects = (GameObjectVector){.head = {.len = 0}};
    scene->OnUpdate = Scene_OnUpdate;
    scene->OnStart = Scene_OnStart;
    scene->OnDestroy = Scene_OnDestroy;
}

void Scene_OnStart(Scene *scene)
{
    if (!scene)
        return;

    printf("Scene [%s] started!\n", scene->name);

    G_VECTOR_FOR(scene->objects, i)
    {
        GameObject *obj = G_VECTOR_ITEM_AT(GameObject *, scene->objects, i);
        if (obj && obj->OnStart)
            obj->OnStart(obj);
    }
}

void Scene_LoadGameObjects(Scene *scene, GameObject *objects, size_t objectsLen)
{
    if (!scene || !objects)
        return;

    for (size_t i = 0; i < objectsLen; i++)
    {
        G_VECTOR_PUSH_BACK(GameObject, scene->objects, objects[i]);
    }
}

void Scene_OnUpdate(Scene *scene)
{
    G_VECTOR_FOR(scene->objects, i)
    {
        GameObject *obj = G_VECTOR_ITEM_AT(GameObject *, scene->objects, i);
        if (obj && obj->OnUpdate)
            obj->OnUpdate(obj);
    }
}

void Scene_OnDestroy(Scene *scene)
{
    G_VECTOR_FOR(scene->objects, i)
    {
        GameObject *obj = G_VECTOR_ITEM_AT(GameObject *, scene->objects, i);
        if (obj && obj->OnDestroy)
            obj->OnDestroy(obj);
    }

    printf("Scene [%s] destroyed!\n", scene->name);
}

void Scene_AddGameObject(Scene *scene, GameObject *gameObject)
{
    if (!scene || !gameObject)
        return;

    gameObject->parentScene = scene;
    G_VECTOR_PUSH_BACK(GameObject *, scene->objects, gameObject);
}

int Scene_FindGameObject(Scene *scene, GameObject **out, char *objectName, uint8_t ignoreCase)
{
    if (!scene || !objectName)
    {
        printf("Error: Null argument passed to Scene_FindGameObject\n");
        return 0;
    }

    if (scene->objects.rawMem == NULL || scene->objects.head.len == 0)
    {
        printf("Error: Scene has no objects or uninitialized data\n");
        return 0;
    }

    printf("Searching for GameObject: %s\n", objectName);

    G_VECTOR_FOR(scene->objects, i)
    {
        GameObject *currentObject = G_VECTOR_ITEM_AT(GameObject *, scene->objects, i);
        if (!currentObject->name)
        {
            printf("Warning: GameObject at index %zu has no name\n", i);
            continue;
        }

        printf("Checking GameObject: %s\n", currentObject->name);

        int comparison = ignoreCase ? strcasecmp(currentObject->name, objectName) : strcmp(currentObject->name, objectName);
        if (comparison == 0)
        {
            printf("Found GameObject: %s\n", currentObject->name);
            *out = currentObject;
            return 1;
        }
    }

    printf("GameObject [%s] not found in scene\n", objectName);
    return 0;
}
