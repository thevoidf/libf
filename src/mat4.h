#ifndef LOWG_MAT4_H
#define LOWG_MAT4_H

#define MAT_SIZE 4 * 4 * sizeof(float)

void lowg_mat4_identity(float *mat);
void lowg_mat4_multiply(float* mat, float* other);
void lowg_mat4_translate(float* mat, float x, float y, float z);
void lowg_mat4_rotate(float* mat, float x, float y, float z, float angle);
void lowg_mat4_scale(float* mat, float x, float y, float z);
void lowg_mat4_orthographic(float* mat, float left, float right, float bottom, float top, float near, float far);

#endif
