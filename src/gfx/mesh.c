#include "mesh.h"

#include "../gfx/shader.h"
#include "../state.h"

#include <stddef.h>

void mesh_init(Mesh *self, Vertex *verticies, u32 *indices, Texture *texture) {
    memset(self, 0, sizeof(Mesh));
    vertex_array_init(&self->VAO);
    vertex_array_bind(&self->VAO);
    buffer_init(&self->VBO, GL_ARRAY_BUFFER, verticies, arrlen(verticies) * sizeof(Vertex));
    buffer_init(&self->EBO, GL_ELEMENT_ARRAY_BUFFER, indices, arrlen(indices) * sizeof(u32));

    self->vertices = verticies;
    self->indices = indices;
    self->texture = texture;

    GL_LAYOUT_LOCATION(0, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, position));
    GL_LAYOUT_LOCATION(1, 3, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, normal));
    GL_LAYOUT_LOCATION(2, 2, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, uv));
    GL_LAYOUT_LOCATION(3, 4, GL_FLOAT, sizeof(Vertex), offsetof(Vertex, tangent));
}

void mesh_render(Mesh *self) {
    shader_uniform_int(&state.shader, "tex", self->texture->slot);
    texture_bind(self->texture);
    vertex_array_bind(&self->VAO);

    glDrawElements(GL_TRIANGLES, arrlen(self->indices), GL_UNSIGNED_INT, NULL);
}

void mesh_destroy(Mesh *self) {
    arrfree(self->vertices);
    arrfree(self->indices);
    vertex_array_destroy(&self->VAO);
    buffer_destroy(&self->VBO);
    buffer_destroy(&self->EBO);
    if (self->texture) {
        texture_destroy(self->texture);
        free(self->texture);
    }
}
