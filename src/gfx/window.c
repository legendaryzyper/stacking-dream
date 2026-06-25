#include "window.h"
#include "../state.h"

#include "vertex_attribute_object.h"
#include "buffer_object.h"

Window window;

static void frame_buffer_size_callback(GLFWwindow *handle, int width, int height) {
    glViewport(0, 0, width, height);

    window.size = (ivec2s){{width, height}};
}

static void init(void) { window.init(); }

static void tick(void) { window.tick(); }

static void update(void) { window.update(); }

static void render(void) { window.render(); }

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

    glfwSetFramebufferSizeCallback(window.handle, frame_buffer_size_callback);

    gladLoadGL();
}

void window_loop(void) {
    init();

    // Vertices coordinates
    GLfloat vertices[] = {
        -0.5f, -0.5f * (float)sqrt(3) / 3, 0.0f, // Lower left corner
        0.5f,  -0.5f * (float)sqrt(3) / 3,    0.0f, // Lower right corner
        0.0f,  0.5f * (float)sqrt(3) * 2 / 3, 0.0f  // Upper corner
    };

    BufferObject *bo = malloc(sizeof(BufferObject));
    VertexAttributeObject *vao = malloc(sizeof(VertexAttributeObject));

    buffer_object_init(bo, GL_ARRAY_BUFFER);
    vertex_attribute_object_init(vao);

    buffer_object_buffer(bo, vertices, sizeof(vertices));

    vertex_attribute_object_attrib(vao, bo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);

    while (!glfwWindowShouldClose(window.handle)) {
        // tick();

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        update();
        render();

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    destroy();
}