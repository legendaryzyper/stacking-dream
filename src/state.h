#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/shader.h"
#include "world/mesh.h"
#include "entity/player.h"

typedef struct State {
    Shader shader;
    Mesh mesh;
    Player player;
    f32 rot;
} State;

extern State state;