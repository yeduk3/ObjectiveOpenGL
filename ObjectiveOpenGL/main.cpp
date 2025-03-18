//
//  main.cpp
//  ObjectiveOpenGL
//
//  Created by 이용규 on 3/17/25.
//

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include "framebuffer.hpp"
#include "program.hpp"


#include <thread>
using namespace std::chrono_literals;


Framebuffer fbo;
Program ftestProgram;
Program program;

GLuint vao;
GLuint vbo;

float points[8] = {
    -1.0, -1.0,
    -1.0, 1.0,
    1.0, -1.0,
    1.0, 1.0
};
#include <unistd.h>
int main(int argc, const char * argv[]) {
    // XCode bug: instance duplication occurs when below code removed.
    // IDK the reason why it works but, you have to wait for 1 second. not even 500ms.
    // From: https://developer.apple.com/forums/thread/765445
    std::this_thread::sleep_for(1000ms);
    
    
    // glfw init
    // --------------------
    if(!glfwInit()) {
        std::cout << "GLFW Init Failed" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(640, 480, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // glew init
    // --------------------
    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW Init Failed" << std::endl;
        return -1;
    }
    
    
    // render init
    // ---------------------
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    
    program.loadShader("test.vert", "test.frag");
    program.linkShader();
    
    ftestProgram.loadShader("ftest.vert", "ftest.frag");
    ftestProgram.linkShader();
    
    fbo.init(w, h);
    fbo.attachTexture2D(1, GL_RGBA32F);
    
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_STATIC_DRAW);
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    
    
    while(!glfwWindowShouldClose(window)) {
        // render
        // -------------------
        glUseProgram(ftestProgram.programID);
        fbo.render(window, vao);
        
        glUseProgram(program.programID);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, w, h);
        glClearColor(0, 0, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUniform1i(glGetUniformLocation(program.programID, "tex"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, fbo.textureIDs[0]);
        
        glUniform2fv(glGetUniformLocation(program.programID, "invSize"),1,
                     glm::value_ptr(glm::vec2(1/(float)w, 1/(float)h)));
        
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);
        
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }
    
    glfwTerminate();
    glfwDestroyWindow(window);
    
    return 0;
}
