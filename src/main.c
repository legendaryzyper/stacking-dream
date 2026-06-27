#include "state.h"
#include "gfx/window.h"

State state;

static void init(void) {
    shader_init(&state.shader, "res/shaders/default.vert", "res/shaders/default.frag");
    texture_system_init();
    texture_init(&state.texture, GL_TEXTURE_2D, 0, "res/textures/brick.png");
    shader_uniform_int(&state.shader, "tex", state.texture.slot);

    camera_init(&state.camera);

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    f32 vertices[] = {-0.5f, 0.0f, 0.5f, 0.0f, 0.0f, -0.5f, 0.0f, -0.5f, 5.0f, 0.0f, 0.5f, 0.0f, -0.5f,
                      0.0f,  0.0f, 0.5f, 0.0f, 0.5f, 5.0f,  0.0f, 0.0f,  0.8f, 0.0f, 2.5f, 5.0f};

    u32 indices[] = {0, 1, 2, 0, 2, 3, 0, 1, 4, 1, 2, 4, 2, 3, 4, 3, 0, 4};

    vertex_array_init(&state.vao);
    buffer_init(&state.vbo, GL_ARRAY_BUFFER);
    buffer_init(&state.ebo, GL_ELEMENT_ARRAY_BUFFER);

    vertex_array_bind(&state.vao);

    buffer_buffer_data(&state.vbo, vertices, sizeof(vertices));
    GL_LAYOUT_LOCATION(0, 3, GL_FLOAT, 5 * sizeof(f32), 0);
    GL_LAYOUT_LOCATION(1, 2, GL_FLOAT, 5 * sizeof(f32), 3 * sizeof(f32));

    buffer_buffer_data(&state.ebo, indices, sizeof(indices));

    state.rot = 0.0f;
    state.prevTime = glfwGetTime();
}

static void tick(void) {}

static void update(void) {
    double crntTime = glfwGetTime();
    if (crntTime - state.prevTime >= 1.0f / 60.0f) {
        state.rot += 0.5f;
        state.prevTime = crntTime;
    }

    state.camera.yaw +=
        window.mouse.delta.x * window.mouse.sensitivity * 0.001f;
    state.camera.pitch -=
        window.mouse.delta.y * window.mouse.sensitivity * 0.001f;

    camera_update(&state.camera);
}

static void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_uniform_mat4(&state.shader, "model",
                        glms_rotate(glms_translate(glms_mat4_identity(), (vec3s){{0.0f, -0.5f, -2.0f}}),
                                    glm_rad(state.rot), (vec3s){{0.0f, 1.0f, 0.0f}}));
    shader_uniform_mat4(&state.shader, "view", state.camera.view);
    shader_uniform_mat4(&state.shader, "proj", state.camera.projection);

    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, NULL);
}

static void destroy(void) {
    shader_destroy(&state.shader);
    texture_destroy(&state.texture);
    buffer_destroy(&state.vbo);
    buffer_destroy(&state.ebo);
    vertex_array_destroy(&state.vao);
    camera_destroy(&state.camera);
}

int main(void) {
    window_init(init, tick, update, render, destroy);
    window_loop();

    return 0;
}