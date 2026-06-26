#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct Buffer {
    GLuint handle;
    GLenum type;
} Buffer;

void buffer_buffer_data(Buffer *self, void *data, GLsizeiptr size);
void buffer_bind(Buffer *self);
void buffer_init(Buffer *self, GLenum type);
void buffer_destroy(Buffer *self);