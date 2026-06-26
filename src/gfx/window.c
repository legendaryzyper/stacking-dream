#include "window.h"

Window window;

static void frame_buffer_size_callback(GLFWwindow *handle, int width, int height) {
    glViewport(0, 0, width, height);

    window.size = (ivec2s){{width, height}};
}

static void global_init(void) { window.init(); }

static void global_tick(void) { window.tick(); }

static void global_update(void) { window.update(); }

static void global_render(void) { window.render(); }

static void global_destroy(void) {
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
#if defined(__APPLE__) && defined(__MACH__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window.handle = glfwCreateWindow(window.size.x, window.size.y, "stacking dream", NULL, NULL);
    
    glfwMakeContextCurrent(window.handle);

    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window.handle, frame_buffer_size_callback);

    gladLoadGL();

    glViewport(0, 0, window.size.x, window.size.y);
}

void window_loop(void) {
    global_init();

    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();

        // TODO
        // global_tick();

        global_update();
        global_render();

        glfwSwapBuffers(window.handle);
    }

    global_destroy();
}