#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct BufferObject {
    GLuint handle;
    GLint type;
} BufferObject;

void buffer_object_buffer(BufferObject *self, void *data, GLsizeiptr size);
void buffer_object_bind(BufferObject *self);
void buffer_object_init(BufferObject *self, GLint type);
void buffer_object_destroy(BufferObject *self);