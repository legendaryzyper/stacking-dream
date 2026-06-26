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
void texture_init(Texture *self, GLenum type, u32 slot, const char *path);
void texture_destroy(Texture *self);