#ifndef LOWG_WINDOW_H
#define LOWG_WINDOW_H

#include <stdbool.h>

#define MAX_KEYS    1024
#define MAX_BUTTONS   32

typedef struct GLFWwindow GLFWwindow;

typedef struct {
  int width;
  int height;
  char* title;
  GLFWwindow* window;
} lowg_window_t;

bool keys[MAX_KEYS];
bool key_state[MAX_KEYS];
bool key_typed[MAX_KEYS];
bool mouse_buttons[MAX_BUTTONS];
double mousex, mousey; 

lowg_window_t* lowg_window_new(char* title, int width, int height);
int lowg_window_should_close();
void lowg_window_clear(float r, float g, float b);
void lowg_window_update();

void lowg_window_update_keys();

bool lowg_window_is_key_pressed(unsigned int key_code);
bool lowg_window_is_key_down(unsigned int key_code);
bool lowg_window_is_mouse_button_pressed(unsigned int button_code);

void lowg_window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void lowg_window_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void lowg_window_mouse_position_callback(GLFWwindow* window, double xpos, double ypos);
void lowg_window_buffer_size_callback(GLFWwindow* window, int width, int height);

#endif
