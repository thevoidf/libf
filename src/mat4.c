#include "mat4.h"

#include <stdlib.h>
#include <math.h>

float* lowg_mat4_identity()
{
  float* mat = malloc(sizeof(float) * (4 * 4));
  /* float mat[4 * 4]; */

  for (int col = 0; col < 4; col++) {
    for (int row = 0; row < 4; row++) {
      mat[row + col * 4] = 0.0f;
    }
  }

  mat[0 + 0 * 4] = 1;
  mat[1 + 1 * 4] = 1;
  mat[2 + 2 * 4] = 1;
  mat[3 + 3 * 4] = 1;

  return mat;
}

float* lowg_mat4_multiply(float* a, float* b)
{
  float *mat = lowg_mat4_identity();

  for (int row = 0; row < 4; row++) {
    for (int col = 0; col < 4; col++) {
      float sum = 0.0f;
      for (int e = 0; e < 4; e++) {
        sum += a[e + row * 4] * b[col + e * 4];
      }
      mat[col + row * 4] = sum;
    }
  }

  return mat;
}

float* lowg_mat4_translate(float x, float y, float z)
{
  float *mat = lowg_mat4_identity();

  mat[0 + 3 * 4] = x;
  mat[1 + 3 * 4] = y;
  mat[2 + 3 * 4] = z;

  return mat;
}

float* lowg_mat4_rotate(float x, float y, float z, float angle)
{
  float *mat = lowg_mat4_identity();
  /* float r = toRadians(angle); */
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

  return mat;
}

float* lowg_mat4_scale(float x, float y, float z)
{
  float *mat = lowg_mat4_identity();

  mat[0 + 0 * 4] = x;
  mat[1 + 1 * 4] = y;
  mat[2 + 2 * 4] = z;

  return mat;
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
