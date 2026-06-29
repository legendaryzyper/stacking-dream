#pragma once

#include "../gfx/gfx.h"
#include "../util/util.h"

#include "../gfx/vertex_array.h"
#include "../gfx/buffer.h"
#include "../gfx/texture.h"

typedef struct Mesh {
    f32 *vertices;
    u32 *indices;
    VertexArray VAO;
    Buffer VBO, EBO;
    Texture *texture;
    u64 indices_count;
    vec3s position;
} Mesh;

void mesh_init(Mesh *self, f32 *vertices, u32 *indices, Texture *texture);
void mesh_render(Mesh * self);
void mesh_destroy(Mesh *self);