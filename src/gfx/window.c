#include "window.h"

Window window;

static void frame_buffer_size_callback(GLFWwindow *handle, int width, int height) {
    glViewport(0, 0, width, height);

    window.size = (ivec2s){{width, height}};
}

static void mouse_button_callback(GLFWwindow *handle, int button, int action, int mods) {
    if (button < 0) { return; }

    switch (action) {
    case GLFW_PRESS:
        window.mouse.buttons[button].down = true;
        break;
    case GLFW_RELEASE:
        window.mouse.buttons[button].down = false;
        break;
    default:
        break;
    }
}

static void key_callback(GLFWwindow *handle, int key, int scancode, int action, int mods) {
    if (key < 0) { return; }

    switch (action) {
    case GLFW_PRESS:
        window.keyboard.keys[key].down = true;
        break;
    case GLFW_RELEASE:
        window.keyboard.keys[key].down = false;
        break;
    default:
        break;
    }
}

static void cursor_pos_callback(GLFWwindow *handle, double xpos, double ypos) {
    vec2s pos = {{xpos, ypos}};

    if (window.mouse.not_first) {
        vec2s diff = glms_vec2_sub(pos, window.mouse.position);
        window.mouse.delta = glms_vec2_add(window.mouse.delta, diff);
    } else {
        window.mouse.delta = GLMS_VEC2_ZERO;
        window.mouse.not_first = true;
    }

    window.mouse.delta.x = clamp(window.mouse.delta.x, -100.0f, 100.0f);
    window.mouse.delta.y = clamp(window.mouse.delta.y, -100.0f, 100.0f);

    window.mouse.position = pos;
}

static void button_array_tick(u16 last, Button *buttons) {
    for (u16 idx = 0; idx < last; idx++) {
        buttons[idx].pressed = buttons[idx].down && !buttons[idx].last;
        buttons[idx].last = buttons[idx].down;
    }
}

static void global_init(void) { window.init(); }

static void global_tick(void) {
    window.ticks++;

    button_array_tick(GLFW_MOUSE_BUTTON_LAST, window.mouse.buttons);
    button_array_tick(GLFW_KEY_LAST, window.keyboard.keys);

    window.tick();
}

static void global_update(void) {
    window.update();

    window.mouse.delta = GLMS_VEC2_ZERO;
}

static void global_render(void) {
    window.frames++;

    window.render();
}

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

    window.last_frame = NOW();
    window.last_second = NOW();

    window.size = (ivec2s){{1920, 1080}};
    window.tickrate = 120;
    window.mouse.sensitivity = 2.0f;

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined(__APPLE__) && defined(__MACH__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window.handle = glfwCreateWindow(window.size.x, window.size.y, "stacking dream", NULL, NULL);

    glfwMakeContextCurrent(window.handle);
    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window.handle, frame_buffer_size_callback);
    glfwSetCursorPosCallback(window.handle, cursor_pos_callback);
    glfwSetMouseButtonCallback(window.handle, mouse_button_callback);
    glfwSetKeyCallback(window.handle, key_callback);

    gladLoadGL();

    glViewport(0, 0, window.size.x, window.size.y);
}

void window_loop(void) {
    global_init();

    while (!glfwWindowShouldClose(window.handle)) {
        glfwPollEvents();

        const u64 now = NOW();

        window.frame_delta = now - window.last_frame;
        window.last_frame = now;

        if (now - window.last_second > NS_PER_SECOND) {
            window.fps = window.frames;
            window.tps = window.ticks;
            window.frames = 0;
            window.ticks = 0;
            window.last_second = now;

            printf("FPS: %" PRIu64 " | TPS: %" PRIu64 "\n", window.fps, window.tps);
        }

       /* const u64 NS_PER_TICK = (NS_PER_SECOND / window.tickrate);
        u64 tick_time = window.frame_delta + window.tick_remainder;

        while (tick_time > NS_PER_TICK) {
            global_tick();
            tick_time -= NS_PER_TICK;
        }

        window.tick_remainder = max(tick_time, 0);*/

        global_update();
        global_render();

        glfwSwapBuffers(window.handle);
    }

    global_destroy();
}