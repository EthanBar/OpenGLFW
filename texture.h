#ifndef TEXTURE_H
#define TEXTURE_H


class Texture {
public:
    unsigned int ID;
    int width, height, nrChannels;
    GLenum slot;
    Texture(const char* filename, GLenum slot, GLenum format);
    void use();
    static void init();
};


#endif
