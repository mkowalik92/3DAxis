#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h> // Must be included before glfw
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void init(const unsigned int width, const unsigned int height, const char* const title);
int isRunning();
void processInput();
void render();

void triangle();
void rectangle();
void cleanUp();

#endif
