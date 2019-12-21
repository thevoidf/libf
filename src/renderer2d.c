#include "renderer2d.h"
#include "util.h"
#include "vec3.h"
#include "sprite.h"

#include <glad/glad.h>

void lowg_renderer2d_init(unsigned int program)
{
  kv_init(sprites);
  position_uniform = glGetUniformLocation(program, "pos");
  lowg_bind_program(program);
}

void lowg_renderer2d_add(lowg_sprite_t* sprite)
{
  kv_push(lowg_sprite_t*, sprites, sprite);
}

void lowg_render2d()
{
  for (int i = 0; i < kv_size(sprites); i++) {
    glEnableVertexAttribArray(i);
    lowg_sprite_t* sp = sprites.a[i];
    glUniform3fv(position_uniform, 1, sp->position);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
