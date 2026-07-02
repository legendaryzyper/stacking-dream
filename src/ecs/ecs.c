#include "ecs.h"

#include "../world/world.h"
#include "../state.h"

void ecs_init(World *world) { world->entities_count = 0; }

void ecs_input(World *world) {}

void ecs_tick(World *world) {
    float arr[3] = {0.2f, 0.3f, 0.5f};
    for (u32 i = 0; i < world->entities_count; i++) {
        Entity *e = &world->entities[i];
        if (!(e->mask & COMPONENT_TRANSFORM)) continue;
        e->transform.rotation.y += arr[i];
        e->transform.rotation.x += arr[i];
    }
}

void ecs_update(World *world) {}

void ecs_destroy(World *world) {}

void ecs_render(World *world) {
    for (u32 i = 0; i < world->entities_count; i++) {
        Entity *e = &world->entities[i];

        if ((e->mask) != (COMPONENT_TRANSFORM | COMPONENT_MESH)) continue;
        TransformComponent *t = &e->transform;
        mat4s model = glms_mat4_identity();
        model = glms_translate(model, t->position);
        model = glms_rotate(model, glm_rad(t->rotation.x), (vec3s){{1, 0, 0}});
        model = glms_rotate(model, glm_rad(t->rotation.y), (vec3s){{0, 1, 0}});
        model = glms_rotate(model, glm_rad(t->rotation.z), (vec3s){{0, 0, 1}});
        model = glms_scale(model, t->scale);

        shader_uniform_mat4(&state.shader, "model", model);
        mesh_render(e->mesh);
    }
}

Entity *ecs_spawn_entity(World *world) {
    u32 idx = world->entities_count;
    world->entities_count++;

    world->entities[idx].mask = 0;
    world->entities[idx].transform = (TransformComponent){0};
    world->entities[idx].transform.scale = (vec3s){{1, 1, 1}};
    world->entities[idx].mesh = NULL;

    return &world->entities[idx];
}
