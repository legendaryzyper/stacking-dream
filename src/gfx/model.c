#include "model.h"
#include "cgltf.h"
#include "mesh.h"
#include "cglm/vec3.h"

#include <stdio.h>

// helper function
static void load_node_data_test(cgltf_node *node, int depth);
static void read_and_walk_node(Model *self, cgltf_node *node);
static void build_mesh_from_primitive(Mesh *out_mesh, const cgltf_primitive *primitive, cgltf_float *world);
static void load_texture_from_primitive(Texture *out_texture, const cgltf_primitive *primitive);

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
        for (cgltf_size i = 0; i < scene->nodes_count; i++) { load_node_data_test(scene->nodes[i], 0); }
    }

    cgltf_free(data);
    return true;
}

static void load_node_data_test(cgltf_node *node, int depth) {
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
            printf("  primitive %zu: type=%d attributes=%zu has_indices=%d has_material=%d\n", i,
                   (int)primitive->type, primitive->attributes_count, (int)(primitive->indices != NULL),
                   (int)(primitive->material != NULL));

            for (cgltf_size j = 0; j < primitive->attributes_count; j++) {
                cgltf_attribute *attrib = &primitive->attributes[j];
                printf("    attr name=%s type=%d index=%d count=%zu data_type=%d component_type=%d\n",
                       attrib->name ? attrib->name : "(null)", (int)attrib->type, (int)attrib->index,
                       attrib->data->count, (int)attrib->data->type, (int)attrib->data->component_type);
            }

            const cgltf_accessor *position = cgltf_find_accessor(primitive, cgltf_attribute_type_position, 0);
            if (position && position->has_max) {
                printf("    POSITION max = [%f, %f, %f]\n", position->max[0], position->max[1],
                       position->max[2]);
            }
            if (position && position->has_min) {
                printf("    POSITION min = [%f, %f, %f]\n", position->min[0], position->min[1],
                       position->min[2]);
            }
            if (primitive->indices) { printf("    index count = %zu\n", primitive->indices->count); }
        }
    }

    for (cgltf_size n = 0; n < node->children_count; n++) {
        load_node_data_test(node->children[n], depth + 1);
    }
}

bool load_glb_model(Model *self, const char *file_path) {
    cgltf_options option = {0};
    cgltf_data *data = NULL;

    if (cgltf_parse_file(&option, file_path, &data) != cgltf_result_success) return false;
    if (cgltf_load_buffers(&option, data, file_path) != cgltf_result_success) {
        cgltf_free(data);
        return false;
    }

    self->meshes = NULL;
    cgltf_scene *scene = data->scene;
    if (!scene && data->scenes_count > 0) scene = &data->scenes[0];
    if (scene) {
        for (cgltf_size i = 0; i < scene->nodes_count; i++) { read_and_walk_node(self, scene->nodes[i]); }
    }

    self->mesh_count = arrlen(self->meshes);

    cgltf_free(data);
    return true;
}

static void read_and_walk_node(Model *self, cgltf_node *node) {
    if (node->mesh) {
        cgltf_float world[16];
        cgltf_node_transform_world(node, world);

        for (cgltf_size i = 0; i < node->mesh->primitives_count; i++) {
            cgltf_primitive *prim = &node->mesh->primitives[i];
            Mesh temp = {0};
            arrput(self->meshes, temp);
            Mesh *mesh = &self->meshes[arrlen(self->meshes) - 1];
            build_mesh_from_primitive(mesh, prim, world);
        }
    }
    for (cgltf_size c = 0; c < node->children_count; c++) read_and_walk_node(self, node->children[c]);
}

