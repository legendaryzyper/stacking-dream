#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/shader.h"
#include "gfx/mesh.h"
#include "entity/player.h"
#include "world/world.h"

typedef struct State {
    World world;
    Shader shader;
    Mesh mesh;
    Player player;
} State;

extern State state;
