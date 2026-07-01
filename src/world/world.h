#pragma once

#include "../gfx/gfx.h"
#include "../util/util.h"
#include "../ecs/ecs.h"

#define MAX_ENTITY 1024

typedef struct World {
    Entity entities[MAX_ENTITY];
    u32 entities_count;
} World;
