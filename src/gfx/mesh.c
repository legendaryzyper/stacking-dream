#include "mesh.h"
#include "../gfx/shader.h"
#include "../state.h"

void mesh_init(Mesh *self, f32 *vertices, u32 *indices, Texture *texture) {
    memset(self, 0, sizeof(Mesh));
    vertex_array_init(&self->VAO);
    vertex_array_bind(&self->VAO);
    buffer_init(&self->VBO, GL_ARRAY_BUFFER, vertices, arrlen(vertices) * sizeof(f32));
    buffer_init(&self->EBO, GL_ELEMENT_ARRAY_BUFFER, indices, arrlen(indices) * sizeof(u32));
    self->vertices = vertices;
    self->indices = indices;
    self->texture = texture;

    GL_LAYOUT_LOCATION(0, 3, GL_FLOAT, 5 * sizeof(f32), 0);
    GL_LAYOUT_LOCATION(1, 2, GL_FLOAT, 5 * sizeof(f32), 3 * sizeof(f32));
}

void mesh_render(Mesh *self) {
    shader_uniform_int(&state.shader, "tex", self->texture->slot);
    texture_bind(self->texture);
    vertex_array_bind(&self->VAO);

    glDrawElements(GL_TRIANGLES, arrlen(self->indices), GL_UNSIGNED_INT, NULL);
}

void mesh_destroy(Mesh *self) {
    vertex_array_destroy(&self->VAO);
    buffer_destroy(&self->VBO);
    buffer_destroy(&self->EBO);
}
