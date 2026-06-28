#include "mesh.h"
#include "../gfx/shader.h"
#include "../state.h"

void mesh_init(Mesh *self, void *vertices, GLsizeiptr v_size, void *indices, GLsizeiptr i_size, u64 i_count,
               Texture texture) {
    memset(self, 0, sizeof(Mesh));
    vertex_array_init(&self->VAO);
    vertex_array_bind(&self->VAO);
    buffer_init(&self->VBO, GL_ARRAY_BUFFER, vertices, v_size);
    buffer_init(&self->EBO, GL_ELEMENT_ARRAY_BUFFER, indices, i_size);
    self->indices_count = i_count;

    GL_LAYOUT_LOCATION(0, 3, GL_FLOAT, 5 * sizeof(f32), 0);
    GL_LAYOUT_LOCATION(1, 2, GL_FLOAT, 5 * sizeof(f32), 3 * sizeof(f32));

    shader_uniform_int(&state.shader, "tex", texture.slot);
}

void mesh_render(Mesh *self) {
    shader_uniform_mat4(&state.shader, "model",
                        glms_rotate(glms_mat4_identity(), glm_rad(state.rot), (vec3s){{0.0f, 1.0f, 0.0f}}));

    vertex_array_bind(&self->VAO);

    glDrawElements(GL_TRIANGLES, self->indices_count, GL_UNSIGNED_INT, NULL);
}

void mesh_destroy(Mesh *self) {
    vertex_array_destroy(&self->VAO);
    buffer_destroy(&self->VBO);
    buffer_destroy(&self->EBO);
}