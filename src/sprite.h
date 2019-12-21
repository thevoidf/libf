#ifndef LOWG_SPRITE_H
#define LOWG_SPRITE_H

typedef struct vec3_t vec3_t;

typedef struct lowg_sprite_t {
  float w;
  float h;
  vec3_t* color;
  vec3_t* position;
} lowg_sprite_t;

lowg_sprite_t* lowg_sprite_new(float x, float y, float w, float h, vec3_t color);
void lowg_sprite_print(lowg_sprite_t* sprite);

#endif
