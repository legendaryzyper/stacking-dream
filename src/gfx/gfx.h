#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define GL_LAYOUT_LOCATION(index, size, type, stride, offset)                                                  \
    ({                                                                                                       \
        glVertexAttribPointer((index), (size), (type), GL_FALSE, (stride), (void *)(offset));                \
        glEnableVertexAttribArray((index));                                                                  \
    })