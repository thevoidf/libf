#ifndef LOWG_MAT4_H
#define LOWG_MAT4_H

float* lowg_mat4_identity();
void lowg_mat4_translate(float *mat, float x, float y, float z);
void lowg_mat4_scale(float *mat, float x, float y, float z);
float* lowg_mat4_orthographic(float left, float right, float bottom, float top, float near, float far);

#endif
