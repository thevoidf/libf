#ifndef LOWG_WINDOW_H
#define LOWG_WINDOW_H

typedef struct GLFWwindow GLFWwindow;

typedef struct {
  int width;
  int height;
  char* title;
  GLFWwindow* window;
} lowg_window_t;

lowg_window_t* lowg_window_new(char* title, int width, int height);
int lowg_window_should_close();
void lowg_window_clear(float r, float g, float b);
void lowg_window_update();

#endif
