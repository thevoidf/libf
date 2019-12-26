#include "window.h"
#include "sprite.h"
#include "renderer2d.h"
#include "vec3.h"
#include "mat4.h"
#include "array.h"
#include <glfw/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 720
#define HEIGHT 640

#define TEST 0

int main()
{
#if TEST == 1
  /* float *m = lowg_mat4_identity(); */
  /* m = lowg_mat4_multiply(m, lowg_mat4_scale(20.0f, 10.0f, 0)); */
  /* m = lowg_mat4_multiply(m, lowg_mat4_translate( */
  /*       2.0f, */
  /*       1.0f, */
  /*       0.0f)); */

  /* for (int i = 0; i < 4*4; i++) { */
  /*   printf("%1.f ", m[i]); */
  /* } */

  /* return 0; */

  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  lowg_sprite_t* sp = lowg_sprite_new_color(200.0f, 200.0f, 200.0f, 200.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
  sp->rotate.z = 1.0f;

  lowg_renderer2d_init(WIDTH, HEIGHT);
  lowg_renderer2d_add(sp);

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
      sp->angle += 0.01f;
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

    float angle = 0.0f;
    while (count >= FPS) {
      angle += 1.0f;

      max = 0.2f, min = -0.2f;
      dx = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
      max = 2.0f, min = 0.5f;
      dy = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
      /* dy += 10.0f; */

      xx = (float) (rand() % WIDTH);

      /* lowg_sprite_t* flake = lowg_sprite_new_image(xx, 0.0f, 20.0f, 20.0f, "/home/void/Downloads/file.png"); */
      lowg_sprite_t* flake = lowg_sprite_new_color(xx, 0.0f, 20.0f, 20.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
      flake->rotate.z = 1.0f;
      lowg_renderer2d_add(flake);

      flake->dx = dx;
      flake->dy = dy;
      flake->rotate.z = 1.0f;
      /* flake->angle += 1.0f; */

      for (int i = 0; i < lowg_array_size(sprites); i++) {
        lowg_sprite_t* flake = lowg_array_get(sprites, i);
        flake->position.x += flake->dx;
        flake->position.y += flake->dy;
        flake->position.y += flake->dy;

        flake->angle += 0.1f;

        if (flake->position.y > HEIGHT) {
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
