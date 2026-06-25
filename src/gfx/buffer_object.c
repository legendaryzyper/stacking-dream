#include "buffer_object.h"

void buffer_object_bind(BufferObject *self) { glBindBuffer(self->type, self->handle); }

void buffer_object_buffer(BufferObject *self, void *data, GLsizeiptr size) {
    buffer_object_bind(self);

    glBufferData(self->type, size, data, GL_STATIC_DRAW);
}

void buffer_object_init(BufferObject *self, GLint type) {
    memset(self, 0, sizeof(BufferObject));
    self->type = type;
    glGenBuffers(1, &self->handle);
}

void buffer_object_destroy(BufferObject *self) { glDeleteBuffers(1, &self->handle); }