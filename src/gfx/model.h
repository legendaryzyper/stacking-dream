#pragma once

#include <stdbool.h>

#include <cgltf.h>

#include "mesh.h"

typedef struct Vertex {
    float position[3];
    float normal[3];
    float uv[2];
    float tangent[4];
} Vertex;

// A Model owns one or more Meshes (one per glTF primitive)
typedef struct Model {
    Mesh *meshes;
    u64 mesh_count;
} Model;

bool load_glb_model_test(Model *self, const char *file_path);
bool load_glb_model(Model *self, const char *path);

// helper
void load_node_data_test(cgltf_node *node, int depth);
