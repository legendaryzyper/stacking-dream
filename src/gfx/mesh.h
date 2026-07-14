#pragma once

#include "../gfx/gfx.h"
#include "../util/util.h"

#include "../gfx/vertex_array.h"
#include "../gfx/buffer.h"
#include "../gfx/texture.h"

typedef struct Vertex {
    vec3s position;
    vec3s normal;
    vec2s uv;
    vec4s tangent;
} Vertex;

typedef struct Mesh {
    Vertex *vertices;
    u32 *indices;
    VertexArray VAO;
    Buffer VBO, EBO;
    Texture *texture;
} Mesh;

void mesh_init(Mesh *self, Vertex *vertices, u32 *indices, Texture *texture);
void mesh_render(Mesh *self);
void mesh_destroy(Mesh *self);
