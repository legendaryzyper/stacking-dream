#include "buffer.h"

void buffer_bind(Buffer *self) { glBindBuffer(self->type, self->handle); }

void buffer_buffer_data(Buffer *self, void *data, GLsizeiptr size) {
    buffer_bind(self);

    glBufferData(self->type, size, data, GL_STATIC_DRAW);
}

void buffer_init(Buffer *self, GLenum type) {
    memset(self, 0, sizeof(Buffer));
    self->type = type;
    glGenBuffers(1, &self->handle);
}

void buffer_destroy(Buffer *self) { glDeleteBuffers(1, &self->handle); }