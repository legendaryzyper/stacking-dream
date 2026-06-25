#include "vertex_array.h"

void vertex_array_bind(VertexArray *self) { glBindVertexArray(self->handle); }

void vertex_array_attrib(VertexArray *self, Buffer *vbo, GLuint index, GLint size, GLenum type,
                         GLsizei stride, size_t offset) {
    vertex_array_bind(self);
    buffer_bind(vbo);

    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
    glEnableVertexAttribArray(index);
}

void vertex_array_init(VertexArray *self) {
    memset(self, 0, sizeof(VertexArray));
    glGenVertexArrays(1, &self->handle);
}

void vertex_array_destroy(VertexArray *self) { glDeleteVertexArrays(1, &self->handle); }