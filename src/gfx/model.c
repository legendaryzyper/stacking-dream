#include "model.h"

#include <stdio.h>

bool load_glb_model_test(Model *self, const char *file_path) {
    (void)self; // unused for now; Step 2 will fill self->meshes

    cgltf_options option = {0};
    cgltf_data *data = NULL;

    cgltf_result parse_result = cgltf_parse_file(&option, file_path, &data);
    if (parse_result != cgltf_result_success) return false;

    cgltf_result load_buffer_result = cgltf_load_buffers(&option, data, file_path);
    if (load_buffer_result != cgltf_result_success) {
        cgltf_free(data);
        return false;
    }

    printf("asset version : %s\n", data->asset.version ? data->asset.version : "(null)");
    printf("asset generator : %s\n", data->asset.generator ? data->asset.generator : "(null)");
    printf("accessors count : %zu\n", data->accessors_count);
    printf("meshes count : %zu\n", data->meshes_count);
    printf("materials count : %zu\n", data->materials_count);
    printf("scenes count : %zu\n", data->scenes_count);
    printf("nodes count : %zu\n", data->nodes_count);

    cgltf_scene *scene = data->scene;
    if (!scene && data->scenes_count > 0) scene = &data->scenes[0];

    if (scene) {
        for (cgltf_size i = 0; i < scene->nodes_count; i++) {
            load_node_data_test(scene->nodes[i], 0);
        }
    }

    cgltf_free(data);
    return true;
}

bool load_glb_model(Model *self, const char *file_path) {
    // TODO(Step 2): parse, walk nodes (flatten transforms via cgltf_node_transform_world),
    // build one Mesh per primitive (read POSITION/NORMAL/TEXCOORD_0/TANGENT via
    // cgltf_accessor_read_float), populate self->meshes / self->mesh_count.
    (void)self;
    (void)file_path;
    return false;
}

void load_node_data_test(cgltf_node *node, int depth) {
    printf("--- node depth %d ---\n", depth);
    printf("has matrix : %d\n", (int)node->has_matrix);
    printf("has translation : %d\n", (int)node->has_translation);
    printf("has rotation : %d\n", (int)node->has_rotation);
    printf("has scale : %d\n", (int)node->has_scale);

    if (node->mesh) {
        printf("mesh name : %s\n", node->mesh->name ? node->mesh->name : "(null)");
        printf("primitive count : %zu\n", node->mesh->primitives_count);

        for (cgltf_size i = 0; i < node->mesh->primitives_count; i++) {
            cgltf_primitive *primitive = &node->mesh->primitives[i];
            printf("  primitive %zu: type=%d attributes=%zu has_indices=%d has_material=%d\n",
                   i, (int)primitive->type, primitive->attributes_count,
                   (int)(primitive->indices != NULL), (int)(primitive->material != NULL));

            for (cgltf_size j = 0; j < primitive->attributes_count; j++) {
                cgltf_attribute *attrib = &primitive->attributes[j];
                printf("    attr name=%s type=%d index=%d count=%zu data_type=%d component_type=%d\n",
                       attrib->name ? attrib->name : "(null)", (int)attrib->type, (int)attrib->index,
                       attrib->data->count, (int)attrib->data->type, (int)attrib->data->component_type);
            }

            const cgltf_accessor *position =
                cgltf_find_accessor(primitive, cgltf_attribute_type_position, 0);
            if (position && position->has_max) {
                printf("    POSITION max = [%f, %f, %f]\n",
                       position->max[0], position->max[1], position->max[2]);
            }
            if (position && position->has_min) {
                printf("    POSITION min = [%f, %f, %f]\n",
                       position->min[0], position->min[1], position->min[2]);
            }
            if (primitive->indices) {
                printf("    index count = %zu\n", primitive->indices->count);
            }
        }
    }

    for (cgltf_size n = 0; n < node->children_count; n++) {
        load_node_data_test(node->children[n], depth + 1);
    }
}
