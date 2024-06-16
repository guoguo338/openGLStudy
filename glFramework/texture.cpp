#include "texture.h"
#include <iostream>
#include "wrapper/checkError.h"
#define STB_IMAGE_IMPLEMENTATION
#include "application/stb_image.h"

Texture::Texture(const std::string& path, unsigned int uint) {
    mUnit = uint;

    // stbimage read picture
    int channels;

    // reverse y-axis
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);

    // generate texture and activate unit
    GL_CALL(glGenTextures(1, &mTexture));
    // activate texture unit
    GL_CALL(glActiveTexture(GL_TEXTURE0 + mUnit));
    // bind texture object
    GL_CALL(glBindTexture(GL_TEXTURE_2D, mTexture));
    // transfer texture data
    int width = mWidth, height = mHeight;
    if (data) {
        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data));
        // generate mipmap
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D));
    } else {
        std::cerr << "Failed to load texture" << std::endl;
    }

    // release data
    stbi_image_free(data);

    // Set texture filter pattern
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));

    // Set texture package pattern
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
}

Texture::~Texture() {
    if (mTexture != 0) {
        glDeleteTextures(1, &mTexture);
    }
    mTexture = 0;
}

void Texture::bind() {
    if (mTexture != 0) {
        GL_CALL(glBindTexture(GL_TEXTURE_2D, mTexture));
    }
}