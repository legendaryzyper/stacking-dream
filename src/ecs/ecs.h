#pragma once

#include "../gfx/gfx.h"
#include "../util/util.h"

typedef struct World World;
typedef struct Mesh Mesh;

typedef struct {
    vec3s position;
    vec3s scale;
    vec3s rotation;
} TransformComponent;

// not accountable for object destruction yet
typedef struct {
    u32 mask;
    TransformComponent transform;
    // PhysicComponent physic;
    // CollisionComponent collison;
    Mesh *mesh;
} Entity;

void ecs_init(World *w);
void ecs_input(World *w);
void ecs_tick(World *w);
void ecs_render(World *w);
// maybe dont need update
void ecs_update(World *w);
void ecs_render(World *w);
void ecs_destroy(World *w);

Entity *spawn_entity(World *w);
