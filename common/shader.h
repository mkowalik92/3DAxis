#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>

char* readfile(char* fileName);
int compileShader(GLenum shaderType, char* shaderSourceFilename);
int createShaderProgram(int vertexShader, int fragmentShader);
int shader(char* vsFileName, char* fsFileName);

/* Read text file into char* buffer and returns the buffer.
   Must free the returned char* buffer                       */
char* readfile(char* fileName)
{
  // File pointer
  FILE *fp;
  // File length in bytes
  int lenBytes = 0;
  // File contents
  char* fileContentsBuffer = NULL;
  // Open file
  fp = fopen(fileName, "r");
  // Check to see if file opened successfully
  // If file read successfully, read it into a
  // char* buffer and return the buffer
  if (fp == NULL)
  {
    printf("Error opening file : [ %s ]\n", fileName);
  }
  else
  {
    // Go to end of file
    fseek(fp, 0, SEEK_END);
    // How many bytes did we pass?
    lenBytes = ftell(fp);
    // Point file pointer back at the beginning of the file
    rewind(fp);
    // Set file buffer length ( + 1 for \0 )
    fileContentsBuffer = malloc((lenBytes + 1) * sizeof(*fileContentsBuffer));
    // Read file into buffer
    fread(fileContentsBuffer, lenBytes, 1, fp);
    // Close file
    fclose(fp);
    // Null terminate the string
    fileContentsBuffer[lenBytes] = '\0';
    // Return file content
    return fileContentsBuffer;
  }
}

int compileShader(GLenum shaderType, char* shaderSourceFilename)
{
  // Takes in GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
  // Returns int -1 and prints error log if shader compilation fails
  // or returns non-zero reference to the compiled shader
  // Create shader object
  int shader = glCreateShader(shaderType);
  // Get shader source from file
  const char* shaderSource = readfile(shaderSourceFilename);
  // Attach shader source to shader
  glShaderSource(shader, 1, &shaderSource, NULL);
  // Compile shader
  glCompileShader(shader);
  // Free shaderSource buffer
  free((char*)shaderSource);
  // Check if compilation successful
  // int that holds whether action was successful
  int success;
  // Create char* for compilation failure information log
  char infoLog[512];
  // Check if compiled
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  // If compilation not successfull print error info log and return -1
  if (!success)
  {
    // Retreive shader compilation status log and store in infoLog[512]
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("\nFailed to compile: [ %s ]\n", shaderSourceFilename);
    printf("Error log:\n%s\n\n", infoLog);
    return -1;
  }
  // Else compilation is successful print that it was and return
  // shader reference number
  else
  {
    printf("[ %s ] compiled successfully\n", shaderSourceFilename);
    return shader;
  }
}

int createShaderProgram(int vertexShader, int fragmentShader)
{
  // Takes in integer references to pre-compiled vertex and
  // fragment shaders and returns a non-zero integer reference to
  // complete linked shader program. Returns non-zero if successful
  // Create shader program
  int shaderProgram = glCreateProgram(); // returns non-zero if successful
  // Attach vertex shader
  glAttachShader(shaderProgram, vertexShader);
  // Attach fragment shader
  glAttachShader(shaderProgram, fragmentShader);
  // Link shader program object
  glLinkProgram(shaderProgram);
  // Check if linking was successful
  // int that holds whether action was successful
  int success;
  // Create char* for shader program linking failure information log
  char infoLog[512];
  // Check if linked
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  // If linking failed, print linking information log
  if (!success)
  {
    // Retreive shader program linking error info log
    glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("\nFailed to link shader program\n");
    printf("Error log:\n%s\n\n", infoLog);
    // Delete shaders after linking, unneeded now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return -1;
  }
  // Else linking is successful print that it was and return
  // shader program reference number
  else
  {
    printf("Shaders linked successfully\n");
    // Delete shaders after linking, unneeded now
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
  }
}

int shader(char* vsFileName, char* fsFileName)
{
  // Creates a shader program from the vertex and fragment
  // shader source code files provided
  // Create/Compile vertex shader from vertex shader source file
  int vertexShader = compileShader(GL_VERTEX_SHADER, vsFileName);
  // Create/Compile fragment shader from fragment shader source file
  int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fsFileName);
  // Create/Link vertex and fragment shader to shader program
  int shaderProgram = createShaderProgram(vertexShader, fragmentShader);
  // Return the ready to use shader program integer reference
  return shaderProgram;
}

#endif
