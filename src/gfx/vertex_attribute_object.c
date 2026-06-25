#include "vertex_attribute_object.h"

void vertex_attribute_object_bind(VertexAttributeObject *self) { glBindVertexArray(self->handle); }

void vertex_attribute_object_attrib(VertexAttributeObject *self, BufferObject *vbo, GLuint index, GLint size,
                                    GLenum type,
                GLsizei stride,
                size_t offset) {
    vertex_attribute_object_bind(self);
    buffer_object_bind(vbo);

    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *)offset);
    glEnableVertexAttribArray(index);
}

void vertex_attribute_object_init(VertexAttributeObject *self) {
    memset(self, 0, sizeof(VertexAttributeObject));
    glGenVertexArrays(1, &self->handle);
}

void vertex_attribute_object_destroy(VertexAttributeObject *self) { glDeleteVertexArrays(1, &self->handle); }