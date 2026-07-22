#include "ecs/ecs.h"
#include "state.h"
#include "gfx/window.h"

#include "gfx/model.h"
#include "util/types.h"

State state;

static void init(void) {
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

    load_glb_model(&state.model, "res/models/Duck.glb");

    Entity *e = ecs_spawn_entity(&state.world);
    e->mask = COMPONENT_TRANSFORM | COMPONENT_MESH;
    e->transform.position = (vec3s){{-0.4f, 0.52f, 0}};
    e->transform.scale = (vec3s){{1, 1, 1}};
    e->transform.rotation = (vec3s){{20, 0, 40}};
    e->model = &state.model;
}

static void input(void) { player_input(&state.player); }

static void tick(void) {
    player_tick(&state.player);

    ecs_tick(&state.world);
}

static void update(void) { player_update(&state.player); }

static void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader_uniform_mat4(&state.shader, "view", state.player.camera.view);
    shader_uniform_mat4(&state.shader, "proj", state.player.camera.projection);

    ecs_render(&state.world);
}

static void destroy(void) {
    shader_destroy(&state.shader);
    player_destroy(&state.player);
    model_destroy(&state.model);
}

int main(void) {
    window_init(init, input, tick, update, render, destroy);
    window_loop();

    return 0;
}
