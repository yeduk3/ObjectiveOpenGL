//
//  framebuffer.cpp
//  ObjectiveOpenGL
//
//  Created by 이용규 on 3/17/25.
//

#include "framebuffer.hpp"

#include <iostream>

void TextureFormat::generate(const GLint &internalFormat) {
    this->internalFormat = internalFormat;
    if (internalFormat == GL_RGBA32F) {
        this->format = GL_RGBA;
        this->type = GL_FLOAT;
    }
}

Framebuffer Framebuffer::init(const int &w, const int &h) {
    this->width = w;
    this->height = h;
    
    glGenFramebuffers(1, &(this->id));
//    std::cout << "Framebuffer Created: " << this->id << std::endl;
    
    return *this;
}

void Framebuffer::attachTexture2D(const int &nTexture, const TextureFormat &format) {
    this->bind();
    glGenTextures(nTexture, this->textureIDs);
    for (int i = 0; i < nTexture; i++) {
        glBindTexture(GL_TEXTURE_2D, this->textureIDs[i]);
        glTexImage2D(GL_TEXTURE_2D,
                     0,
                     format.internalFormat,
                     this->width,
                     this->height,
                     0,
                     format.format,
                     format.type,
                     0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER,
                               GL_COLOR_ATTACHMENT0 + i,
                               GL_TEXTURE_2D,
                               this->textureIDs[i],
                               0);

        glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
    }
    
    this->unbind();
}

void Framebuffer::attachTexture2D(const int &nTexture, const GLint &internalFormat) {
    this->bind();
    TextureFormat tf;
    tf.generate(internalFormat);
    
    this->attachTexture2D(nTexture, tf);
    
    this->unbind();
}

void Framebuffer::render(GLFWwindow* window, const GLuint &vao) {
    this->bind();
    
    glViewport(0, 0, this->width, this->height);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vao);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
    
    this->unbind();
}


void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->id);
//    std::cout << "Framebuffer Bounded: " << this->id << std::endl;
}
void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    std::cout << "Framebuffer Bounded: " << this->id << std::endl;
}
