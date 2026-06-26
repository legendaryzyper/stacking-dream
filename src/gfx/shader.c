#include "shader.h"

static GLuint compile(const char *path, GLenum type) {
    FILE *f;
    char *text;
    long len;

    f = fopen(path, "rb");
    fseek(f, 0, SEEK_END);
    len = ftell(f);
    assert(len > 0);
    fseek(f, 0, SEEK_SET);
    text = calloc(1, len + 1);
    assert(text != NULL);
    text[len] = '\0';
    fread(text, 1, len, f);
    assert(strlen(text) > 0);
    fclose(f);

    GLuint handle = glCreateShader(type);

    glShaderSource(handle, 1, (const GLchar *const *)&text, NULL);
    glCompileShader(handle);

    free(text);

    return handle;
}

void shader_bind(Shader *self) { glUseProgram(self->handle); }

void shader_uniform_int(Shader *self, const char *name, GLuint value) {
    shader_bind(self);

    glUniform1i(glGetUniformLocation(self->handle, (const GLchar *)name), value);
}

void shader_uniform_mat4(Shader *self, const char *name, mat4s mat) {
    glUniformMatrix4fv(glGetUniformLocation(self->handle, (const GLchar *)name), 1, GL_FALSE,
                       (const GLfloat *)&mat.raw);
}

void shader_init(Shader *self, const char *vertex_path, const char *fragment_path) {
    memset(self, 0, sizeof(Shader));
    GLuint vertex_handle = compile(vertex_path, GL_VERTEX_SHADER);
    GLuint fragment_handle = compile(fragment_path, GL_FRAGMENT_SHADER);
    self->handle = glCreateProgram();

    glAttachShader(self->handle, vertex_handle);
    glAttachShader(self->handle, fragment_handle);

    glLinkProgram(self->handle);

    glDeleteShader(vertex_handle);
    glDeleteShader(fragment_handle);
}

void shader_destroy(Shader *self) { glDeleteProgram(self->handle); }