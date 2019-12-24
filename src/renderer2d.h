#ifndef LOWG_RENDERER2D_H
#define LOWG_RENDERER2D_H

#include <gmodule.h>

typedef struct lowg_sprite_t lowg_sprite_t;

unsigned int dim_w;
unsigned int dim_h;
float* model;
float* view;
float* proj;
int model_uniform;
int view_uniform;
int proj_uniform;
unsigned int program;
GPtrArray *sprites;

void lowg_renderer2d_init(unsigned int w, unsigned h);
void lowg_renderer2d_add(lowg_sprite_t* sprite);
void lowg_render2d_remove(unsigned int idx);
void lowg_render2d();

#endif
