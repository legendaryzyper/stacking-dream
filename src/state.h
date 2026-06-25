#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/window.h"
#include "gfx/shader.h"
#include "gfx/vertex_array.h"
#include "gfx/buffer.h"

typedef struct State {
    Shader shader;
    VertexArray vao;
    Buffer vbo, ebo;
} State;

extern State state;