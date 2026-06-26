#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void texture_bind(Texture* self) { glBindTexture(self->type, self->handle); }

void texture_init(Texture *self, GLenum type, u32 slot, const char *path) {
    memset(self, 0, sizeof(Texture));
    glGenTextures(1, &self->handle);
    self->type = type;
    self->slot = slot;

    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;
    unsigned char *image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);

    self->size = (ivec2s){{width, height}};

    texture_bind(self);

    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(type, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(type);

    stbi_image_free(image);
}

void texture_destroy(Texture* self) { glDeleteTextures(1, &self->handle); }