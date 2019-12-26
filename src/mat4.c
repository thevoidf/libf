#include "mat4.h"

#include <math.h>

void lowg_mat4_identity(float *mat)
{
  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      mat[row + col * 4] = 0.0f;
    }
  }

  mat[0 + 0 * 4] = 1;
  mat[1 + 1 * 4] = 1;
  mat[2 + 2 * 4] = 1;
  mat[3 + 3 * 4] = 1;
}

void lowg_mat4_multiply(float* mat, float* other)
{
  float result[MAT_SIZE];

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      float sum = 0.0f;
      for (int e = 0; e < 4; e++) {
        sum += mat[e + row * 4] * other[col + e * 4];
      }
      result[col + row * 4] = sum;
    }
  }

  for (int i = 0; i < 4 * 4; i++)
    mat[i] = result[i];
}

void lowg_mat4_translate(float* mat, float x, float y, float z)
{
  mat[0 + 3 * 4] = x;
  mat[1 + 3 * 4] = y;
  mat[2 + 3 * 4] = z;
}

void lowg_mat4_rotate(float *mat, float x, float y, float z, float angle)
{
  float r = angle;
  float c = cos(r);
  float s = sin(r);
  float omc = 1.0f - c;

  mat[0 + 0 * 4] = x * x * omc + c;
  mat[1 + 0 * 4] = y * x * omc + z * s;
  mat[2 + 0 * 4] = x * z * omc - y * s;

  mat[0 + 1 * 4] = x * y * omc - z * s;
  mat[1 + 1 * 4] = y * y * omc + c;
  mat[2 + 1 * 4] = y * z * omc + x * s;

  mat[0 + 2 * 4] = x * z * omc + y * s;
  mat[1 + 2 * 4] = y * z * omc - x * s;
  mat[2 + 2 * 4] = z * z * omc + c;
}

void lowg_mat4_scale(float *mat, float x, float y, float z)
{
  mat[0 + 0 * 4] = x;
  mat[1 + 1 * 4] = y;
  mat[2 + 2 * 4] = z;
}

void lowg_mat4_orthographic(float *mat, float left, float right, float bottom, float top, float near, float far)
{
  mat[0 + 0 * 4] = 2.0f / (right - left);
  mat[1 + 1 * 4] = 2.0f / (top - bottom);
  mat[2 + 2 * 4] = 2.0f / (near - far);
  mat[0 + 3 * 4] = (left + right) / (left - right);
  mat[1 + 3 * 4] = (bottom + top) / (bottom - top);
  mat[2 + 3 * 4] = (far + near) / (far - near);
}
