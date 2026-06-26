#pragma once

#include "gfx.h"
#include "../util/util.h"

#include "texture.h"

typedef struct Shader {
    GLuint handle;
} Shader;

void shader_bind(Shader *self);
void shader_uniform_texture(Shader *self, const char *name, Texture *texture);
void shader_init(Shader *self, const char *vertex_path, const char *fragment_path);
void shader_destroy(Shader *self);