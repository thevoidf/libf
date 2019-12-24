#include "mat4.h"

#include <stdlib.h>

float* lowg_mat4_identity()
{
  float* mat = malloc(sizeof(float) * (4 * 4));

  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      mat[row + col * 4] = 0;
    }
  }

  mat[0 + 0 * 4] = 1;
  mat[1 + 1 * 4] = 1;
  mat[2 + 2 * 4] = 1;
  mat[3 + 3 * 4] = 1;

  return mat;
}

void lowg_mat4_translate(float *mat, float x, float y, float z)
{
  mat[0 + 3 * 4] = x;
  mat[1 + 3 * 4] = y;
  mat[2 + 3 * 4] = z;
}

void lowg_mat4_scale(float *mat, float x, float y, float z)
{
  mat[0 + 0 * 4] = x;
  mat[1 + 1 * 4] = y;
  mat[2 + 2 * 4] = z;
}

float* lowg_mat4_orthographic(float left, float right, float bottom, float top, float near, float far)
{
  float* mat = lowg_mat4_identity();

  mat[0 + 0 * 4] = 2.0f / (right - left);
  mat[1 + 1 * 4] = 2.0f / (top - bottom);
  mat[2 + 2 * 4] = 2.0f / (near - far);
  mat[0 + 3 * 4] = (left + right) / (left - right);
  mat[1 + 3 * 4] = (bottom + top) / (bottom - top);
  mat[2 + 3 * 4] = (far + near) / (far - near);

  return mat;
}
