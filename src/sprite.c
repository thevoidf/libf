#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>
#include "vec3.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

lowg_sprite_t* lowg_sprite_new(float x, float y, float w, float h, vec3_t color, char* tex_path)
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

  // hack
  sprite->position->x += w / 2.0f;
  sprite->position->y += h / 2.0f;

  float vertices[] = {
    0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };
  float uvs[] = {
    1.0f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f,
    0.0f, 1.0f
  };
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };
  float colors[] = {
    color.x, color.y, color.z,
    color.x, color.y, color.z,
    color.x, color.y, color.z,
    color.x, color.y, color.z
  };

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &vbc);
  glBindBuffer(GL_ARRAY_BUFFER, vbc);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

  if (tex_path) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int img_w, img_h, img_channels;
    unsigned char* data;

    /* stbi_set_flip_vertically_on_load(1); */
    if (tex_path)
      data = stbi_load(tex_path, &img_w, &img_h, &img_channels, 0);
    if (!data)
      printf("Failed to load image\n");

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_w, img_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    if (tex_path)
      stbi_image_free(data);
  }

  glGenBuffers(1, &vbt);
  glBindBuffer(GL_ARRAY_BUFFER, vbt);
  glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  return sprite;
}

lowg_sprite_t* lowg_sprite_new_color(float x, float y, float w, float h, vec3_t color)
{
  return lowg_sprite_new(x, y, w, h, color, NULL);
}

lowg_sprite_t* lowg_sprite_new_image(float x, float y, float w, float h, char* tex_path)
{
  return lowg_sprite_new(x, y, w, h, (vec3_t) {}, tex_path);
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
