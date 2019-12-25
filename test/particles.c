#include "window.h"
#include "sprite.h"
#include "renderer2d.h"
#include "vec3.h"
#include "glfw/glfw3.h"

#include <time.h>

#define WIDTH 720
#define HEIGHT 640

int main()
{
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

      xx = (float) (rand() % WIDTH);

      /* lowg_sprite_t* flake = lowg_sprite_new_image(xx, 0.0f, 20.0f, 20.0f, "/home/void/Downloads/file.png"); */
      lowg_sprite_t* flake = lowg_sprite_new_color(xx, 0.0f, 10.0f, 10.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
      lowg_renderer2d_add(flake);

      flake->dx = dx;
      flake->dy = dy;

      for (int i = 0; i < sprites->len; i++) {
        lowg_sprite_t* flake = g_ptr_array_index(sprites, i);
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

  return 0;
}
