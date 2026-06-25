#pragma once

#include "gfx.h"
#include "../util/util.h"

#include "buffer_object.h"

typedef struct VertexAttributeObject {
    GLuint handle;
} VertexAttributeObject;

void vertex_attribute_object_bind(VertexAttributeObject *self);
void vertex_attribute_object_attrib(VertexAttributeObject *self, BufferObject *vbo, GLuint index, GLint size,
                                    GLenum type,
                GLsizei stride,
                size_t offset);
void vertex_attribute_object_init(VertexAttributeObject *self);
void vertex_attribute_object_destroy(VertexAttributeObject *self);