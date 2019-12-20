#ifndef LOWG_UTIL_H
#define LOWG_UTIL_H

char* lowg_read_file(char* path);
unsigned int lowg_create_shader_program(char * vertex_path, char* fragment_path);
unsigned int lowg_create_shader(char* path, unsigned int type);
unsigned int lowg_create_program(unsigned int vertex_shader, unsigned int fragment_shader);

#endif
