#include "state.h"

State state;

static void init(void) {
    shader_init(&state.shader, "res/shaders/default.vert", "res/shaders/default.frag");

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    GLfloat vertices[] = {
        -0.5f, -0.5f * (float)sqrt(3) / 3,    0.0f, // Lower left corner
        0.5f,  -0.5f * (float)sqrt(3) / 3,    0.0f, // Lower right corner
        0.0f,  0.5f * (float)sqrt(3) * 2 / 3, 0.0f  // Upper corner
    };

    buffer_init(&state.vbo, GL_ARRAY_BUFFER);
    vertex_array_init(&state.vao);

    buffer_buffer_data(&state.vbo, vertices, sizeof(vertices));

    vertex_array_attrib(&state.vao, &state.vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), 0);
}

static void tick(void) {}

static void update(void) {}

static void render(void) {
    shader_bind(&state.shader);
    vertex_array_bind(&state.vao);

    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

static void destroy(void) {
    shader_destroy(&state.shader);

    buffer_destroy(&state.vbo);
    vertex_array_destroy(&state.vao);
}

int main(void) {
    window_init(init, tick, update, render, destroy);
    window_loop();

    return 0;
}