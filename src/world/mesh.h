#pragma once

#include "../gfx/gfx.h"
#include "../util/util.h"

#include "../gfx/vertex_array.h"
#include "../gfx/buffer.h"
#include "../gfx/texture.h"

typedef struct MeshBuffer {
    void *data;
    u64 count;
} MeshBuffer;

typedef struct Mesh {
    MeshBuffer vertex_data, indices;
    VertexArray VAO;
    Buffer VBO, EBO;
    Texture texture;
    u64 indices_count;
    vec3s position;
} Mesh;

void mesh_init(Mesh *self, void *vertices, GLsizeiptr v_size, void *indices, GLsizeiptr i_size, u64 i_count, Texture texture);
void mesh_render(Mesh * self);
void mesh_destroy(Mesh *self);