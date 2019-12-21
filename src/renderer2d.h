#ifndef LOWG_RENDERER2D_H
#define LOWG_RENDERER2D_H

#include <kvec/kvec.h>

typedef struct lowg_sprite_t lowg_sprite_t;

int position_uniform;
kvec_t(lowg_sprite_t*) sprites;

void lowg_renderer2d_init(unsigned int program);
void lowg_renderer2d_add(lowg_sprite_t* sprite);
void lowg_render2d();

#endif
