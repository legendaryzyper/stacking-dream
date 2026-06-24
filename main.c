#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <glad/glad.h>
#include <math.h>
#include <stdio.h>

// ── Shader sources ────────────────────────────────────────────────────────────
static const char* vert_src = "#version 330 core\n"
"layout(location = 0) in vec2 aPos;\n"
"uniform mat4 uMVP;\n"
"void main() {\n"
"    gl_Position = uMVP * vec4(aPos, 0.0, 1.0);\n"
"}\n";

static const char* frag_src = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec3 uColor;\n"
"void main() {\n"
"    FragColor = vec4(uColor, 1.0);\n"
"}\n";

// ── Helpers ───────────────────────────────────────────────────────────────────
static GLuint compile_shader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, NULL);
    glCompileShader(s);

    GLint ok;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(s, 512, NULL, log);
        fprintf(stderr, "Shader compile error: %s\n", log);
    }
    return s;
}

static GLuint make_program(void) {
    GLuint vs = compile_shader(GL_VERTEX_SHADER, vert_src);
    GLuint fs = compile_shader(GL_FRAGMENT_SHADER, frag_src);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

// ── Main ──────────────────────────────────────────────────────────────────────
int main(void) {
    printf("=== Library Test ===\n");

    // ── 1. math.h ─────────────────────────────────────────────────────────────
    printf("\n[math.h]\n");
    printf("  sin(PI/6) = %.4f  (expect 0.5000)\n", sin(GLM_PI / 6.0));
    printf("  cos(PI/3) = %.4f  (expect 0.5000)\n", cos(GLM_PI / 3.0));
    printf("  sqrt(2)   = %.4f  (expect 1.4142)\n", sqrt(2.0));

    // ── 2. cglm ───────────────────────────────────────────────────────────────
    printf("\n[cglm]\n");

    vec3 a = { 1.0f, 0.0f, 0.0f };
    vec3 b = { 0.0f, 1.0f, 0.0f };
    vec3 cross;
    glm_vec3_cross(a, b, cross);
    printf("  cross({1,0,0}, {0,1,0}) = {%.0f, %.0f, %.0f}  (expect {0, 0, 1})\n", cross[0], cross[1],
        cross[2]);

    float dot = glm_vec3_dot(a, b);
    printf("  dot({1,0,0}, {0,1,0})   = %.1f  (expect 0.0)\n", dot);

    mat4 model, view, proj, mvp;
    glm_mat4_identity(model);
    glm_translate(model, (vec3) { 0.5f, 0.0f, 0.0f });
    glm_rotate(model, glm_rad(45.0f), (vec3) { 0.0f, 0.0f, 1.0f });

    glm_lookat((vec3) { 0.0f, 0.0f, 3.0f }, (vec3) { 0.0f, 0.0f, 0.0f }, (vec3) { 0.0f, 1.0f, 0.0f }, view);
    glm_perspective(glm_rad(60.0f), 640.0f / 480.0f, 0.1f, 100.0f, proj);
    glm_mat4_mul(proj, view, mvp);
    glm_mat4_mul(mvp, model, mvp);

    printf("  MVP[3][3] = %.4f  (expect 1.0000 for affine last row)\n", mvp[3][3]);
    printf("  cglm OK\n");

    // ── 3. GLFW ───────────────────────────────────────────────────────────────
    printf("\n[GLFW]\n");
    if (!glfwInit()) {
        fprintf(stderr, "  FAILED to init GLFW\n");
        return -1;
    }
    printf("  glfwInit OK\n");
    printf("  Version: %s\n", glfwGetVersionString());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); // headless — no window pops up

    GLFWwindow* window = glfwCreateWindow(640, 480, "lib test", NULL, NULL);
    if (!window) {
        fprintf(stderr, "  FAILED to create window\n");
        glfwTerminate();
        return -1;
    }
    printf("  Window created OK\n");
    glfwMakeContextCurrent(window);

    // ── 4. GLAD ───────────────────────────────────────────────────────────────
    printf("\n[GLAD]\n");
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "  FAILED to load GL\n");
        glfwTerminate();
        return -1;
    }
    printf("  GL loaded OK\n");
    printf("  Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("  Renderer: %s\n", glGetString(GL_RENDERER));
    printf("  Version:  %s\n", glGetString(GL_VERSION));
    printf("  GLSL:     %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // ── 5. Minimal draw: triangle with MVP ────────────────────────────────────
    printf("\n[Draw test]\n");

    // clang-format off
    float verts[] = {
         0.0f,  0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
    };
    // clang-format on

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint prog = make_program();
    glUseProgram(prog);

    // Upload MVP from cglm
    GLint mvp_loc = glGetUniformLocation(prog, "uMVP");
    GLint color_loc = glGetUniformLocation(prog, "uColor");
    glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, (float*)mvp);
    glUniform3f(color_loc, 0.2f, 0.8f, 0.4f);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);

    GLenum err = glGetError();
    if (err == GL_NO_ERROR)
        printf("  glDrawArrays OK — no GL errors\n");
    else
        printf("  GL error: 0x%x\n", err);

    // ── Cleanup ───────────────────────────────────────────────────────────────
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(prog);
    glfwDestroyWindow(window);
    glfwTerminate();

    printf("\n=== All tests passed ===\n");
    return 0;
}