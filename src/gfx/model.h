#pragma once

#include "mesh.h"
#include "../ecs/ecs.h"

#include <stdbool.h>
#include <cgltf.h>

// A Model owns one or more Meshes (one per glTF primitive)
typedef struct Model {
    Mesh *meshes;
    u64 mesh_count;
} Model;

// could delete the test function
bool load_glb_model_test(Model *self, const char *file_path);
bool load_glb_model(Model *self, const char *path);
void model_destroy(Model *self);

// this could have a better place
void model_render(Entity *entity);
