// Standard includes
#include <stdio.h> // printf()

// Custom includes
#include <window.h>

// Global variables
const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;
const char* const WINDOW_TITLE = "openGL Engine v0.1\0";

int main()
{
  printf("\n--- Engine Started ---\n\n");
  init(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
  // Render loop
  while (isRunning())
  {
    // Process input
    processInput();
    // Swap buffers and poll events
    render();
  }
  cleanUp();
  glfwTerminate();
  printf("\n--- Engine Terminated ---\n\n");

  return 0;
}
