#include "texture.h"
#include <stb_image.h>

void texture_system_init(void) { stbi_set_flip_vertically_on_load(false); }

void texture_bind(Texture *self) {
    glActiveTexture(GL_TEXTURE0 + self->slot);
    glBindTexture(self->type, self->handle);
}

void texture_init_from_memory(Texture *self, GLenum type, u32 slot, const u8 *buffer, int buffer_len) {
    memset(self, 0, sizeof(Texture));
    glGenTextures(1, &self->handle);
    self->type = type;
    self->slot = slot;

    int width, height;
    unsigned char *image =
        stbi_load_from_memory((const stbi_uc *)buffer, buffer_len, &width, &height, NULL, STBI_rgb_alpha);

    self->size = (ivec2s){{width, height}};

    texture_bind(self);

    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(type);

    stbi_image_free(image);
}

void texture_init_fall_back(Texture *self, GLenum type, u32 slot, const u8 rgba[4]) {
    memset(self, 0, sizeof(Texture));
    glGenTextures(1, &self->handle);
    self->type = type;
    self->slot = slot;
    self->size = (ivec2s){{1, 1}};

    texture_bind(self);

    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(type, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
}

void texture_destroy(Texture *self) { glDeleteTextures(1, &self->handle); }
