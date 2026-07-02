#pragma once

#include "../gfx/gfx.h"
#include "../util/util.h"

typedef struct World World;
typedef struct Mesh Mesh;

#define COMPONENT_TRANSFORM (1 << 0)
#define COMPONENT_MESH (1 << 1)
#define COMPONENT_PHYSIC (1 << 2)
#define COMPONENT_COLLISION (1 << 3)

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

void ecs_init(World *world);
void ecs_input(World *world);
void ecs_tick(World *world);
void ecs_render(World *world);
// maybe dont need update
void ecs_update(World *world);
void ecs_render(World *world);
void ecs_destroy(World *world);

Entity *ecs_spawn_entity(World *world);
