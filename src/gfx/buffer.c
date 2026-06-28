#include "buffer.h"

void buffer_bind(Buffer *self) { glBindBuffer(self->type, self->handle); }

void buffer_init(Buffer *self, GLenum type, void *data, GLsizeiptr size) {
    memset(self, 0, sizeof(Buffer));
    self->type = type;
    glGenBuffers(1, &self->handle);

    buffer_bind(self);
    glBufferData(self->type, size, data, GL_STATIC_DRAW);
}

void buffer_destroy(Buffer *self) { glDeleteBuffers(1, &self->handle); }