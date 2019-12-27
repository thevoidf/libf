#include "renderer2d.h"
#include "util.h"
#include "vec3.h"
#include "mat4.h"
#include "sprite.h"
#include "array.h"

#include <glad/glad.h>

void lowg_renderer2d_init(unsigned int w, unsigned h)
{
  dim_w = w;
  dim_h = h;

  sprites = lowg_array_new();

  lowg_mat4_identity(model);
  lowg_mat4_identity(view);
  lowg_mat4_identity(proj);
  lowg_mat4_orthographic(proj, 0.0f, dim_w, dim_h, 0.0f, -1.0f, 1.0f);

  program = lowg_create_shader_program("assets/shader.vert", "assets/shader.frag");

  model_uniform = glGetUniformLocation(program, "model");
  view_uniform = glGetUniformLocation(program, "view");
  proj_uniform = glGetUniformLocation(program, "proj");

  lowg_bind_program(program);
}

void lowg_renderer2d_add(lowg_sprite_t* sprite)
{
  lowg_array_add(sprites, sprite);
}

void lowg_render2d_remove(unsigned int idx)
{
  lowg_sprite_t* sprite = sprites->array[idx];
  lowg_array_remove(sprites, idx);
  lowg_sprite_free(sprite);
}

void lowg_render2d()
{
  unsigned int size = lowg_array_size(sprites);
  for (int i = 0; i < size; i++) {
    lowg_sprite_t* sp = lowg_array_get(sprites, i);

    glBindVertexArray(i + 1);
    glBindTexture(GL_TEXTURE_2D, sp->texture);

    float scale[16];
    float trans[16];
    float neg[16];
    float rotate[16];

    lowg_mat4_identity(scale);
    lowg_mat4_identity(trans);
    lowg_mat4_identity(neg);
    lowg_mat4_identity(rotate);

    lowg_mat4_scale(scale, sp->w, sp->h, 0);
    lowg_mat4_translate(trans,
        sp->position.x,
        sp->position.y,
        sp->position.z);
    lowg_mat4_translate(neg,
        -sp->position.x,
        -sp->position.y,
        -sp->position.z);
    lowg_mat4_rotate(rotate,
        sp->rotate.x,
        sp->rotate.y,
        sp->rotate.z,
        sp->angle);

    lowg_mat4_identity(model);
    lowg_mat4_multiply(model, scale);
    lowg_mat4_multiply(model, trans);
    lowg_mat4_multiply(model, neg);
    lowg_mat4_multiply(model, rotate);
    lowg_mat4_multiply(model, trans);

    glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, proj);
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, view);
    glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
}
