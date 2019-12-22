#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include "vec3.h"

lowg_sprite_t* lowg_sprite_new(float x, float y, float w, float h, vec3_t color)
{
  lowg_sprite_t* sprite = memcpy(
    malloc(sizeof(lowg_sprite_t)),
    &(lowg_sprite_t const) { .w = w, .h = h },
    sizeof(lowg_sprite_t)
  );
  sprite->position = memcpy(
    malloc(sizeof(vec3_t)),
    &(vec3_t const) { .x = x, .y = y },
    sizeof(vec3_t)
  );
  sprite->color = memcpy(
    malloc(sizeof(vec3_t)),
    &color,
    sizeof(vec3_t)
  );

  float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };
  float colors[] = {
    color.x, color.y, color.z,
    color.x, color.y, color.z,
    color.x, color.y, color.z,
    color.x, color.y, color.z
  };
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  unsigned int vbc;
  glGenBuffers(1, &vbc);
  glBindBuffer(GL_ARRAY_BUFFER, vbc);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

  unsigned int ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  return sprite;
}

void lowg_sprite_print(lowg_sprite_t* sprite)
{
  printf(
    "{ x: %.1f, y: %.1f, w: %.1f, h: %.1f }\n",
    sprite->position->x,
    sprite->position->y,
    sprite->w,
    sprite->h
  );
}
