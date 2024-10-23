#include "gameObject.h"

GameObject GameObject_NewName(char *name)
{
    GameObject obj;
    obj.name = strdup(name);
    obj.isVisible = 1;
    obj.location = (Location){0, 0};
    obj.OnUpdate = GameObject_OnUpdate;
    obj.OnStart = GameObject_OnStart;
    obj.OnDestroy = GameObject_OnDestroy;
    return obj;
}

void GameObject_New(GameObject *out)
{
    if (!out)
        return;

    out->location = (Location){.x = 10, .y = 10};
    out->OnDestroy = GameObject_OnDestroy;
    out->OnUpdate = GameObject_OnUpdate;
    out->OnStart = GameObject_OnStart;
    out->isVisible = 1;
}

void GameObject_OnUpdate(GameObject *out)
{
}

void GameObject_OnStart(GameObject *out)
{
}

void GameObject_OnDestroy(GameObject *out)
{
}
