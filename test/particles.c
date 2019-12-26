#include "window.h"
#include "sprite.h"
#include "renderer2d.h"
#include "vec3.h"
#include "array.h"
#include "glfw/glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 720
#define HEIGHT 640

#define TEST 0

int main()
{
#if TEST == 1
  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  lowg_sprite_t* sp = lowg_sprite_new_color(1.0f, 0.0f, 10.0f, 10.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
  lowg_sprite_t* sp2 = lowg_sprite_new_color(20.0f, 20.0f, 10.0f, 10.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
  lowg_array_t* array = lowg_array_new();
  lowg_array_add(array, sp);
  lowg_array_add(array, sp2);

  lowg_renderer2d_init(WIDTH, HEIGHT);

  for (int i = 0; i < array->size; i++) {
    lowg_sprite_t* sp = array->array[i];
    lowg_sprite_print(sp);
    lowg_renderer2d_add(sp);
  }

  double prev = glfwGetTime();
  double FPS = 1.0 / 60;
  double count = 0.0;
  while (!lowg_window_should_close(w)) {
    lowg_window_clear(0.4f, 0.1f, 0.7f);

    double now = glfwGetTime();
    double delta = now - prev;
    prev = now;
    count += delta;

    while (count >= FPS) {
      /* sp->position->x += 1.0f; */
      /* sp->position->y += 1.0f; */
      count -= FPS;
    }

    lowg_render2d();

    lowg_window_update(w);
  }
#else
  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  lowg_renderer2d_init(WIDTH, HEIGHT);

  srand(time(NULL));

  float max, min, xx, dx, dy;
  double prev = glfwGetTime();
  double FPS = 1.0 / 60;
  double count = 0.0;
  while (!lowg_window_should_close(w)) {
    lowg_window_clear(0.4f, 0.1f, 0.7f);

    double now = glfwGetTime();
    double delta = now - prev;
    prev = now;
    count += delta;

    while (count >= FPS) {
      max = 0.2f, min = -0.2f;
      dx = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
      max = 2.0f, min = 0.5f;
      dy = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
      /* dy += 10.0f; */

      xx = (float) (rand() % WIDTH);

      /* lowg_sprite_t* flake = lowg_sprite_new_image(xx, 0.0f, 20.0f, 20.0f, "/home/void/Downloads/file.png"); */
      lowg_sprite_t* flake = lowg_sprite_new_color(xx, 0.0f, 10.0f, 10.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
      lowg_renderer2d_add(flake);

      flake->dx = dx;
      flake->dy = dy;

      for (int i = 0; i < lowg_array_size(sprites); i++) {
        lowg_sprite_t* flake = lowg_array_get(sprites, i);
        flake->position->x += flake->dx;
        flake->position->y += flake->dy;

        if (flake->position->y > HEIGHT) {
          lowg_render2d_remove(i);
        }
      }

      count -= FPS;
    }

    lowg_render2d();

    lowg_window_update(w);
  }

  lowg_array_free(sprites);
#endif
  return 0;
}
