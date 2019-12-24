#include "renderer2d.h"
#include "util.h"
#include "vec3.h"
#include "mat4.h"
#include "sprite.h"

#include <glad/glad.h>

void lowg_renderer2d_init(unsigned int w, unsigned h)
{
  dim_w = w;
  dim_h = h;

  sprites = g_ptr_array_new();

  model = lowg_mat4_identity();
  view = lowg_mat4_identity();
  proj = lowg_mat4_identity();

  program = lowg_create_shader_program("assets/shader.vert", "assets/shader.frag");

  model_uniform = glGetUniformLocation(program, "model");
  view_uniform = glGetUniformLocation(program, "view");
  proj_uniform = glGetUniformLocation(program, "proj");

  lowg_bind_program(program);
}

void lowg_renderer2d_add(lowg_sprite_t* sprite)
{
  g_ptr_array_add(sprites, sprite);
}

void lowg_render2d_remove(unsigned int idx)
{
  lowg_sprite_t* sprite = g_ptr_array_index(sprites, idx);
  g_ptr_array_remove_index(sprites, idx);
  free(sprite->color);
  free(sprite->position);
  free(sprite);
}

void lowg_render2d()
{
  float* model = lowg_mat4_identity();
  float* view = lowg_mat4_identity();
  float* proj = lowg_mat4_orthographic(0.0f, dim_w, dim_h, 0.0f, -1.0f, 1.0f);

  for (int i = 0; i < sprites->len; i++) {
    lowg_sprite_t* sp = g_ptr_array_index(sprites, i);

    glBindVertexArray(i + 1);
    glBindTexture(GL_TEXTURE_2D, i + 1);

    lowg_mat4_translate(model,
      sp->position->x,
      sp->position->y,
      sp->position->z);
    lowg_mat4_scale(model, sp->w, sp->h, 0);

    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, proj);
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, view);
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
