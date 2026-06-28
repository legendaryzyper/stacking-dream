#include "camera.h"
#include "../gfx/window.h"

void camera_init(Camera *self) {
    memset(self, 0, sizeof(Camera));
    self->fov = radians(45);
    self->znear = 0.01f;
    self->zfar = 1000.0f;
    self->yaw = -PI_2;
}

void camera_input(Camera* self) {
    self->yaw += window.mouse.delta.x * window.mouse.sensitivity * 0.001f;
    self->yaw = (self->yaw < 0 ? TAU : 0.0f) + fmodf(self->yaw, TAU);
    self->pitch -= window.mouse.delta.y * window.mouse.sensitivity * 0.001f;
    self->pitch = clamp(self->pitch, -PI_2 + 0.01f, PI_2 - 0.01f);
}

void camera_update(Camera *self) {
    self->direction = glms_vec3_normalize((vec3s){
        {cosf(self->pitch) * cosf(self->yaw), sinf(self->pitch), cosf(self->pitch) * sinf(self->yaw)}});
    self->right = glms_vec3_normalize(glms_vec3_cross(self->direction, (vec3s){{0.0f, 1.0f, 0.0f}}));
    self->up = glms_vec3_normalize(glms_vec3_cross(self->right, self->direction));

    self->view = glms_lookat(self->position, glms_vec3_add(self->position, self->direction), self->up);

    self->aspect = (f32)window.size.x / window.size.y;
    self->projection = glms_perspective(self->fov, self->aspect, self->znear, self->zfar);
}

void camera_destroy(Camera *self) {}