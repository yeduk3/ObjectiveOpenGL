//
//  framebuffer.hpp
//  ObjectiveOpenGL
//
//  Created by 이용규 on 3/17/25.
//

#ifndef framebuffer_hpp
#define framebuffer_hpp

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <stdio.h>

struct TextureFormat {
    /** Specifies the number of color components in the texture.
     */
    GLint internalFormat;
    /** Specifies the format of the pixel data
     
     */
    GLenum format;
    /** Specifies the data type of the pixel data.
     
     */
    GLenum type;
    
    /** Generate texture format data by internalFormat
    
     - Parameters:
        - parameter internalFormat: Split this into format and type value.
     */
    void generate(const GLint &internalFormat);
};

/** Framebuffer managing object.
 */
struct Framebuffer {
    /** Framebuffer object's ID(handle)*/
    GLuint id;
    int width, height;
    
    GLuint textureIDs[];
    
    /** Generate new framebuffer object.
     
     Create a new framebuffer object with given width and height
     
     - Parameters:
         - parameter w: **Width** of the framebuffer
         - parameter h: **Height** of the framebuffer
     */
    Framebuffer init(const int &w, const int &h);
    
    
    
    /** Generate new 2D textures and attach to this framebuffer.
     
     Generated textures are canvas of this framebuffer's draw call.
     
     Used functions:
     
     - [glGenTextures](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml)
     
     - [glTexImage2D](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml)
     
     - Parameters:
     
        - parameter nTexture: Number of the textures will be attached.
     
        - parameter format: Texture's format used when creating texture.
     */
    void attachTexture2D(const int &nTexture, const TextureFormat &format);
    
    /** Generate new 2D textures and attach to this framebuffer.
     
     Generated textures are canvas of this framebuffer's draw call.
     
     Used functions:
     
     - [glGenTextures](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGenTextures.xhtml)
     
     - [glTexImage2D](https://registry.khronos.org/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml)
     
     - Parameters:
     
        - parameter nTexture: Number of the textures will be attached.
     
        - parameter internalFormat: Texture's internalFormat used when create TextureFormat object and call again.
     */
    void attachTexture2D(const int &nTexture, const GLint &internalFormat);
    
    void render(GLFWwindow* window, const GLuint &vao);
    
private:
    /** Bind this framebuffer object.*/
    void bind();
    /** Unbind this framebuffer object.*/
    void unbind();
};

#endif /* framebuffer_hpp */
