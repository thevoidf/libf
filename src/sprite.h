#ifndef LOWG_SPRITE_H
#define LOWG_SPRITE_H

typedef struct vec3_t vec3_t;

typedef struct lowg_sprite_t {
  float w;
  float h;
  float dx;
  float dy;
  vec3_t* color;
  vec3_t* position;
} lowg_sprite_t;

unsigned int vao;
unsigned int vbo;
unsigned int vbc;
unsigned int vbt;
unsigned int ibo;
unsigned int texture;

lowg_sprite_t* lowg_sprite_new(float x, float y, float w, float h, vec3_t color, char* tex_path);
lowg_sprite_t* lowg_sprite_new_color(float x, float y, float w, float h, vec3_t color);
lowg_sprite_t* lowg_sprite_new_image(float x, float y, float w, float h, char* tex_path);
void lowg_sprite_print(lowg_sprite_t* sprite);

#endif
