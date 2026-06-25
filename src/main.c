#include "state.h"

State state;

static void init(void) {
    shader_init(&state.shader, "res/shaders/default.vert", "res/shaders/default.frag");
    return;
}

static void tick(void) {}

static void update(void) {}

static void render(void) {
    shader_bind(&state.shader);
    return;
}

static void destroy(void) {
    shader_destroy(&state.shader);
    return;
}

int main(void) {
    window_init(init, tick, update, render, destroy);
    window_loop();

    return 0;
}
