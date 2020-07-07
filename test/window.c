#include "window.h"
#include "renderer2d.h"
#include "sprite.h"

#include <stdio.h>
#ifdef __APPLE__
#include <glfw/mac/glfw3.h>
#elif __linux__
#include <glfw/linux/glfw3.h>
#endif

#define WIDTH 640 * 2
#define HEIGHT 420 * 2

int main()
{
  lowg_window_t* w = lowg_window_new("lowg Window", WIDTH, HEIGHT);
  lowg_sprite_t* cursor = lowg_sprite_new_color(0.0f, 0.0f, 100.0f, 100.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
  lowg_sprite_t* sprite = lowg_sprite_new_color(0.0f, 0.0f, 100.0f, 100.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
  lowg_sprite_t* block = lowg_sprite_new_color(WIDTH/2.0f, 0.0f, 100.0f, 100.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });

  lowg_renderer2d_init(WIDTH, HEIGHT);
  lowg_renderer2d_add(cursor);
  lowg_renderer2d_add(sprite);
  lowg_renderer2d_add(block);

  while (!lowg_window_should_close(w)) {
    lowg_window_clear(0.4f, 0.1f, 0.7f);

    cursor->position.x = mousex;
    cursor->position.y = mousey;
    cursor->rotate.z = 1.0f;
    cursor->angle += 0.01f;

    if (lowg_window_is_key_pressed(GLFW_KEY_A))
      sprite->position.x -= 1.0f;
    if (lowg_window_is_key_pressed(GLFW_KEY_W))
      sprite->position.y -= 1.0f;
    if (lowg_window_is_key_pressed(GLFW_KEY_S))
      sprite->position.y += 1.0f;
    if (lowg_window_is_key_pressed(GLFW_KEY_D))
      sprite->position.x += 1.0f;

    if (lowg_window_is_key_down(GLFW_KEY_SPACE))
      block->position.y += 10.0f;

    if (lowg_window_is_mouse_button_pressed(GLFW_MOUSE_BUTTON_1)) {
      sprite->position.x = mousex;
      sprite->position.y = mousey;
    }

    lowg_render2d();

    lowg_window_update(w);
  }

  return 0;
}
