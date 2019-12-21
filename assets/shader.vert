#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 out_color;

uniform vec3 pos;

void main()
{
  gl_Position = vec4(position + pos, 1.0);
  out_color = color;
}
