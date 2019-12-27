#include "window.h"
#include "renderer2d.h"
#include "sprite.h"

#define WIDTH 640 * 2
#define HEIGHT 420 * 2

int main()
{
  lowg_window_t* win = lowg_window_new("lowg Textures", WIDTH, HEIGHT);
  lowg_sprite_t* sprite_color = lowg_sprite_new_color(100.0f, 100.0f, 200.0f, 200.0f, (vec3_t) { 1.0f, 1.0f, 1.0f });
  lowg_sprite_t* sprite_texture = lowg_sprite_new_image(400.0f, 200.0f, 340.0f, 240.0f, "./assets/robot.jpg");
  lowg_sprite_t* sprite_texture_alpha = lowg_sprite_new_image(800.0f, 400.0f, 200.0f, 200.0f, "./assets/flk.png");

  lowg_renderer2d_init(WIDTH, HEIGHT);

  lowg_renderer2d_add(sprite_color);
  lowg_renderer2d_add(sprite_texture);
  lowg_renderer2d_add(sprite_texture_alpha);

  while (!lowg_window_should_close(win)) {
    lowg_window_clear(0.4f, 0.1f, 0.7f);

    lowg_render2d();

    lowg_window_update(win);
  }

  return 0;
}
