#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/window.h"
#include "gfx/shader.h"
#include "gfx/vertex_attribute_object.h"
#include "gfx/buffer_object.h"

typedef struct State {
    Shader shader;
} State;

extern State state;