#include <glad/glad.h>
#include <stdio.h>

#include "../util.h"
#include "../io/io.h"
#include "render_internal.h"

u32 compile_shader_from_source(const char *path, GLenum type, char *log_buf) {
    int success;

    File file = io_file_read(path);
    if (!file.is_valid) {
        ERROR_EXIT("Error occured while reading shader: %s\n", path);
    }

    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char *const *)&file, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) { 
        glGetShaderInfoLog(shader, sizeof(log_buf), NULL, log_buf);
        ERROR_EXIT("Error compiling shader: %s; %s\n", path, log_buf);
    }

    free(file.data);
    return shader;
}

u32 render_shader_create(const char *path_vert, const char *path_frag){
    int success;
    char log[512];

    u32 shader_vertex = compile_shader_from_source(path_vert, GL_VERTEX_SHADER, log);
    u32 shader_fragment = compile_shader_from_source(path_frag, GL_FRAGMENT_SHADER, log);

    u32 shader = glCreateProgram();
    glAttachShader(shader, shader_vertex);
    glAttachShader(shader, shader_fragment);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        ERROR_EXIT("Error while linking shader. %s\n", log);
    }

    return shader;
}