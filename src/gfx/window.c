#include "window.h"

Window window;

static void init(void) {
    window.init();
}

static void tick(void) {
    window.tick();
}

static void update(void) {
    window.update();
}

static void render(void) {
    window.render();
}

static void destroy(void) {
    window.destroy();

    glfwDestroyWindow(window.handle);
    glfwTerminate();
}

void window_init(FWindow init, FWindow tick, FWindow update, FWindow render, FWindow destroy) {
    window.init = init;
    window.tick = tick;
    window.update = update;
    window.render = render;
    window.destroy = destroy;

    window.size = (ivec2s){{1920, 1080}};

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window.handle = glfwCreateWindow(window.size.x, window.size.y, "game", NULL, NULL);

    glfwMakeContextCurrent(window.handle);

    gladLoadGL();
}

void window_loop(void) {
    init();
    
    while (!glfwWindowShouldClose(window.handle)) {
        // tick();

        update();
        render();

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    destroy();
}