#include "window.h"
#include "sprite.h"
#include "renderer2d.h"
#include "vec3.h"
#include <glad/glad.h>

#include <time.h>

#define WIDTH 720
#define HEIGHT 640

/* #define TEST_PARTICLES */
#define TEST_SNOW

int main()
{
#ifdef TEST_PARTICLES
  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  lowg_renderer2d_init(WIDTH, HEIGHT);

  srand(time(NULL));

  for (int i = 0; i < 9000; i++) {
    float xx = (float) (rand() % WIDTH);
    float yy = (float) (rand() % HEIGHT);

    float max = 1.0f, min = 0.0f;
    float r = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
    float g = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
    float b = (float) (rand() / (float) RAND_MAX) * (max - min) + min;

    max = 5.0f;
    min = 2.0f;
    float w = (float) (rand() / (float) RAND_MAX) * (max - min) + min;

    lowg_sprite_t* sprite = lowg_sprite_new_color(xx, yy, w, w, (vec3_t) { r, g, b });

    max = 2.0f;
    min = -2.0f;
    float dx = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
    float dy = (float) (rand() / (float) RAND_MAX) * (max - min) + min;

    sprite->dx = dx;
    sprite->dy = dy;

    lowg_renderer2d_add(sprite);
  }

  while (!lowg_window_should_close(w)) {
    lowg_window_clear(0.4f, 0.1f, 0.7f);

    for (int i = 0; i < sprites->len; i++) {
      lowg_sprite_t* s = g_ptr_array_index(sprites, i);
      s->position->x += s->dx;
      s->position->y += s->dy;

      if (
        s->position->x > WIDTH ||
        s->position->x < 0 ||
        s->position->y > HEIGHT ||
        s->position->y < 0
      ) {
        lowg_render2d_remove(i);
      }
    }

    lowg_render2d();

    lowg_window_update(w);
  }
#endif
#ifdef TEST_SNOW
  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  lowg_renderer2d_init(WIDTH, HEIGHT);

  srand(time(NULL));

  float max, min, dx, dy;
  while (!lowg_window_should_close(w)) {
    lowg_window_clear(0.4f, 0.1f, 0.7f);

    max = 0.2f, min = -0.2f;
    dx = (float) (rand() / (float) RAND_MAX) * (max - min) + min;
    max = 2.0f, min = 0.5f;
    dy = (float) (rand() / (float) RAND_MAX) * (max - min) + min;

    float xx = (float) (rand() % WIDTH);
    float yy = (float) (rand() % HEIGHT);

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

    lowg_render2d();

    lowg_window_update(w);
  }
#endif

  return 0;
}
