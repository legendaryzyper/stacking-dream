#include "vertex_array.h"

void vertex_array_bind(VertexArray *self) { glBindVertexArray(self->handle); }

void vertex_array_init(VertexArray *self) {
    memset(self, 0, sizeof(VertexArray));
    glGenVertexArrays(1, &self->handle);
}

void vertex_array_destroy(VertexArray *self) { glDeleteVertexArrays(1, &self->handle); }