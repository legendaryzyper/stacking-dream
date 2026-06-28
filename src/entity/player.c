#include "player.h"
#include "../gfx/window.h"

void player_init(Player *self) {
    memset(self, 0, sizeof(Player));
    camera_init(&self->camera);
}

void player_input(Player *self) { camera_input(&self->camera); }

void player_tick(Player* self) {
    vec3s movement, forward, right;

    movement = GLMS_VEC3_ZERO;
    forward = (vec3s){{cosf(self->camera.yaw), 0.0f, sinf(self->camera.yaw)}};
    right = glms_vec3_cross(forward, (vec3s){{0.0f, 1.0f, 0.0f}});

    if (window.keyboard.keys[GLFW_KEY_W].down) { movement = glms_vec3_add(movement, forward); }

    if (window.keyboard.keys[GLFW_KEY_S].down) { movement = glms_vec3_sub(movement, forward); }

    if (window.keyboard.keys[GLFW_KEY_D].down) { movement = glms_vec3_add(movement, right); }

    if (window.keyboard.keys[GLFW_KEY_A].down) { movement = glms_vec3_sub(movement, right); }

    if (window.keyboard.keys[GLFW_KEY_SPACE].down) {
        movement = glms_vec3_add(movement, (vec3s){{0.0f, 1.0f, 0.0f}});
    }

    if (window.keyboard.keys[GLFW_KEY_LEFT_SHIFT].down) {
        movement = glms_vec3_sub(movement, (vec3s){{0.0f, 1.0f, 0.0f}});
    }

    if (glms_vec3_norm(movement) > F32_EPSILON) {
        movement = glms_vec3_normalize(movement);
        movement = glms_vec3_scale(movement, self->speed / window.tickrate);

        self->position = glms_vec3_add(self->position, movement);
    }
}

void player_update(Player *self) {
    self->camera.position = self->position;
    camera_update(&self->camera);
}

void player_destroy(Player *self) { camera_destroy(&self->camera); }