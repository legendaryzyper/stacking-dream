#include "state.h"
#include "gfx/window.h"

State state;

static void init(void) {
    texture_system_init();
    shader_init(&state.shader, "res/shaders/default.vert", "res/shaders/default.frag");
    player_init(&state.player);

    state.player.position = (vec3s){{0.0f, 0.0f, 2.0f}};
    state.player.speed = 2.0f;

    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    f32 vertices_i[] = {-0.5f, 0.0f, 0.5f, 0.0f, 0.0f, -0.5f, 0.0f, -0.5f, 5.0f, 0.0f, 0.5f, 0.0f, -0.5f,
                      0.0f,  0.0f, 0.5f, 0.0f, 0.5f, 5.0f,  0.0f, 0.0f,  0.8f, 0.0f, 2.5f, 5.0f};
    f32 *vertices = NULL;
    arrsetlen(vertices, sizeof(vertices_i) / sizeof(f32));
    memcpy(vertices, vertices_i, sizeof(vertices_i));

    u32 indices_i[] = {0, 1, 2, 0, 2, 3, 1, 0, 4, 2, 1, 4, 3, 2, 4, 0, 3, 4};
    u32 *indices = NULL;
    arrsetlen(indices, sizeof(indices_i) / sizeof(u32));
    memcpy(indices, indices_i, sizeof(indices_i));

    Texture brick;
    texture_init(&brick, GL_TEXTURE_2D, 0, "res/textures/brick.png");

    mesh_init(&state.mesh, vertices, indices, &brick);

    state.rot = 0.0f;
}

static void input(void) { player_input(&state.player); }

static void tick(void) {
    player_tick(&state.player);

    state.rot += 0.5f;
}

static void update(void) { player_update(&state.player); }

static void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_uniform_mat4(&state.shader, "view", state.player.camera.view);
    shader_uniform_mat4(&state.shader, "proj", state.player.camera.projection);

    mesh_render(&state.mesh);
}

static void destroy(void) {
    shader_destroy(&state.shader);
    player_destroy(&state.player);
    mesh_destroy(&state.mesh);
}

int main(void) {
    window_init(init, input, tick, update, render, destroy);
    window_loop();

    return 0;
}