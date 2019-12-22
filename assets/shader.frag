#version 330 core

in vec3 out_color;
in vec2 out_uv;

out vec4 color;

uniform sampler2D tex;

void main()
{
  if (out_color.x > 0) {
    color = vec4(out_color, 1.0);
  } else {
    color = texture(tex, out_uv);
  }
}
