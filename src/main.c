#include "state.h"
#include "gfx/window.h"

State state;

static void global_init(void) {
    shader_init(&state.shader, "res/shaders/default.vert", "res/shaders/default.frag");
    texture_init(&state.texture, GL_TEXTURE_2D, 0, "res/textures/pop_cat.png");
    shader_uniform_texture(&state.shader, "tex", &state.texture);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    f32 vertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Lower left corner
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // Upper left corner
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // Upper right corner
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f  // Lower right corner
    };

    u32 indices[] = {
        0, 2, 1, // Upper triangle
        0, 3, 2  // Lower triangle
    };

    buffer_init(&state.vbo, GL_ARRAY_BUFFER);
    buffer_init(&state.ebo, GL_ELEMENT_ARRAY_BUFFER);
    vertex_array_init(&state.vao);

    buffer_buffer_data(&state.vbo, vertices, sizeof(vertices));
    vertex_array_attrib(&state.vao, &state.vbo, 0, 3, GL_FLOAT, 5 * sizeof(f32), 0);   
    vertex_array_attrib(&state.vao, &state.vbo, 1, 2, GL_FLOAT, 5 * sizeof(f32), 3 * sizeof(f32));
    
    buffer_buffer_data(&state.ebo, indices, sizeof(indices));
}

static void global_tick(void) {}

static void global_update(void) {}

static void global_render(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

static void global_destroy(void) {
    shader_destroy(&state.shader);
    texture_destroy(&state.texture);
    buffer_destroy(&state.vbo);
    buffer_destroy(&state.ebo);
    vertex_array_destroy(&state.vao);
}

int main(void) {
    window_init(global_init, global_tick, global_update, global_render, global_destroy);
    window_loop();

    return 0;
}