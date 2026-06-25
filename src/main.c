#include "state.h"

State state;

static void init(void) {
    shader_init(&state.shader, "res/shaders/default.vert", "res/shaders/default.frag");

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    GLfloat vertices[] = {
        -0.5f,     -0.5f * (float)sqrt(3) / 3,    0.0f, // Lower left corner
        0.5f,      -0.5f * (float)sqrt(3) / 3,    0.0f, // Lower right corner
        0.0f,      0.5f * (float)sqrt(3) * 2 / 3, 0.0f, // Upper corner
        -0.5f / 2, 0.5f * (float)sqrt(3) / 6,     0.0f, // Inner left
        0.5f / 2,  0.5f * (float)sqrt(3) / 6,     0.0f, // Inner right
        0.0f,      -0.5f * (float)sqrt(3) / 3,    0.0f  // Inner down
    };

    GLuint indices[] = {
        0, 3, 5, // Lower left triangle
        3, 2, 4, // Upper triangle
        5, 4, 1  // Lower right triangle
    };

    buffer_init(&state.vbo, GL_ARRAY_BUFFER);
    buffer_init(&state.ebo, GL_ELEMENT_ARRAY_BUFFER);
    vertex_array_init(&state.vao);

    buffer_buffer_data(&state.vbo, vertices, sizeof(vertices));
    vertex_array_attrib(&state.vao, &state.vbo, 0, 3, GL_FLOAT, 3 * sizeof(GLfloat), 0);    
    buffer_buffer_data(&state.ebo, indices, sizeof(indices));
}

static void tick(void) {}

static void update(void) {}

static void render(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    shader_bind(&state.shader);

    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
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