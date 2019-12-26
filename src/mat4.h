#ifndef LOWG_MAT4_H
#define LOWG_MAT4_H

float* lowg_mat4_identity();
float* lowg_mat4_multiply(float* a, float* b);
float* lowg_mat4_translate(float x, float y, float z);
float* lowg_mat4_rotate(float x, float y, float z, float angle);
float* lowg_mat4_scale(float x, float y, float z);
float* lowg_mat4_orthographic(float left, float right, float bottom, float top, float near, float far);

#endif
