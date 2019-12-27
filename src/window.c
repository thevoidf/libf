#include "window.h"

#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

lowg_window_t* lowg_window_new(char* title, int width, int height)
{
  int i;
  for (i = 0; i < MAX_KEYS; i++) {
    keys[i] = false;
    key_state[i] = false;
    key_typed[i] = false;
  }
  for (i = 0; i < MAX_BUTTONS; i++) {
    mouse_buttons[i] = false;
  }

  if (!glfwInit()) {
    printf("Failed to init glfw");
    return NULL;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  lowg_window_t* w = malloc(sizeof(lowg_window_t));

  w->window = glfwCreateWindow(width, height, title, NULL, NULL);
  if (!w->window) {
    glfwTerminate();
    return NULL;
  }

  glfwMakeContextCurrent(w->window);

  glfwSetKeyCallback(w->window, lowg_window_key_callback);
  glfwSetCursorPosCallback(w->window, lowg_window_mouse_position_callback);
  glfwSetMouseButtonCallback(w->window, lowg_window_mouse_button_callback);
  glfwSetFramebufferSizeCallback(w->window, lowg_window_buffer_size_callback);

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
  // BETTER HANDLEING FFS
  /* GLenum error = glGetError(); */
  /* if (error != GL_NO_ERROR) */
  /*   printf("OpenGL Error: %d\n", error); */

  glfwSwapBuffers(w->window);
  glfwPollEvents();
  lowg_window_update_keys();
}

void lowg_window_update_keys()
{
  int i;
  for (i = 0; i < MAX_KEYS; i++)
    key_typed[i] = keys[i] && !key_state[i];
  for (i = 0; i < MAX_KEYS; i++)
    key_state[i] = keys[i];
}

bool lowg_window_is_key_pressed(unsigned int key_code)
{
  if (key_code > MAX_KEYS)
    return false;
  return keys[key_code];
}

bool lowg_window_is_key_down(unsigned int key_code)
{
  if (key_code > MAX_KEYS)
    return false;
  return key_typed[key_code];
}

bool lowg_window_is_mouse_button_pressed(unsigned int button_code)
{
  if (button_code > MAX_BUTTONS)
    return false;
  return mouse_buttons[button_code];
}

void lowg_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  keys[key] = action != GLFW_RELEASE;
}

void lowg_window_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  mouse_buttons[button] = action != GLFW_RELEASE;
}

void lowg_window_mouse_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  mousex = xpos;
  mousey = ypos;
}

void lowg_window_buffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
