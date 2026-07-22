#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct Texture {
    GLuint handle;
    GLenum type;
    u32 slot;
    ivec2s size;
} Texture;

void texture_bind(Texture *self);
void texture_init_fall_back(Texture *self, GLenum type, u32 slot, const u8 rgba[4]);
void texture_init_from_memory(Texture *self, GLenum type, u32 slot, const u8 *buffer, int len);
// TODO: texture init for when wanting to put a picture in
void texture_destroy(Texture *self);
