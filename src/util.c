#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glad/glad.h>

char* lowg_read_file(char* path)
{
  if (access(path, F_OK) == -1) {
    printf("File does not exist\n");
    return NULL;
  }

  FILE *fp = fopen(path, "r");
  fseek(fp, 0, SEEK_END);
  size_t size = ftell(fp);
  rewind(fp);

  char* buffer = malloc(size + 1);
  if (!buffer) {
    printf("Failed to allocate file");
    return NULL;
  }

  size_t read = fread(buffer, sizeof(char), size, fp);

  fclose(fp);
  buffer[read] = '\0';
  return buffer;
}

unsigned int lowg_create_shader_program(char * vertex_path, char* fragment_path)
{
  unsigned int vertex_shader = lowg_create_shader("assets/shader.vert", GL_VERTEX_SHADER);
  unsigned int fragment_shader = lowg_create_shader("assets/shader.frag", GL_FRAGMENT_SHADER);
  unsigned int program = lowg_create_program(vertex_shader, fragment_shader);

  return program;
}

unsigned int lowg_create_shader(char* path, unsigned int type)
{
  unsigned int shader = glCreateShader(type);
  const char* source = lowg_read_file(path);

  int status = 0;
  int len;

  glShaderSource(shader, 1, &source , NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

  if (len > 0) {
    char* message = malloc(sizeof(char) * len);
    glGetShaderInfoLog(shader, len, NULL, message);
    printf("%s\n", message);
  }

  return shader;
}

unsigned int lowg_create_program(unsigned int vertex_shader, unsigned int fragment_shader)
{
  unsigned int program = glCreateProgram();
  int status = 0;
  int len;

  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &status);
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
  if (len > 0) {
    char* message = malloc(sizeof(char) * len);
    glGetProgramInfoLog(program, len, NULL, message);
    printf("%s\n", message);
  }

  glDetachShader(program, vertex_shader);
  glDetachShader(program, fragment_shader);

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  return program;
}

void lowg_bind_program(unsigned int program)
{
  glUseProgram(program);
}
