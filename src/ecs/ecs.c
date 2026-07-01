#include "ecs.h"

#include "../world/world.h"
#include "../state.h"

void ecs_init(World *w) { w->entities_count = 0; }

void ecs_input(World *w) {}

void ecs_tick(World *w) {
    float arr[3] = {0.2f, 0.3f, 0.5f};
    for (u32 i = 0; i < w->entities_count; i++) {
        Entity *e = &w->entities[i];
        e->transform.rotation.y += arr[i];
        e->transform.rotation.x += arr[i];
    }
}

void ecs_update(World *w) {}

void ecs_destroy(World *w) {}

void ecs_render(World *w) {
    for (u32 i = 0; i < w->entities_count; i++) {

        TransformComponent *t = &w->entities[i].transform;
        mat4s model = glms_mat4_identity();
        model = glms_translate(model, t->position);
        model = glms_rotate(model, glm_rad(t->rotation.x), (vec3s){{1, 0, 0}});
        model = glms_rotate(model, glm_rad(t->rotation.y), (vec3s){{0, 1, 0}});
        model = glms_rotate(model, glm_rad(t->rotation.z), (vec3s){{0, 0, 1}});
        model = glms_scale(model, t->scale);

        shader_uniform_mat4(&state.shader, "model", model);
        mesh_render(w->entities[i].mesh);
    }
}

Entity *spawn_entity(World *w) {
    u32 idx = w->entities_count;
    w->entities_count++;

    w->entities[idx].mask = 0;
    w->entities[idx].transform = (TransformComponent){0};
    w->entities[idx].transform.scale = (vec3s){{1, 1, 1}};
    w->entities[idx].mesh = NULL;

    return &w->entities[idx];
}
