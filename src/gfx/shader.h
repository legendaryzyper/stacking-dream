#pragma once

#include "gfx.h"
#include "../util/util.h"

typedef struct Shader {
    GLuint handle, vhandle, fhandle;
} Shader;

void shader_bind(Shader *self);
void shader_init(Shader *self, const char *vs_path, const char *fs_path);
void shader_destroy(Shader *self);