static void build_mesh_from_primitive(Mesh *out_mesh, const cgltf_primitive *primitive, cgltf_float *world) {
    const cgltf_accessor *position = cgltf_find_accessor(primitive, cgltf_attribute_type_position, 0);
    const cgltf_accessor *normal = cgltf_find_accessor(primitive, cgltf_attribute_type_normal, 0);
    const cgltf_accessor *texture = cgltf_find_accessor(primitive, cgltf_attribute_type_texcoord, 0);
    const cgltf_accessor *tangent = cgltf_find_accessor(primitive, cgltf_attribute_type_tangent, 0);

    // vertex = position count cause vertex alway have position
    cgltf_size vertex_count = position ? position->count : 0;
    Vertex *vertices = NULL;
    arrsetlen(vertices, vertex_count);

    for (u32 v = 0; v < vertex_count; v++) {
        Vertex temp_vertex = {0};

        // default fall back if model do not have normal or tangent
        temp_vertex.normal.y = 1.0;
        temp_vertex.tangent.x = 1.0;

        // read info and write to temp vertex
        if (position) cgltf_accessor_read_float(position, v, temp_vertex.position.raw, 3);
        if (normal) cgltf_accessor_read_float(normal, v, temp_vertex.normal.raw, 3);
        if (texture) cgltf_accessor_read_float(texture, v, temp_vertex.uv.raw, 2);
        if (tangent) cgltf_accessor_read_float(tangent, v, temp_vertex.tangent.raw, 4);

        // transform math stuff i dont know ¯\(ツ)/¯
        // position
        f32 pos_x = temp_vertex.position.x;
        f32 pos_y = temp_vertex.position.y;
        f32 pos_z = temp_vertex.position.z;

        temp_vertex.position.x = world[0] * pos_x + world[4] * pos_y + world[8] * pos_z + world[12];
        temp_vertex.position.y = world[1] * pos_x + world[5] * pos_y + world[9] * pos_z + world[13];
        temp_vertex.position.z = world[2] * pos_x + world[6] * pos_y + world[10] * pos_z + world[14];

        // normal
        f32 normal_x = temp_vertex.normal.x;
        f32 normal_y = temp_vertex.normal.y;
        f32 normal_z = temp_vertex.normal.z;

        temp_vertex.normal.x = world[0] * normal_x + world[4] * normal_y + world[8] * normal_z;
        temp_vertex.normal.y = world[1] * normal_x + world[5] * normal_y + world[9] * normal_z;
        temp_vertex.normal.z = world[2] * normal_x + world[6] * normal_y + world[10] * normal_z;
        glm_vec3_normalize(temp_vertex.normal.raw);

        // tangent
        f32 tangent_x = temp_vertex.tangent.x;
        f32 tangent_y = temp_vertex.tangent.y;
        f32 tangent_z = temp_vertex.tangent.z;

        temp_vertex.tangent.x = world[0] * tangent_x + world[4] * tangent_y + world[8] * tangent_z;
        temp_vertex.tangent.y = world[1] * tangent_x + world[5] * tangent_y + world[9] * tangent_z;
        temp_vertex.tangent.z = world[2] * tangent_x + world[6] * tangent_y + world[10] * tangent_z;

        f32 tangent_w = temp_vertex.tangent.w;
        glm_vec3_normalize(temp_vertex.tangent.raw);
        temp_vertex.tangent.w = tangent_w;

        vertices[v] = temp_vertex;
    }

    u32 *indices = NULL;
    if (primitive->indices) {
        cgltf_size indicies_count = primitive->indices->count;
        arrsetlen(indices, indicies_count);
        for (u32 i = 0; i < indicies_count; i++)
            indices[i] = (u32)cgltf_accessor_read_index(primitive->indices, i);
    } else {
        arrsetlen(indices, vertex_count);
        for (u32 i = 0; i < vertex_count; i++) indices[i] = (u32)i;
    }

    Texture *tex_obj = malloc(sizeof(Texture));
    load_texture_from_primitive(tex_obj, primitive);

    mesh_init(out_mesh, vertices, indices, tex_obj);
}

static void load_texture_from_primitive(Texture *out_texture, const cgltf_primitive *primitive) {
    memset(out_texture, 0, sizeof(Texture));
    // fallback for texture is full white
    u8 fallback[4] = {255, 255, 255, 255};

    if (primitive->material && primitive->material->has_pbr_metallic_roughness) {
        cgltf_texture_view *bc = &primitive->material->pbr_metallic_roughness.base_color_texture;
        if (bc->texture && bc->texture->image && bc->texture->image->buffer_view) {
            const u8 *bytes = cgltf_buffer_view_data(bc->texture->image->buffer_view);
            cgltf_size size = bc->texture->image->buffer_view->size;
            texture_init_from_memory(out_texture, GL_TEXTURE_2D, 0, bytes, (int)size);
            return;
        }
    }

    texture_init_fall_back(out_texture, GL_TEXTURE_2D, 0, fallback);
    return;
}

void model_destroy(Model *self) {
    for (u64 i = 0; i < self->mesh_count; i++) { mesh_destroy(&self->meshes[i]); }
    if (self->meshes) arrfree(self->meshes);
    self->meshes = NULL;
    self->mesh_count = 0;
}
