#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/window.h"
#include "gfx/shader.h"

typedef struct State {
    Shader shader;
} State;

extern State state;