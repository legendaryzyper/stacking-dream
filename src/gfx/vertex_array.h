#pragma once

#include "gfx.h"
#include "../util/util.h"

#include "buffer.h"

typedef struct VertexArray {
    GLuint handle;
} VertexArray;

void vertex_array_bind(VertexArray *self);
void vertex_array_attrib(VertexArray *self, Buffer *vbo, GLuint index, GLint size, GLenum type,
                         GLsizei stride, size_t offset);
void vertex_array_init(VertexArray *self);
void vertex_array_destroy(VertexArray *self);