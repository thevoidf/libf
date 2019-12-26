#include "window.h"

#include <stdlib.h>
#include <stdio.h>
#include "glad/glad.h"
#include "glfw/glfw3.h"

lowg_window_t* lowg_window_new(char* title, int width, int height)
{
  if (!glfwInit()) {
    printf("Failed to init glfw");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  lowg_window_t* w = (lowg_window_t*) malloc(sizeof(lowg_window_t));

  w->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!w->window) {
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(w->window);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    printf("Failed to init OpenGL\n");
    return NULL;
  }

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  return w;
}

int lowg_window_should_close(lowg_window_t* w)
{
  return glfwWindowShouldClose(w->window);
}

void lowg_window_clear(float r, float g, float b)
{
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  glClearColor(r, g, b, 1.0f);
}

void lowg_window_update(lowg_window_t* w)
{
  GLenum error = glGetError();
  if (error != GL_NO_ERROR)
    printf("OpenGL Error: %d\n", error);

  glfwSwapBuffers(w->window);
  glfwPollEvents();
}
