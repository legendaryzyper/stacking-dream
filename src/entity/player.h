#pragma once

#include "../gfx/gfx.h"
#include "../util/util.h"

#include "camera.h"

typedef struct Player {
    Camera camera;
    vec3s position;
    f32 speed;
} Player;

void player_init(Player *self);
void player_input(Player *self);
void player_tick(Player *self);
void player_update(Player *self);
void player_destroy(Player *self);