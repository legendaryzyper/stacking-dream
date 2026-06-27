#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/shader.h"
#include "gfx/vertex_array.h"
#include "gfx/buffer.h"
#include "gfx/texture.h"
#include "entity/camera.h"

typedef struct State {
    Shader shader;
    VertexArray vao;
    Buffer vbo, ebo;
    Texture texture;
    Camera camera;
    f32 rot;
    f64 prevTime;
} State;

extern State state;