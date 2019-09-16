// Standard includes
#include <stdio.h> // printf()
#include <stdlib.h> // exit()

#include <glad/glad.h> // Must be included before glfw
#include <GLFW/glfw3.h>

// Custom includes
#include <window.h>
#include <shader.h>

// Global variables
GLFWwindow* window; // main window
int shaderProgram;
unsigned int VBO, VAO, EBO;

int fpsCounter = 0;
int lastFullSecondTime = 0;

int timeUniformLocation;
int deltaTimeUniformLocation;
int resolutionUniformLocation;
float timeValueStart = 0.0f;
float timeValueDelta = 0.0f;
float timeValueCurrent = 0.0f;

char* vsFileName = "./shaders/basic_vs.glsl\0";
char* fsFileName = "./shaders/basic_fs.glsl\0";

void init(const unsigned int width, const unsigned int height, const char* const title)
{
  // Initialize GLFW
  glfwInit();
  // Configure GLFW
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  printf("GLFW initialized and configured!\n");
  // Create window object
  window = glfwCreateWindow(width, height, title, NULL, NULL);
  // Check to see if window object created successfully
  if(window == NULL)
  {
    printf("Failed to create GLFW window!\n");
    glfwTerminate();
    exit(-1);
  }
  // Makes specified window(context) current on the calling thread.
  glfwMakeContextCurrent(window);
  // Sets the framebuffer resize callback of the specified window.
  // Called when the framebuffer of the specified window is resized.
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // Initialize GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD!\n");
    exit(-1);
  }
  printf("GLAD initialized!\n");
  shaderProgram = shader(vsFileName, fsFileName);
  timeUniformLocation = glGetUniformLocation(shaderProgram, "iTime");
  deltaTimeUniformLocation = glGetUniformLocation(shaderProgram, "iTimeDelta");
  resolutionUniformLocation = glGetUniformLocation(shaderProgram, "iResolution");
  glUseProgram(shaderProgram);
  glUniform2f(resolutionUniformLocation, (float)width, (float)height);

  timeValueStart = glfwGetTime();
  rectangle();
  //triangle();
}

int isRunning()
{
  return !glfwWindowShouldClose(window);
}

void processInput()
{
  // Returns the last state reported for the specified key to the specified window
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    // Sets the value of the close flag of the specified window
    glfwSetWindowShouldClose(window, 1);
  }
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
  {
    printf("Shader refreshed!\n");
    glDeleteProgram(shaderProgram);
    shaderProgram = shader(vsFileName, fsFileName);
    timeUniformLocation = glGetUniformLocation(shaderProgram, "iTime");
    deltaTimeUniformLocation = glGetUniformLocation(shaderProgram, "iTimeDelta");
    resolutionUniformLocation = glGetUniformLocation(shaderProgram, "iResolution");
    glUseProgram(shaderProgram);
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);
    glUniform2f(resolutionUniformLocation, (float)width, (float)height);
    timeValueStart = glfwGetTime();
  }
}

void render()
{
  fpsCounter = fpsCounter + 1;
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  timeValueCurrent = glfwGetTime();
  timeValueDelta = timeValueCurrent - timeValueStart;
  if((int)timeValueCurrent > lastFullSecondTime)
  {
    //printf("timeValueStart: %f\n", timeValueStart);
    lastFullSecondTime = (int)timeValueCurrent;
    //printf("###### FPS %i ######\n", fpsCounter);
    //printf("timeValueCurrent: %f\n", timeValueCurrent);
    fpsCounter = 0;
  }
  timeValueStart = timeValueCurrent;

  glUniform1f(timeUniformLocation, timeValueCurrent);
  glUniform1f(deltaTimeUniformLocation, timeValueDelta);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  //glDrawArrays(GL_TRIANGLES, 0, 3);

  // Swaps the front and back buffers of the specified window
  glfwSwapBuffers(window);
  // Processes only those events that are already in the event queue
  glfwPollEvents();
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glUniform2f(resolutionUniformLocation, (float)width, (float)height);
  glViewport(0, 0, width, height);
}

void triangle()
{
  float vertices[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
  };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void rectangle()
{
  float vertices[] = {
    -1.0f, -1.0f, 0.0f, /* Bottom Left */
     1.0f, -1.0f, 0.0f, /* Bottom Right */
     1.0f,  1.0f, 0.0f, /* Top Right */
    -1.0f,  1.0f, 0.0f  /* Top Left */
  };
  unsigned int indices[] = {
    0, 1, 2,
    0, 2, 3
  };
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  // Bind vertex array object first
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void cleanUp()
{
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
}
