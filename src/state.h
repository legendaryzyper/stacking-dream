#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/shader.h"
#include "gfx/vertex_array.h"
#include "gfx/buffer.h"
#include "gfx/texture.h"

typedef struct State {
    Shader shader;
    VertexArray vao;
    Buffer vbo, ebo;
    Texture texture;
} State;

extern State state;