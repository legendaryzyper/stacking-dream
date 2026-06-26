#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void texture_system_init(void) { stbi_set_flip_vertically_on_load(true); }

void texture_bind(Texture *self) {
    glActiveTexture(GL_TEXTURE0 + self->slot);
    glBindTexture(self->type, self->handle);
}

void texture_init(Texture *self, GLenum type, u32 slot, const char *path) {
    memset(self, 0, sizeof(Texture));
    glGenTextures(1, &self->handle);
    self->type = type;
    self->slot = slot;

    int width, height;
    unsigned char *image = stbi_load(path, &width, &height, NULL, STBI_rgb_alpha);

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

void texture_destroy(Texture* self) { glDeleteTextures(1, &self->handle); }