#pragma once

#include "gfx/gfx.h"
#include "util/util.h"

#include "gfx/shader.h"
#include "gfx/model.h"
#include "entity/player.h"
#include "world/world.h"

typedef struct State {
    World world;
    Shader shader;
    Model model;
    Player player;
} State;

extern State state;
