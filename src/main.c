#include "gfx/window.h"
#include "state.h"

static void init(void) {}

static void tick(void) {}

static void update(void) {}

static void render(void) {}

static void destroy(void) {}

int main(void) {
    window_init(init, tick, update, render, destroy);
    window_loop();

    return 0;
}
