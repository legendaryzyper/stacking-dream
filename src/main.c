#include "state.h"

State state;

BufferObject vbo;
VertexAttributeObject vao;

static void init(void) {
    shader_init(&state.shader, "res/shaders/default.vert", "res/shaders/default.frag");

    // Vertices coordinates
    GLfloat vertices[] = {
        -0.5f, -0.5f * (float)sqrt(3) / 3,    0.0f, // Lower left corner
        0.5f,  -0.5f * (float)sqrt(3) / 3,    0.0f, // Lower right corner
        0.0f,  0.5f * (float)sqrt(3) * 2 / 3, 0.0f  // Upper corner
    };

    buffer_object_init(&vbo, GL_ARRAY_BUFFER);
    vertex_attribute_object_init(&vao);

    buffer_object_buffer(&vbo, vertices, sizeof(vertices));

    vertex_attribute_object_attrib(&vao, &vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
}

static void tick(void) {}

static void update(void) {}

static void render(void) {
    shader_bind(&state.shader);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    return;
}

static void destroy(void) {
    shader_destroy(&state.shader);

    
    buffer_object_destroy(&vbo);
    vertex_attribute_object_destroy(&vao);

    return;
}

int main(void) {
    window_init(init, tick, update, render, destroy);
    window_loop();

    return 0;
}