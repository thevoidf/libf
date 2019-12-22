#include "window.h"
#include "sprite.h"
#include "renderer2d.h"
#include "vec3.h"

#define WIDTH 680
#define HEIGHT 480

int main()
{
  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  lowg_sprite_t* sprite = lowg_sprite_new(0.0f, 0.0f, 0.4f, 0.4f, (vec3_t) { 1.0f, 0.0f, 0.0f });
  lowg_sprite_t* sprite2 = lowg_sprite_new(-0.5f, 0.0f, 0.2f, 0.2f, (vec3_t) { 1.0f, 1.0f, 1.0f });

  lowg_renderer2d_init(program);
  lowg_renderer2d_add(sprite);
  lowg_renderer2d_add(sprite2);

  while (!lowg_window_should_close(w)) {
    lowg_window_clear(0.4f, 0.1f, 0.7f);

    sprite->position->x += 0.1f * 0.001f;
    sprite->position->y += 0.1f * 0.001f;

    sprite2->position->x -= 0.1f * 0.001f;
    sprite2->position->y -= 0.1f * 0.001f;

    lowg_render2d();

    lowg_window_update(w);
  }

  return 0;
}
