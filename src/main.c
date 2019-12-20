#include "window.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "glad/glad.h"
#include "glfw/glfw3.h"

#define WIDTH 680
#define HEIGHT 480

int main()
{
  float vertex_data[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
  };

  lowg_window_t* w = lowg_window_new("lowg", WIDTH, HEIGHT);

  unsigned int program = lowg_create_shader_program("assets/shader.vert", "assets/shader.frag");
  glUseProgram(program);

  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  unsigned int vb;
  glGenBuffers(1, &vb);
  glBindBuffer(GL_ARRAY_BUFFER, vb);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

  while (!lowg_window_should_close(w)) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
      printf("OpenGL Error: %d\n", error);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glClearColor(0.4f, 0.1f, 0.7f, 1.0f);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    lowg_window_update(w);
  }

  return 0;
}
